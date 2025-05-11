module spi_slave (
    input  wire       clk,         // 系统时钟
    input  wire       rst_n,       // 复位

    input  wire       sclk,        // SPI时钟
    input  wire       mosi,        // 主机输出
    input  wire       cs_n,        // 片选（低有效）
    output wire       miso         // 从机输出
);

    // SPI 接收和发送移位寄存器
    reg [7:0] rx_shift;
    reg [7:0] tx_shift;
    reg [2:0] bit_cnt;

    reg [7:0] reg_file [0:255];     // 寄存器表
    reg [7:0] address;
    reg [7:0] status_reg = 8'h00;   // 状态寄存器

    reg [1:0] state;
    localparam IDLE  = 2'd0,
               CMD   = 2'd1,
               ADDR  = 2'd2,
               WRITE = 2'd3;

    reg [7:0] command;

    // miso 输出
    reg miso_reg;
    assign miso = miso_reg;

    // 用于同步SCLK边沿
    reg sclk_d, sclk_dd;
    wire sclk_rising  = (sclk_d == 0) && (sclk_dd == 1);
    wire sclk_falling = (sclk_d == 1) && (sclk_dd == 0);

    // 状态机
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sclk_d <= 0;
            sclk_dd <= 0;
        end else begin
            sclk_dd <= sclk;
            sclk_d  <= sclk_dd;
        end
    end

    // SPI 协议处理
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx_shift <= 8'd0;
            tx_shift <= 8'd0;
            bit_cnt  <= 3'd0;
            miso_reg <= 1'b0;
            state    <= IDLE;
        end else begin
            if (!cs_n) begin
                // 在 SCLK 上升沿接收 MOSI
                if (sclk_rising) begin
                    rx_shift <= {rx_shift[6:0], mosi};
                    bit_cnt  <= bit_cnt + 1;

                    if (bit_cnt == 3'd7) begin
                        case (state)
                            IDLE: begin
                                command <= {rx_shift[6:0], mosi};
                                state   <= CMD;
                            end
                            CMD: begin
                                address <= {rx_shift[6:0], mosi};
                                if ({rx_shift[6:0], mosi} < 8'hFF)
                                    state <= (command == 8'h02) ? WRITE : IDLE;
                            end
                            WRITE: begin
                                reg_file[address] <= {rx_shift[6:0], mosi};
                                state <= IDLE;
                            end
                        endcase
                        bit_cnt <= 3'd0;
                    end
                end

                // 在 SCLK 下降沿发送 MISO
                if (sclk_falling) begin
                    case (state)
                        CMD: begin
                            if (command == 8'h03)  // READ
                                tx_shift <= reg_file[{rx_shift[6:0], mosi}];
                            else if (command == 8'h05)
                                tx_shift <= status_reg;
                        end
                    endcase

                    miso_reg <= tx_shift[7];
                    tx_shift <= {tx_shift[6:0], 1'b0};
                end
            end else begin
                // 片选无效时，重置状态机
                state   <= IDLE;
                bit_cnt <= 3'd0;
                miso_reg <= 1'b0;
            end
        end
    end
endmodule
