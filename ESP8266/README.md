# ESP8266 Firmware Build Instructions

## Option 1: ESP8266 RTOS SDK (C)
- Install ESP8266 RTOS SDK (https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/)
- Set up the toolchain and environment variables as per Espressif documentation.
- Place `ESP8266_Room_Monitor.c` in your project `main` directory.
- Update `CMakeLists.txt` or Makefile to include this source file.
- Update WiFi credentials and server IP in the code.
- Build and flash:
  ```sh
  idf.py build
  idf.py -p /dev/ttyUSB0 flash
  ```

## Option 2: Arduino IDE (Recommended for Simplicity)
- Use the Arduino sketch provided earlier (not this C file).
- Install ESP8266 board support in Arduino IDE.
- Select the correct board (e.g., NodeMCU 1.0 or Generic ESP8266).
- Upload via USB UART.

## Notes
- For RTOS SDK, ensure you have the correct drivers and permissions for flashing.
- For Arduino, use the Arduino version of the code for easier setup.
