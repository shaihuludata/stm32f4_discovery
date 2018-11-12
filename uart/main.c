#include "main.h"

int putcharx(int ch) {
while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
USART_SendData(USART2, (uint8_t)ch);
return ch;
}

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitTypeDef PORT_SETUP; //структура настройки ножки
	PORT_SETUP.GPIO_Mode = GPIO_Mode_AF; //альтернативная функция ножки
	PORT_SETUP.GPIO_OType = GPIO_OType_PP; //ножка пуш-пул
	PORT_SETUP.GPIO_Pin = GPIO_Pin_2; //2 ножка
	PORT_SETUP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &PORT_SETUP);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);

	USART_InitTypeDef uart_setup;
	uart_setup.USART_BaudRate = 9600; //скорость 9600
	uart_setup.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //нет контроля потока
	uart_setup.USART_Mode =  USART_Mode_Tx; //только передатчик
	uart_setup.USART_Parity = USART_Parity_No; //без контроля четности
	uart_setup.USART_StopBits = USART_StopBits_1; //1 стоп бит
	uart_setup.USART_WordLength = USART_WordLength_8b; //8 бит данных
	USART_Init(USART2, &uart_setup); //запись структуры

	USART_Cmd(USART2, ENABLE); //включить юарт2

	putcharx('h');
	putcharx('e');
	putcharx('l');
	putcharx('l');
	putcharx('o');

    while(1)
    {
    }
}

void assert_failed(uint8_t* file, uint32_t line) {
	/* User can add his own implementation to
	 * report the file name and line number,
	 * ex: printf("Wrong parameters value:
	 * file %s on line %d\r\n", file, line) */
	/* Infinite loop */
	while (1) {
	}
}
