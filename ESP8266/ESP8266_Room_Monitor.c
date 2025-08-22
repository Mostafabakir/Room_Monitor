/*
 * ESP8266_Room_Monitor.c
 *
 * ESP8266 (ESP-12E) firmware for WiFi Room Monitoring System
 * Receives alarm messages from STM32 via UART and sends them to a PC via TCP/IP.
 *
 * Author: Professional Embedded Engineer
 *
 * Note: This code is for ESP8266 with an RTOS SDK or similar C environment. For Arduino, use the Arduino sketch provided earlier.
 */

#include <stdio.h>
#include <string.h>
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/sockets.h"
#include "uart.h"

#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASS       "YOUR_WIFI_PASSWORD"
#define SERVER_IP       "192.168.1.100" // Replace with your PC's IP
#define SERVER_PORT     5000
#define UART_BAUDRATE   115200
#define UART_NUM        UART1

static void wifi_init(void) {
    struct station_config config;
    wifi_set_opmode(STATION_MODE);
    memset(&config, 0, sizeof(config));
    strcpy((char*)config.ssid, WIFI_SSID);
    strcpy((char*)config.password, WIFI_PASS);
    wifi_station_set_config(&config);
    wifi_station_connect();
    // Wait for connection
    while (wifi_station_get_connect_status() != STATION_GOT_IP) {
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

static void tcp_send_alarm(const char* msg) {
    int sock;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return;
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sock);
        return;
    }
    send(sock, msg, strlen(msg), 0);
    close(sock);
}

static void uart_task(void* pvParameters) {
    char rx_buf[128];
    int idx = 0;
    while (1) {
        if (UART_ReadByte(UART_NUM, (uint8_t*)&rx_buf[idx], 100) == 0) {
            if (rx_buf[idx] == '\n' || idx >= sizeof(rx_buf) - 2) {
                rx_buf[idx+1] = '\0';
                tcp_send_alarm(rx_buf);
                idx = 0;
            } else {
                idx++;
            }
        }
    }
}

void user_init(void) {
    uart_init_new(UART_BAUDRATE, UART_BAUDRATE, UART_NUM);
    wifi_init();
    xTaskCreate(uart_task, "uart_task", 512, NULL, 2, NULL);
}
