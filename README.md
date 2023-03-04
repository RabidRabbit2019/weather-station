# weather-station
weather station: blue pill (CKS32F based) + BME280 + ST7735 display 128x160
temperature (degrees Celsius), pressure (mm Hg), humidity (percents)

## connections
BME280: SCL -> B6, SDA -> B7
Display: SCK -> A5, SDA -> A7, AD -> B14, RESET -> B13, CS -> B12

## build
make

## upload using ST-Link
1. openocd
2. gdb-multiarch -x gdb_start.cmd a.elf

## uses
1. https://github.com/RabidRabbit2019/small_images_compress for display compressed images
2. https://github.com/RabidRabbit2019/smooth-bitmap-fonts for display smooth symbols

## example
https://lira39.tk/weather_station_screen.png - link to example screen

## notes
existing openocd.cfg for blue pill board based on CKS32F103C8T6 ucontroller (clone of STM32F103C8T6)

## thanx
to https://github.com/afiskon/stm32-st7735 for ST7735 library
