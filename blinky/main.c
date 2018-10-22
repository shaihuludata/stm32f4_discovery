#define USE_STDPERIPH_DRIVER
#include "stm32f4xx.h"

#define DELAY 1000

//Flash orange LED at about 1hz
int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
    __asm("dsb");                         // stall instruction pipeline, until instruction completes, as
                                          //    per Errata 2.1.13, "Delay after an RCC peripheral clock enabling"
    GPIOD->MODER = (1 << 26);             // set pin 13 to be general purpose output

    for (;;) {
		for (int i=0; i<5971*DELAY; i++) {
			__asm("nop");
		}
		GPIOD->ODR ^= (1 << 13);           // Toggle the pin
    }
}
