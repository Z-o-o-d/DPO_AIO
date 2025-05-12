module dds #(
    parameter DAT_W = 14, // 输出数据宽度
    parameter ROM_W = 10, // ROM 地址宽度（即相位位数）
    parameter FW_W  = 32  // 相位累加器宽度
) (
    input  wire             clk,
    input  wire             rst_n,
    input  wire             int_dff_en,

    input  wire [ FW_W-1:0] freq_word,
    input  wire [ FW_W-1:0] triangle_sym,

    output reg  [ FW_W-1:0] phase_acc,
    output reg  [ FW_W-1:0] phase_acc_dly,

    output reg  [DAT_W-1:0] sine_wave_dout,
    output reg  [DAT_W-1:0] ramp_wave_dout
);

    // ROM 读取正弦波表
    reg [DAT_W-1:0] sine_wave_mem [(2**ROM_W)-1:0];
    initial begin
        $readmemh("./sin_wave.dat", sine_wave_mem);
    end

    // 相位累加器逻辑
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            phase_acc <= 0;
        else if (int_dff_en)
            phase_acc <= phase_acc + freq_word;
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            phase_acc_dly <= 0;
        else if (int_dff_en)
            phase_acc_dly <= phase_acc;
    end

    // Sine 波输出
    wire [ROM_W-1:0] addr = phase_acc_dly[FW_W-1 -: ROM_W];
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            sine_wave_dout <= 0;
        else if (int_dff_en)
            sine_wave_dout <= sine_wave_mem[addr];
    end

    // 三角波输出
    wire [FW_W-1:0] phase_now = phase_acc_dly;
    wire [FW_W-1:0] full_scale = 32'hFFFFFFFF;  // 最大相位值
    wire [FW_W-1:0] half_scale = 32'h7FFFFFFF;  // 半周期
    wire [FW_W-1:0] abs_diff = (phase_now < triangle_sym) ?
                                (triangle_sym - phase_now) :
                                (phase_now - triangle_sym);

    // 线性映射：根据相对于对称点的距离决定输出幅值，最大 DAT_W 位
    // 最简单的方式：abs_diff 高位取 ROM_W 位，再左移 DAT_W - ROM_W 做线性斜率
    wire [ROM_W-1:0] triangle_addr = abs_diff[FW_W-1 -: ROM_W];
    wire [DAT_W-1:0] triangle_val  = triangle_addr << (DAT_W - ROM_W);

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            ramp_wave_dout <= 0;
        else if (int_dff_en)
            ramp_wave_dout <= triangle_val;
    end

endmodule
