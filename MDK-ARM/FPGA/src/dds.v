

module dds #(
    parameter DAT_W = 14, // The width of the sine wave data table in ROM. 
    parameter ROM_W = 10, // The width of addr of the ROM table,the number of sampling points per sinewave's period = 2^ROM_W 10.1024
    parameter FW_W  = 64  // The width of frequency word 64

) (
    //clk & reset inputs
    input  wire             clk,
    input  wire             rst_n,
    input  wire             int_dff_en,
    


    //registers
    input  wire [ FW_W-1:0] freq_word,
    //data output

    output reg  [ FW_W-1:0] phase_acc,
    output reg  [ FW_W-1:0] phase_acc_dly,
    output reg  [DAT_W-1:0] dout
);

  //sine_wave_mem
  // Read a sine wave data table from external file.
  reg [DAT_W-1:0] sine_wave_mem [(2**ROM_W)-1:0];


  initial begin
    $readmemh("./sin_wave.dat",sine_wave_mem);
  end
   



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
          dout <= sine_wave_mem[addr];
      end
  end

  //dout_vld

///////////////////////////////

endmodule
