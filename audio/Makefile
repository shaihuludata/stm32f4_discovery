# Put your STM32F4 library code directory here
STM_COMMON = ../STM32F4-Discovery_FW_V1.1.0

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=audio

# Put your source files here (or *.c, etc)
SRCS = main.c system_stm32f4xx.c stm32f4xx_it.c waveplayer.c
SRCS +=stm32f4xx_dma.c stm32f4xx_exti.c stm32f4xx_gpio.c stm32f4xx_spi.c stm32f4xx_syscfg.c
SRCS +=stm32f4xx_i2c.c stm32f4xx_dac.c
#  waverecorder.c
SRCS +=stm32f4_discovery.c stm32f4_discovery_lis302dl.c stm32f4_discovery_audio_codec.c
SRCS +=stm32f4xx_rcc.c stm32f4xx_tim.c misc.c
# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s 

#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

vpath %.c \
$(STM_COMMON)/Utilities/STM32F4-Discovery \
$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src \
#$(STM_COMMON)/Libraries/STM32_USB_OTG_Driver/src \
#$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Core/src \
#$(STM_COMMON)/Libraries/STM32_USB_Device_Library/Class/cdc/src

# Include files from STM libraries
CFLAGS += -I.
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

OBJS = $(SRCS:.c=.o)

#######################################################################################

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATHS) $(LIBS)
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	st-flash write $(PROJ_NAME).bin 0x8000000
