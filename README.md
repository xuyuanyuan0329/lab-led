# **Проект светодиодного индикатора управления Bluetooth**
## **Введение в проект**
Этот проект основан на микроконтроллере STM32 и модуле Bluetooth (например, HC-05/HC-06) для реализации функции дистанционного управления светодиодом через Bluetooth. Модуль Bluetooth связывается с STM32 через последовательный порт и получает инструкции пользователя по управлению состоянием светодиода, включая включение, выключение и переключение.

## **Функция проекта**
1. Связь через последовательный порт Bluetooth: модуль Bluetooth обменивается данными с последовательным портом STM32 (USART).
2. Функция управления светодиодом:
 + «LED ON»: загорается светодиод.
 + «LED OFF»: выключить светодиод.
 + «LED TOGGLE»: переключение состояния светодиода.
3. Прием через последовательный порт на основе прерываний: эффективно получать и анализировать инструкции, отправленные через Bluetooth.

## **Требования к оборудованию**
1. Плата разработки микроконтроллера STM32 (например, STM32F103C8T6).
2. Модуль Bluetooth (например, HC-05/HC-06).
3. Светодиод и токоограничивающий резистор (220 Ом).
4. Перемычки и блок питания (источник питания USB).

## **Аппаратное подключение**
1. Подключение модуля Bluetooth:
 + ВКК → 3,3 В/5 В
 + Земля → Земля
 + TX (Bluetooth) → RX (STM32 USART1_RX)
 + RX (Bluetooth) → TX (STM32 USART1_TX)
2. Подключите светодиод к STM32:
 + Положительный светодиод → вывод STM32 GPIO (например, PA5)
 + катод светодиода → резистор → GND

## **Конфигурация программного обеспечения**
### **1. Настройте контакты GPIO (управление светодиодами)**.
Инициализируйте GPIO в файле main.c:

```c
GPIO_InitTypeDef GPIO_InitStruct;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Включить часы GPIOA

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;            // Выберите контакт PA5
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;     // двухтактный режим вывода
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    // Установить скорость вывода
GPIO_Init(GPIOA, &GPIO_InitStruct);
```

### **2. Настройте USART1 (связь Bluetooth)**.
Инициализируйте последовательный порт для связи Bluetooth со скоростью передачи данных 9600 бод:

```c
USART_InitTypeDef USART_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         // контакт ТХ
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        // контакт RX
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
```

## **Логика кода**
### **1. Основная программа**.
Инициализируйте светодиод и последовательный порт в основной функции и включите прием прерываний:

```c
int main(void) {
    HAL_Init();
    SystemClock_Config();

    LED_Init();       // Инициализация светодиода
    USART1_Init();    // Инициализируйте последовательный порт USART1

    while (1) {
        // Ожидание команды обработки приема прерывания
    }
}
```

### **2. Обработка прерывания приема последовательного порта**.
Получите инструкции, отправленные модулем Bluetooth, разберите и выполните соответствующие операции:

```c

char rx_buffer[10];
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        char received = USART_ReceiveData(USART1);
        static uint8_t i = 0;

        rx_buffer[i++] = received;
        if (received == '\n') {
            rx_buffer[i] = '\0';  // терминатор строки
            i = 0;

            if (strcmp(rx_buffer, "LED ON\n") == 0) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Зажгите светодиод
            } else if (strcmp(rx_buffer, "LED OFF\n") == 0) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Выключить светодиод
            } else if (strcmp(rx_buffer, "LED TOGGLE\n") == 0) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Переключить статус светодиода
            }
        }
    }
}
```

## **Этапы использования**
1. Конструкция оборудования: подключите модуль Bluetooth и STM32 в соответствии со схемой подключения оборудования.
2. Компиляция и запись кода:
 + Используйте STM32CubeIDE для компиляции проекта.
 + Записать код на плату разработки STM32.
3. Конфигурация модуля Bluetooth:
 + Скорость передачи по умолчанию установлена ​​на 9600.
4. Тест:
 + Используйте помощник последовательного порта Bluetooth вашего мобильного телефона (например, приложение Bluetooth Debugging Assistant) для подключения к модулю Bluetooth.
 + Отправить тест команды:
 + «LED ON»: загорается светодиод.
 + «LED OFF»: выключить светодиод.
 + «LED TOGGLE»: переключение состояния светодиода.

