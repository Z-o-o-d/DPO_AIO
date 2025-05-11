/*
 * @Author: Tomood
 * @Date: 2025-03-22 01:22:21
 * @LastEditors: Tomood
 * @LastEditTime: 2025-03-28 11:15:59
 * @FilePath: /uart_ip/src/uart_tx_core.v
 * @Description: 
 * Copyright (c) 2025 by Tomood, All Rights Reserved. 
 */
`timescale 1ns / 1ps

module uart_tx_core #(
    parameter CLK_FREQ = 10_000_000,
    parameter BUAD_RATE = 115200
)(
    //system
    input  wire           clk,
    input  wire           rst_n,
    //ctrl signals
    input  wire           dat_en,
    input  wire [7:0]     din,
    //uart
    output reg            uart_txd,  
    //status out
    output reg            tx_busy,
    output wire           tx_done
);

//CNT_MAX:时钟分频计数器最大值
localparam CNT_MAX = CLK_FREQ / BUAD_RATE;
//DR:数据寄存器
reg [7:0] DR;
//dff_en:触发器时钟使能信号
reg dff_en;
//div_cnt:时钟分频计数器
reg [$clog2(CNT_MAX)-1:0] div_cnt;
//bit_cnt:位计数器
reg [2+1:0] bit_cnt;
//state:状态机
reg [2:0] state;
//********************************************************************//
//***************************   Main Code   **************************//
//********************************************************************//

//dff_en:触发器时钟使能信号
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        dff_en <= 1'b0;
    end else if(div_cnt == CNT_MAX - 1'b1) begin
        dff_en <= 1'b1;
    end else begin
        dff_en <= 1'b0;
    end
end

//div_cnt:时钟分频计数器
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        div_cnt <= 0;
    end else if(div_cnt == CNT_MAX - 1'b1) begin
        div_cnt <= 0;
    end else begin
        div_cnt <= div_cnt + 1'b1;
    end
end

//DR:数据寄存器
always @(posedge clk or negedge rst_n) begin
    if(!rst_n)
        DR <= 0;
    else if(dat_en)  //有数据输入
        DR <= din;
end

//bit_cnt:位计数器
always @(posedge clk or negedge rst_n) begin
    if(!rst_n)
        bit_cnt <= 1'b0;
    else if(dff_en) begin
        if(bit_cnt == 9)//溢出
            bit_cnt <= 1'b0;
        else if(tx_busy)//正在发送时自增
            bit_cnt <= bit_cnt + 1'b1;
    end
end

//uart_txd:串口发送数据线
always@(posedge clk or negedge rst_n) begin
    if(!rst_n)
        uart_txd <= 1'b1; //空闲状态时为高电平
    else if(dff_en) begin
        if(tx_busy) //在发送状态
            case(bit_cnt)
                0 : uart_txd <= 1'b0; // START BIT
                1 : uart_txd <= DR[0]; // LSB FIRST
                2 : uart_txd <= DR[1];
                3 : uart_txd <= DR[2];
                4 : uart_txd <= DR[3];
                5 : uart_txd <= DR[4];
                6 : uart_txd <= DR[5];
                7 : uart_txd <= DR[6];
                8 : uart_txd <= DR[7];
                9 : uart_txd <= 1'b1; // STOP BIT
                default : uart_txd <= 1'b1; //空闲状态时为高电平
            endcase
        else begin
            uart_txd <= 1'b1; //空闲状态时为高电平
        end
    end

end

//tx_busy:模块工作忙信号
always@(posedge clk or negedge rst_n) begin
    if(!rst_n)
        tx_busy <= 1'b0;
    else if(dat_en) //有数据输入
        tx_busy <= 1'b1;
    else if(dff_en && (bit_cnt == 9)) /*bit_cnt == 8溢出时为连续*/
        tx_busy <= 1'b0;
 end
 

assign tx_done = dff_en && (bit_cnt == 9);

endmodule
