#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#define LED_BLUE_ON   GPIOD->BSRRL = GPIO_Pin_15;
#define LED_BLUE_OFF  GPIOD->BSRRH = GPIO_Pin_15;

uint32_t ADC_VAL[100];

GPIO_InitTypeDef * GPIO_InitStructure;
NVIC_InitTypeDef * NVIC_InitStructure;
// DMA_InitTypeDef * dma_InitStructure;
ADC_InitTypeDef * ADC_InitStructure;
