/*
 * @Author: Tomood
 * @Date: 2024-07-31 02:45:23
 * @LastEditors: Tomood
 * @LastEditTime: 2024-12-28 12:21:09
 * @FilePath: /dds/src/dds.v
 * @Description: 
 * Copyright (c) 2024 by Tomood, All Rights Reserved. 
 */

// ****************************************************************************************************** //
// Features: A high-precision dds who can be used to generate low-frequency signals. 
//           The dds based on look-up table.
//           And only 1/4 period of the sine wave was stored to saving rom resources.
// Tips :    The dds was designed to be used for audio tremolo effects ,
//           the phase of output wave is not supported to configuration manually.
// ****************************************************************************************************** //

// v1.1: Change the clock divider logics to use the filp-flop CE signal from an external input. -Tomood Edit
// v2.0a: 改成读全部的
module dds #(
    parameter DAT_W = 16, // The width of the sine wave data table in ROM.
    parameter ROM_W = 12, // The width of addr of the ROM table,the number of sampling points per sinewave's period = 2^ROM_W
    parameter FW_W  = 24  // The width of frequency word
) (
    //clk & reset inputs
    input  wire             clk,
    input  wire             rst_n,
    input  wire             int_dff_en,
    //registers
    input  wire [ FW_W-1:0] freq_word,
    //data output
    output wire             dout_vld,
    output reg  [DAT_W-1:0] dout
);

  //sine_wave_mem
  // Read a sine wave data table from external file.
  reg [DAT_W-1:0] sine_wave_mem [(2**ROM_W)-1:0];

  initial begin
    $readmemh("./sin_wave.dat",sine_wave_mem);
  end

  


  //phase_acc
  reg [FW_W-1:0] phase_acc;
  reg [FW_W-1:0] phase_acc_dly;
///////////////////////////////
  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      phase_acc <= 0;
    end else if (int_dff_en) begin
      phase_acc <= phase_acc + freq_word;  //Auto Reload
    end
  end

  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      phase_acc_dly <= 0;
    end else if (int_dff_en) begin
      phase_acc_dly <= phase_acc;
    end 
  end
///////////////////////////////



  //dout
///////////////////////////////
  wire [ROM_W-1:0] addr = phase_acc_dly[FW_W-1 -: ROM_W];

  always @(posedge clk or negedge rst_n) begin
      if (!rst_n) begin
          dout <= 0;
      end else if (int_dff_en) begin
//        dout <= sine_wave_mem[addr];
        dout <= phase_acc_dly[FW_W-1:FW_W+1-DAT_W];

      end
  end

  //dout_vld
  assign dout_vld = int_dff_en;  //在更新时输出即可
///////////////////////////////

endmodule
