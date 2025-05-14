module TOP(
    input clk,
    input rst_n,

    output [DAC_W-1 : 0]  dds_dout_1,
    output DAC_CLK_1,


    output [DAC_W-1 : 0]  dds_dout_2,
    output DAC_CLK_2,
    


    input      sclk,      
    input       mosi,        
    input       cs_n,   
    output      miso     
);

// Parameters             
parameter CLK_FREQ = 50_000_000; //时钟频率 (Hz)

parameter FW_W      = 32;  // 频率控制字
parameter DAC_W = 14; // The width of the DAC904.

wire clkout0;

reg   [ FW_W-1:0]  freq_word1               = 2147483 ;
reg   [ FW_W-1:0]  freq_word2               = 2147483 ;


Gowin_PLL u_Gowin_PLL(
    .lock(lock), //output lock
    .clkout0(clkout0), //output clkout0
    .clkin(clk) //input clkin
);


// 1. Generate the DAC_CLK_1 and DAC_CLK_2 signals using ODDR


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
    .freq_word               ( freq_word1  [ FW_W-1:0] ),

    .sine_wave_dout                    ( dds_dout_1               )
);


dds #(
    .FW_W      ( FW_W   )  // The width of addr of the ROM table
)
 u_dds_2 (
      //clk & reset inputs
    .clk                     ( clkout0                 ),
    .rst_n                   ( rst_n                   ),

    .int_dff_en              (  1                      ),
    .freq_word               ( freq_word2  [ FW_W-1:0] ),
    .triangle_sym            (  154748364  ),
    .ramp_wave_dout          ( dds_dout_2              )
);


spi_slave U_SPI_S(
    .clk                     ( clkout0                 ),
    .rst_n                   ( rst_n                   ),


    .sclk              (  sclk                      ),
    .mosi               ( mosi  ),
    .cs_n            (  cs_n  ),
    .miso          ( miso              )

);

endmodule