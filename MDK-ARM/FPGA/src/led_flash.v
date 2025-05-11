module led_flash(
    input clk,
    input rst_n,
    output UART_TX,
    output clkout0,


    output [DAT_W-1 : 0]  dds_dout_1,
    output DAC_CLK_1,
    output reg DAC_REF_1,
    output reg DAC_DC_1,

    output [DAT_W-1 : 0]  dds_dout_2,
    output DAC_CLK_2,
    output reg DAC_REF_2,
    output reg DAC_DC_2

);

// Parameters             
parameter CLK_FREQ = 50_000_000; //时钟频率 (Hz)
parameter BUAD_RATE = 115200; //波特率
parameter GAP_TIME = 100; //发送间隔时间（ms）

parameter FW_W      = 30;  // 频率控制字
parameter DAT_W = 16; // The width of the sine wave data table in ROM.

parameter DDS_W = 14; // The width of the DAC904.
wire clkout0;


reg [15:0] counter_ref_1 = 0;
reg [15:0] counter_dc_1 = 0;
reg [15:0] duty_cycle_ref_1 =  5000;
reg [15:0] duty_cycle_dc_1 =  10000;



reg [15:0] counter_ref_2 = 0;
reg [15:0] counter_dc_2 = 0;
reg [15:0] duty_cycle_ref_2 =  65535;
reg [15:0] duty_cycle_dc_2 =  65535;

reg   [ FW_W-1:0]  freq_word               = 268_435_45 ;

Gowin_PLL u_Gowin_PLL(
    .lock(lock), //output lock
    .clkout0(clkout0), //output clkout0
    .clkin(clk) //input clkin
);



uart_tx_string #(
    .CLK_FREQ(CLK_FREQ),
    .BUAD_RATE(BUAD_RATE),
    .GAP_TIME(GAP_TIME),//发送间隔时间（ms）
    .STR_DAT("J18\n"), //要发送的字符串
    .STR_LEN(4)
)u_uart_tx_string(
    //system
    .clk(clk),
    .rst_n(rst_n),
    .uart_txd(UART_TX)
);




always @(posedge clkout0 or negedge rst_n) begin
    if (!rst_n) begin
        counter_ref_1 <= 8'b0;
        DAC_REF_1 <= 1'b0;
    end else begin
        counter_ref_1 <= counter_ref_1 + 1;
        if (counter_ref_1 < duty_cycle_ref_1) begin
            DAC_REF_1 <= 1'b1;
        end else begin
            DAC_REF_1 <= 1'b0;
        end
    end
end

always @(posedge clkout0 or negedge rst_n) begin
    if (!rst_n) begin
        counter_dc_1 <= 8'b0;
        DAC_DC_1 <= 1'b0;
    end else begin
        counter_dc_1 <= counter_dc_1 + 1;
        if (counter_dc_1 < duty_cycle_dc_1) begin
            DAC_DC_1 <= 1'b1;
        end else begin
            DAC_DC_1 <= 1'b0;
        end
    end
end


always @(posedge clkout0 or negedge rst_n) begin
    if (!rst_n) begin
        counter_ref_2 <= 8'b0;
        DAC_REF_2 <= 1'b0;
    end else begin
        counter_ref_2 <= counter_ref_2 + 1;
        if (counter_ref_2 < duty_cycle_ref_2) begin
            DAC_REF_2 <= 1'b1;
        end else begin
            DAC_REF_2 <= 1'b0;
        end
    end
end

always @(posedge clkout0 or negedge rst_n) begin
    if (!rst_n) begin
        counter_dc_2 <= 8'b0;
        DAC_DC_2 <= 1'b0;
    end else begin
        counter_dc_2 <= counter_dc_2 + 1;
        if (counter_dc_2 < duty_cycle_dc_2) begin
            DAC_DC_2 <= 1'b1;
        end else begin
            DAC_DC_2 <= 1'b0;
        end
    end
end





//  always @(posedge clkout0 or negedge rst_n) begin
//      if (!rst_n) begin
//         DAC_CLK     <= 'b0 ;
//      end
//      else begin
//         c     <= ~DAC_CLK ;
//      end
//   end



ODDR uut( 
.Q0(DAC_CLK_1), 
.Q1(), 
.D0(1'b1), 
.D1(1'b0), 
.TX(0), 
.CLK(clkout0) 
); 

ODDR uut_( 
.Q0(DAC_CLK_2), 
.Q1(), 
.D0(1'b1), 
.D1(1'b0), 
.TX(0), 
.CLK(clkout0) 
); 


dds #(
    .FW_W      ( FW_W   )  // The width of addr of the ROM table
)
 u_dds_1 (
    //clk & reset inputs
    .clk                     ( clkout0                    ),
    .rst_n                   ( rst_n                  ),

    .int_dff_en              (  1                 ),
    .freq_word               ( freq_word  [ FW_W-1:0] ),

    .dout_vld                (                ),
    .dout                    ( dds_dout_1               )
);


dds #(
    .FW_W      ( FW_W   )  // The width of addr of the ROM table
)
 u_dds_2 (
    //clk & reset inputs
    .clk                     ( clkout0                    ),
    .rst_n                   ( rst_n                  ),

    .int_dff_en              (  1                 ),
    .freq_word               ( freq_word  [ FW_W-1:0] ),

    .dout_vld                (                ),
    .dout                    ( dds_dout_2               )
);

endmodule