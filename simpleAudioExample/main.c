#include "main.h"

int main(void) {
	SystemInit();

	fir_8 filt;

	//enables GPIO for PortD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//enables GPIO for PortC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	codec_init();
	codec_ctrl_init();

	I2S_Cmd(CODEC_I2S, ENABLE);
	initFilter(&filt);

    while(1) {
		if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE)) {
			SPI_I2S_SendData(CODEC_I2S, sample);
    		// only update on every second sample to insure that L & R ch.
    		// have the same sample value
    		if (sampleCounter & 0x00000001) {
    			sawWave += NOTEFREQUENCY;
    			if (sawWave > 1.0) sawWave -= 2.0;
    			filteredSaw = updateFilter(&filt, sawWave);
    			sample = (int16_t)(NOTEAMPLITUDE * filteredSaw);
    		}
    		sampleCounter++;
    	}
    	if (sampleCounter == 48000) {
    		LED_BLUE_OFF;
    	} else if (sampleCounter == 96000) {
    		LED_BLUE_ON;
    		sampleCounter = 0;
    	}
    }
}

// a very crude FIR lowpass filter
float updateFilter(fir_8 * filt, float val) {
	uint16_t valIndex;
	uint16_t paramIndex;
	float outval = 0.0;

	valIndex = filt->currIndex;
	filt->tabs[valIndex] = val;
	for (paramIndex=0; paramIndex<8; paramIndex++) {
		outval += (filt->params[paramIndex]) *
				(filt->tabs[(valIndex+paramIndex)&0x07]);
	}
	valIndex++;
	valIndex &= 0x07;
	filt->currIndex = valIndex;
	return outval;
}

void initFilter(fir_8 * theFilter) {
	uint8_t i;
	theFilter->currIndex = 0;
	for (i=0; i<8; i++) theFilter->tabs[i] = 0.0;
	theFilter->params[0] = 0.01;
	theFilter->params[1] = 0.05;
	theFilter->params[2] = 0.12;
	theFilter->params[3] = 0.32;
	theFilter->params[4] = 0.32;
	theFilter->params[5] = 0.12;
	theFilter->params[6] = 0.05;
	theFilter->params[7] = 0.01;
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
