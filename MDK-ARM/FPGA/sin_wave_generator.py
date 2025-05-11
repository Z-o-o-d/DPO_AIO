import numpy as np


def generate_sin_wave(num_points=1024, bit_depth=14):
    # 生成 num_points 个点的正弦波
    x = np.linspace(0, 2 * np.pi, num_points)
    sin_wave = np.sin(x)

    # 将正弦波数据归一化到 0 到 2^14 - 1 的范围
    max_value = 2**bit_depth - 1
    sin_wave_normalized = (sin_wave + 1) / 2 * max_value

    # 转换为整数类型
    sin_wave_int = np.round(sin_wave_normalized).astype(int)

    return sin_wave_int


def save_to_dat_file(data, filename="sin_wave.dat"):
    try:
        with open(filename, 'w') as file:
            for value in data:
                # 转换为十六进制并去除 '0x' 前缀，不足四位时前面补零
                hex_value = '{:04X}'.format(value)
                file.write(f"{hex_value}\n")
        print(f"数据已成功保存到 {filename}")
    except Exception as e:
        print(f"保存文件时出错: {e}")


if __name__ == "__main__":
    sin_wave_data = generate_sin_wave()
    save_to_dat_file(sin_wave_data)
    