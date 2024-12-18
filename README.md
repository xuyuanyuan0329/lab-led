蓝牙控制 LED 项目
项目简介
本项目基于 STM32 微控制器 和 蓝牙模块（如 HC-05/HC-06），实现通过蓝牙远程控制 LED 的功能。蓝牙模块与 STM32 通过串口通信，接收用户的指令来控制 LED 的状态，包括 开启、关闭 和 切换。

项目功能
蓝牙串口通信：蓝牙模块与 STM32 串口（USART）通信。
LED 控制功能：
"LED ON"：点亮 LED。
"LED OFF"：关闭 LED。
"LED TOGGLE"：切换 LED 状态。
基于中断的串口接收：高效接收和解析蓝牙发送的指令。
硬件需求
STM32 微控制器开发板（如 STM32F103C8T6）。
蓝牙模块（如 HC-05/HC-06）。
LED 与限流电阻（220 欧姆）。
跳线与供电设备（USB 电源）。
硬件连接
蓝牙模块连接：

VCC → 3.3V/5V
GND → GND
TX（蓝牙） → RX（STM32 USART1_RX）
RX（蓝牙） → TX（STM32 USART1_TX）
LED 与 STM32 连接：

LED 正极 → STM32 GPIO 引脚（如 PA5）
LED 负极 → 电阻 → GND
软件配置
1. 配置 GPIO 引脚（LED 控制）
在 main.c 文件中初始化 GPIO：

GPIO_InitTypeDef GPIO_InitStruct;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能 GPIOA 时钟

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;            // 选择 PA5 引脚
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;     // 推挽输出模式
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // 设置输出速度
GPIO_Init(GPIOA, &GPIO_InitStruct);


