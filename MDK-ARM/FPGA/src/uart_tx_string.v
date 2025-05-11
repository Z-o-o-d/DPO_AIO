/*
 * @Author: Tomood
 * @Date: 2025-03-22 03:08:18
 * @LastEditors: Tomood
 * @LastEditTime: 2025-03-28 02:26:40
 * @FilePath: /uart_ip/src/uart_tx_string.v
 * @Description: 
 * Copyright (c) 2025 by Tomood, All Rights Reserved. 
 */
module uart_tx_string #(
    parameter CLK_FREQ = 10_000_000, //时钟频率 (Hz)
    parameter BUAD_RATE = 115200, //波特率
    parameter GAP_TIME = 100, //发送间隔时间（ms）
    parameter STR_DAT = "TEST\r", //要发送的字符串
    parameter STR_LEN = 5  // 要发送的字符串长度
) (
    //system
    input  wire         clk,
    input  wire         rst_n,
    //uart
    output wire         uart_txd
);

//CLK_PERIOD:时钟周期（us）
localparam CLK_PERIOD = 1000_000_000 / CLK_FREQ;
//CNT_MAX:计数器最大值
localparam CNT_MAX = (1000_000 * GAP_TIME) / CLK_PERIOD;

//state machine status paramater
localparam WAIT = 1'b0;
localparam SEND = 1'b1;

wire core_done;
reg  core_en;
wire [7:0] core_din;

//state machine status regs
reg cstate;
reg nstate;

reg [$clog2(CNT_MAX)-1:0] time_cnt;
reg [$clog2(STR_LEN)-1:0] byte_cnt;

reg [(STR_LEN*8)-1:0] string_buf;

//the 1st part of the state mechine
always @(posedge clk or negedge rst_n) begin
    if(!rst_n)
        cstate <= WAIT;
    else
        cstate <= nstate;
end

//the 2st part of the state mechine
always @(*) begin
    case (cstate)
        WAIT : begin
            //if accept a send req
            if(time_cnt == CNT_MAX - 1'b1)
                nstate = SEND;
            else
                nstate = WAIT;
        end
        SEND : begin
            //if send done
            if((byte_cnt == STR_LEN - 1'b1) && core_done)
                nstate = WAIT;
            else
                nstate = SEND;
        end
    endcase
end

// STR_DAT
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        string_buf <= 0; //only support while using system verilog
    end else if((cstate == WAIT) && (time_cnt == CNT_MAX - 1'b1)) begin 
        string_buf <= STR_DAT; //only support while using system verilog
    end else if(core_done)begin //a byte had sent
        string_buf <= string_buf << 8;//move a byte
    end
end

//core_din: the byte data which input to the uart core
assign core_din = string_buf[(STR_LEN*8)-1 -: 8]; //send the 8LSB of the string buf

// time_cnt: counter for time delay
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        time_cnt <= 0;
    end else if(cstate == WAIT)begin
        if(time_cnt < CNT_MAX - 1'b1)
            time_cnt <= time_cnt + 1'b1;
    end else if(cstate == SEND)begin
        time_cnt <= 0;
    end
end

// core_en : send enable of the uart core
//assign core_en = (time_cnt == CNT_MAX) && (cstate == WAIT);

always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        core_en <= 1'b0;
    end else if(cstate == SEND)begin
        if((byte_cnt < STR_LEN - 1'b1) && core_done) // if uart core have sent a byte.
            core_en <= 1'b1;
        else
            core_en <= 1'b0;
    end else if(cstate == WAIT)begin
        if(time_cnt == CNT_MAX - 1'b1) // if sleep time out
            core_en <= 1'b1;
        else
            core_en <= 1'b0;
    end else begin
        core_en <= 1'b0;
    end
end


// byte_cnt: counter for send data byte
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        byte_cnt <= 0;
    end else if(cstate == WAIT) begin
        byte_cnt <= 0;
    end else if((cstate == SEND) && (byte_cnt < STR_LEN))begin
        if(core_done) // if uart core have sent a byte.
            byte_cnt <= byte_cnt + 1'b1;
        else
            byte_cnt <= byte_cnt;
    end
end

uart_tx_core #(
    .CLK_FREQ(CLK_FREQ),
    .BUAD_RATE(BUAD_RATE)
)u_uart_tx_core(
    //system
    .clk(clk),
    .rst_n(rst_n),
    //ctrl signals
    .dat_en(core_en),
    .din(core_din),
    //uart
    .uart_txd(uart_txd),
    //status out
    .tx_busy(/*do not use*/),
    .tx_done(core_done)
);
endmodule