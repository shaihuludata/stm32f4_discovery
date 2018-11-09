#include "main.h"

uint16_t val = 0;

void ADC_IRQHandler(void) {
    if (ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
        // Чтение значения АЦП
        // Функцию нашел в stm32f10x_adc.h
        val = ADC_GetConversionValue(ADC1);
    };
};

void my_audio_init(void) {
// enable GPIO for PortD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_DeInit(GPIOD);
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure->GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

// enable GPIO for PortC
	ADC_DeInit();
// uint32_t ADC_Resolution;
// ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
// ADC_InitStructure->ADC_NbrOfChannel = 1;
	ADC_InitStructure->ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
//	ADC_ResetCalibration(ADC1);
//	while (ADC_GetResetCalibrationStatus(ADC1)) { };
//	ADC_StartCalibration(ADC1);
//	while (ADC_GetCalibrationStatus(ADC1)) { };

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure->NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure->NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure->NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(NVIC_InitStructure);
}

//void usart_init(void) {
//	USART_Cmd(USART1, ENABLE);
//}

int main(void) {
// SystemInit();
	my_audio_init();

//	usart_init();

	for (;;) {
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_15Cycles);
		ADC_SoftwareStartConv(ADC1);

		GPIOD->ODR ^= (1 << 13);           // Toggle the pin
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
