# WiFi Room Monitoring System Wiring

## Components
- NUCLEO-F411RE (STM32)
- ESP-12E (ESP8266 DollaTek Shield)
- KY-013 Temperature Sensor (NTC)

## Wiring Diagram

### 1. KY-013 to NUCLEO-F411RE
- KY-013 Signal (middle pin) → NUCLEO A0 (PA0)
- KY-013 VCC (one side pin) → NUCLEO 3.3V
- KY-013 GND (other side pin) → NUCLEO GND

### 2. ESP-12E (ESP8266) to NUCLEO-F411RE
- ESP8266 TX → NUCLEO RX (e.g., PA10, USART1_RX)
- ESP8266 RX → NUCLEO TX (e.g., PA9, USART1_TX)
- ESP8266 GND → NUCLEO GND
- ESP8266 VCC → NUCLEO 3.3V (ensure current is sufficient)
- (Optional) ESP8266 CH_PD/EN → NUCLEO 3.3V

> **Note:** Use a voltage divider or level shifter for NUCLEO TX to ESP8266 RX if NUCLEO uses 5V logic (F411RE is 3.3V, so direct connection is safe).

### 3. PC Connection
- PC connects via WiFi to the same network as ESP8266.

## Block Diagram

```
[KY-013] --A0--> [NUCLEO-F411RE] --UART--> [ESP8266] --WiFi--> [PC]
```

## Summary Table
| Signal         | NUCLEO Pin | ESP8266 Pin | KY-013 Pin |
| -------------- | ---------- | ----------- | ---------- |
| UART TX        | PA9        | RX          |            |
| UART RX        | PA10       | TX          |            |
| 3.3V           | 3.3V       | VCC         | VCC        |
| GND            | GND        | GND         | GND        |
| Analog Input   | PA0 (A0)   |             | Signal     |

