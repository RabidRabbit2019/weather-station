.PHONY: clean

release:
	arm-none-eabi-g++ -c -Wall -Wextra -O2 -flto -s \
	  main.cpp \
	  trace.c \
	  stdio.c \
	  bme280_hwi2c.cpp \
	  st7735.cpp \
	  temp_plus.cpp \
	  temp_minus.cpp \
	  pressure_meter.cpp \
	  humidity.cpp \
	  flag.cpp \
	  weather_font.c \
    utils/zic_utils.cpp \
    font_bmp.c \
	  -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -lnosys \
	  -nostartfiles -ffreestanding -specs=nosys.specs -fno-rtti -fno-exceptions
	arm-none-eabi-g++ -c -Wall -Wextra -Os -s \
	  vectors.cpp \
	  -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -lnosys \
	  -nostartfiles -ffreestanding -specs=nosys.specs -fno-rtti -fno-exceptions
	arm-none-eabi-g++ -flto \
	  vectors.o \
	  main.o \
	  trace.o \
	  stdio.o \
	  bme280_hwi2c.o \
	  st7735.o \
	  weather_font.o \
	  temp_plus.o \
	  temp_minus.o \
	  pressure_meter.o \
	  humidity.o \
	  flag.o \
    zic_utils.o \
    font_bmp.c \
	  -Wl,-gc-sections -mcpu=cortex-m3 -mthumb -lnosys -nostartfiles -ffreestanding \
	  -specs=nosys.specs -TSTM32F103C8Tx_FLASH.ld -o a.elf

debug:
	arm-none-eabi-g++ -c -Wall -Wextra -O0 -g \
	  vectors.cpp \
	  main.cpp \
	  trace.c \
	  stdio.c \
	  bme280_hwi2c.cpp \
	  radiomodem.cpp \
	  st7735.cpp \
	  fonts.c \
	  temp_plus.cpp \
	  temp_minus.cpp \
	  pressure_meter.cpp \
	  humidity.cpp \
	  flag.cpp \
    utils/zic_utils.cpp \
	  -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -lnosys -nostartfiles \
	  -ffreestanding -specs=nosys.specs -fno-rtti -fno-exceptions
	arm-none-eabi-g++ \
	  vectors.o \
	  main.o \
	  trace.o \
	  stdio.o \
	  bme280_hwi2c.o \
	  radiomodem.o \
	  st7735.o \
	  fonts.o \
	  temp_plus.o \
	  temp_minus.o \
	  pressure_meter.o \
	  humidity.o \
	  flag.o \
    zic_utils.o \
	  -Wl,-gc-sections -mcpu=cortex-m3 -mthumb -lnosys -nostartfiles -ffreestanding \
	  -specs=nosys.specs -TSTM32F103C8Tx_FLASH.ld -o a.elf

clean:
	rm *.elf
	rm *.o
