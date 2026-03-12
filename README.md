# Mambo Robot Firmware

## 简介 (Introduction)

本项目是 Mambo 机器人的嵌入式固件，基于 RISC-V 架构（具体为 StarrySky C2 / retroSoC 核心）开发。该固件控制一个四足机器人，通过 4 个 SG90 舵机实现各种动作（如站立、前进、后退、转向、趴下、跳舞等），并通过 SSD1306 OLED 显示屏展示相应的表情或状态。

## 硬件架构 (Hardware Architecture)

*   **核心控制器**: 基于 RISC-V 32位架构 (RV32IM) 的 SoC (如 StarrySky C2)。
*   **执行器**: 4 x SG90 舵机，分别连接到 PWM 通道。
    *   `Front Right` (前右)
    *   `Front Left` (前左)
    *   `Back Right` (后右)
    *   `Back Left` (后左)
*   **显示**: SSD1306 OLED 显示屏 (128x64)，通过 I2C 接口连接 (地址 0x3C)。
*   **通信**: UART 串口，用于接收控制指令。

## 软件依赖 (Software Dependencies)

1.  **RISC-V 交叉编译工具链**: `riscv64-unknown-elf-gcc` (支持 RV32IM, ILP32)。
2.  **构建工具**: GNU Make。

## 目录结构 (Directory Structure)

```
/home/timmo/ecos/prj/embedded-prj-mambot
├── src/
│   ├── main.c           # 主程序入口，包含核心业务逻辑和动作序列
│   ├── main.h           # 主程序头文件
│   ├── board.h          # 硬件寄存器定义 (GPIO, PWM, UART, I2C等)
│   ├── sg90.h           # SG90 舵机相关定义
│   ├── start.s          # 启动汇编代码
│   ├── sections.lds     # 链接脚本
│   ├── Makefile         # 构建脚本
│   ├── configs/         # 配置文件目录 (Kconfig 生成的配置)
│   ├── scripts/         # 构建辅助脚本
│   ├── components/      # 核心组件库 (自包含)
│   ├── devices/         # 设备驱动库 (自包含)
│   ├── tools/           # 构建配置工具 (Kconfig, fixdep)
│   └── build/           # 编译产出目录 (固件 hex, bin, map 等)
└── README.md            # 项目说明文档
```

## 编译与部署 (Build & Deploy)

1.  **准备环境**:
    确保已安装 `riscv64-unknown-elf-gcc` 工具链并配置到 PATH 中。

2.  **编译固件**:
    进入 `src` 目录并运行 `make`。
    ```bash
    cd src
    make
    ```
    (无需再设置 ECOS_SDK_HOME 环境变量，所有依赖已包含在项目中)

    编译成功后，将在 `src/build/` 目录下生成以下文件：
    *   `retrosoc_fw.elf`: ELF 可执行文件
    *   `retrosoc_fw.hex`: Verilog 格式的 Hex 文件 (用于仿真或烧录)
    *   `retrosoc_fw.bin`: 二进制固件文件
    *   `retrosoc_fw.txt`: 反汇编文件

3.  **清理构建**:
    ```bash
    make clean
    ```

## 通信协议 (Communication Protocol)

机器人通过 UART 接收单字节十六进制指令来执行动作。波特率通常配置为 115200 (需参考 `hp_uart_init` 设置)。

| 指令 (Hex) | 动作 (Action) | 描述 (Description) | OLED 显示 |
| :--- | :--- | :--- | :--- |
| `0xAA` | Handshake (握手) | 晃动身体，表示连接成功 | 表情 5 |
| `0xAB` | Stand Up (站立) | 恢复初始站立姿势 (所有舵机 90 度) | 表情 6 |
| `0xAC` | Step Forward (前进) | 执行前进的步态序列 | 表情 2 |
| `0xAD` | Step Backward (后退) | 执行后退的步态序列 | 表情 7 |
| `0xBB` | Turn Left (左转) | 执行原地左转动作 | 左转箭头 |
| `0xBC` | Turn Right (右转) | 执行原地右转动作 | 右转箭头 |
| `0xBD` | Lay Down (趴下) | 所有舵机调整角度使机器人趴下 | 表情 1 |
| `0xBF` | Rap (跳舞) | 执行一段节奏性的动作 | (保持原样) |

## 关键代码说明 (Key Code Modules)

*   **`src/main.c`**:
    *   `init_sg90()`: 初始化 PWM 控制器以驱动 SG90 舵机 (50Hz)。
    *   `set_sg90_degree()`: 将角度转换为 PWM 比较值。注意不同通道的安装方向可能导致角度映射不同 (部分通道做了 `180 - degree` 的反向处理)。
    *   `main()`: 系统初始化 (UART, SG90, OLED)，然后进入无限循环监听 UART 指令并执行对应 `case` 分支。

*   **`src/board.h`**:
    *   定义了所有外设的基地址和寄存器偏移，如 `REG_GPIO_0_DR`, `REG_UART_1_LCR`, `REG_PWM_0_CMP` 等。这些宏用于直接访问硬件寄存器。

*   **动作实现**:
    *   动作通过 `set_all_sg90_degree(fr, fl, bl, br)` 函数组合实现，通过 `delay_ms()` 控制动作节奏。
    *   步态算法主要通过调整 4 个舵机的相位差来实现前进、后退和转向。

## 注意事项 (Notes)

*   **电源**: 4 个舵机同时工作电流较大，确保电源供应充足，避免拉低 MCU 电压导致复位。
*   **舵机校准**: 代码中存在 `cmp_value` 的计算公式 `(180 - degree) * 2000 / 180 + 17500`，这与具体的机械安装结构有关。如需修改机械结构，可能需要重新校准此公式。
