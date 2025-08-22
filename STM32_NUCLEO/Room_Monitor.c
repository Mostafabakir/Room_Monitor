/*
 * Room_Monitor.c
 *
 * WiFi Room Monitoring System
 * Hardware: NUCLEO-F411RE + ESP-12E (ESP8266) + KY-013 (NTC)
 * Function: Reads temperature, compares to threshold, sends alarm via UART to ESP8266 for WiFi notification.
 * Author: Professional Embedded Engineer
 */

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

#define TEMP_THRESHOLD_C 30.0f // Adjustable temperature threshold (Celsius)
#define UART_TIMEOUT    100    // UART timeout in ms

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);

// --- Temperature Reading and Conversion ---
static float Read_Temperature_C(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t adc_val = HAL_ADC_GetValue(&hadc1);
    // Convert ADC value to voltage (12-bit ADC, 3.3V ref)
    float voltage = (adc_val / 4095.0f) * 3.3f;
    // KY-013: NTC, approximate conversion (adjust for your sensor)
    float tempC = (voltage - 0.5f) * 100.0f;
    return tempC;
}

// --- Main Application ---
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_ADC1_Init();

    char uart_msg[64];
    float temperature;

    while (1) {
        temperature = Read_Temperature_C();
        if (temperature > TEMP_THRESHOLD_C) {
            snprintf(uart_msg, sizeof(uart_msg), "ALARM: Temp=%.2fC\r\n", temperature);
            HAL_UART_Transmit(&huart1, (uint8_t*)uart_msg, strlen(uart_msg), UART_TIMEOUT);
        }
        HAL_Delay(1000); // 1 second interval
    }
}

// --- Peripheral Initialization Functions ---
void SystemClock_Config(void) {
    // ...existing code for clock config...
}

void MX_GPIO_Init(void) {
    // ...existing code for GPIO init...
}

void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    HAL_ADC_Init(&hadc1);

    sConfig.Channel = ADC_CHANNEL_0; // PA0
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
