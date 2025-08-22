# STM32 NUCLEO-F411RE Firmware Build Instructions

## Requirements
- SEGGER Embedded Studio (SES) for ARM
- STM32Cube HAL library for STM32F4 series
- ST-LINK programmer/debugger

## Steps
1. Open SEGGER Embedded Studio.
2. Create a new project for STM32F411RE (or use STM32CubeMX to generate initialization code, then import to SES).
3. Add `Room_Monitor.c` to your project source files.
4. Ensure the HAL drivers are included in your project (stm32f4xx_hal_*.c/h).
5. Configure the project to use the correct MCU (STM32F411RE) and clock settings.
6. Build the project (Project > Build Solution).
7. Connect your NUCLEO board via ST-LINK.
8. Download the firmware (Project > Download & Debug).

## Notes
- Adjust the ADC channel and UART pins if your hardware wiring differs.
- Use STM32CubeMX for easier peripheral configuration if needed.
