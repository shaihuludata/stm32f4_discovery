#include "main.h"
#include <stdlib.h>

uint16_t val = 0;

void delay (uint16_t del) {
	for (int i=0; i<5971*del; i++) {
		__asm("nop");
	}
}

void ADC_IRQHandler(void) {
    if (ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
        // Чтение значения АЦП
        val = ADC_GetConversionValue(ADC1);
    }
}

void init_led(void) {
// enable GPIO for PortD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_DeInit(GPIOD);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = LED13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void adc_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

// enable GPIO for PortC
	ADC_DeInit();
// uint32_t ADC_Resolution;
// ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
//	ADC_ResetCalibration(ADC1);
//	while (ADC_GetResetCalibrationStatus(ADC1)) { };
//	ADC_StartCalibration(ADC1);
//	while (ADC_GetCalibrationStatus(ADC1)) { };

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void usart_init(void) {
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_DeInit(GPIOD);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //альтернативная функция ножки
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ножка пуш-пул
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //2 ножка
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	USART_DeInit(USART2);
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;  // | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void usart_send(unsigned char * buf) {
	while (*buf != 0)
		USART_SendData(USART2, *buf++);
}

int main(void) {
//	SystemInit();
	char usart_buf[10];

	init_led();
	adc_init();
	usart_init();

	while (1) {
		delay(500);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_15Cycles);
		ADC_SoftwareStartConv(ADC1);
		itoa(val, usart_buf, 10);
		usart_send((unsigned char *)usart_buf);
		usart_send((unsigned char *)"\r\n");
		LED13_TOGGLE;
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
