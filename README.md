# **蓝牙控制 LED 项目**
## **项目简介**
本项目基于 STM32 微控制器 和 蓝牙模块（如 HC-05/HC-06），实现通过蓝牙远程控制 LED 的功能。蓝牙模块与 STM32 通过串口通信，接收用户的指令来控制 LED 的状态，包括 开启、关闭 和 切换。

## **项目功能**
1. 蓝牙串口通信：蓝牙模块与 STM32 串口（USART）通信。
2. LED 控制功能：
  + "LED ON"：点亮 LED。
  + "LED OFF"：关闭 LED。
  + "LED TOGGLE"：切换 LED 状态。
3. 基于中断的串口接收：高效接收和解析蓝牙发送的指令。

## **硬件需求**
1. STM32 微控制器开发板（如 STM32F103C8T6）。
2. 蓝牙模块（如 HC-05/HC-06）。
3. LED 与限流电阻（220 欧姆）。
4. 跳线与供电设备（USB 电源）。

## **硬件连接**
1. 蓝牙模块连接：
   + VCC → 3.3V/5V
   + GND → GND
   + TX（蓝牙） → RX（STM32 USART1_RX）
   + RX（蓝牙） → TX（STM32 USART1_TX）
2. LED 与 STM32 连接：
   + LED 正极 → STM32 GPIO 引脚（如 PA5）
   + LED 负极 → 电阻 → GND

## **软件配置**
### **1. 配置 GPIO 引脚（LED 控制）**
在 main.c 文件中初始化 GPIO：

```c
GPIO_InitTypeDef GPIO_InitStruct;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能 GPIOA 时钟

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;            // 选择 PA5 引脚
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;     // 推挽输出模式
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // 设置输出速度
GPIO_Init(GPIOA, &GPIO_InitStruct);

### **2. 配置 USART1（蓝牙通信）**
初始化串口用于蓝牙通信，波特率为 9600：

```c
USART_InitTypeDef USART_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         // TX 引脚
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        // RX 引脚
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);

USART_InitStructure.USART_BaudRate = 9600;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

USART_Init(USART1, &USART_InitStructure);
USART_Cmd(USART1, ENABLE);

## **代码逻辑**
### **1. 主程序**
在主函数中初始化 LED 和串口，开启中断接收：

```c
int main(void) {
    HAL_Init();
    SystemClock_Config();

    LED_Init();       // 初始化 LED
    USART1_Init();    // 初始化串口 USART1

    while (1) {
        // 等待中断接收处理命令
    }
}

### **2. 串口接收中断处理**
接收蓝牙模块发送的指令，并解析执行对应操作：

```c

char rx_buffer[10];
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        char received = USART_ReceiveData(USART1);
        static uint8_t i = 0;

        rx_buffer[i++] = received;
        if (received == '\n') {
            rx_buffer[i] = '\0';  // 字符串结束符
            i = 0;

            if (strcmp(rx_buffer, "LED ON\n") == 0) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // 点亮 LED
            } else if (strcmp(rx_buffer, "LED OFF\n") == 0) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // 熄灭 LED
            } else if (strcmp(rx_buffer, "LED TOGGLE\n") == 0) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // 切换 LED 状态
            }
        }
    }
}

## **使用步骤**
1. 硬件搭建：按照硬件连接方案连接蓝牙模块与 STM32。
2. 代码编译与烧录：
   + 使用 STM32CubeIDE 编译项目。
   + 将代码烧录到 STM32 开发板。
3. 蓝牙模块配置：
   + 默认波特率设置为 9600。
4. 测试：
   + 使用手机蓝牙串口助手（如 蓝牙调试助手 App）连接蓝牙模块。
   + 发送指令测试：
     + "LED ON"：点亮 LED。
     + "LED OFF"：关闭 LED。
     + "LED TOGGLE"：切换 LED 状态。

