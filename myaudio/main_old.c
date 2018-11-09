#include "main.h"

int main(void) {
	SystemInit();

	//enable GPIO for PortD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_DeInit(gpio_InitStructure);
	gpio_InitStructure->GPIO_Pin = GPIO_Pin_15;
	gpio_InitStructure->GPIO_Mode = GPIO_Mode_OUT;
	gpio_InitStructure->GPIO_OType = GPIO_OType_PP;
	gpio_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, gpio_InitStructure);

	//enable GPIO for PortC
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_DeInit(nvic_InitStructure);
	nvic_InitStructure->NVIC_IRQChannel = USART1_IRQn;
	nvic_InitStructure->NVIC_IRQChannelPreemptionPriority = 1;
	nvic_InitStructure->NVIC_IRQChannelSubPriority = 3;
	nvic_InitStructure->NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(nvic_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_DeInit(dma_InitStructure);
	dma_InitStructure->DMA_PeripheralBaseAddr = ;
	dma_InitStructure->DMA_Memory0BaseAddr = (uint32_t) & ADC_VAL;
	dma_InitStructure->DMA_DIR = DMA_DIR_PeripheralToMemory;
	dma_InitStructure->DMA_BufferSize = ;
	dma_InitStructure->DMA_PeripheralInc = DISABLE;
	dma_InitStructure->DMA_Channel = ;
	dma_InitStructure->DMA_MemoryInc = ENABLE;
	dma_InitStructure->DMA_PeripheralBaseAddr = ;
	DMA_Init(dma_InitStructure);
	DMA_Cmd(DMA2, ENABLE);



	ADC_DeInit(adc_InitStructure);
	ADC_Init(adc_InitStructure);
	ADC_Cmd(ADC1, ENABLE);



//	USART_Cmd(USART1, ENABLE);









}
