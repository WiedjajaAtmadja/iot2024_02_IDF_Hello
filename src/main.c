#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define LED_PIN 4

#define UART_PORT_NUM      UART_NUM_0
// #define UART_BAUD_RATE     115200
// #define UART_TX_PIN        GPIO_NUM_1
// #define UART_RX_PIN        GPIO_NUM_3

void app_main() {
    //     const uart_config_t uart_config = {
    //     .baud_rate = UART_BAUD_RATE,
    //     .data_bits = UART_DATA_8_BITS,
    //     .parity    = UART_PARITY_DISABLE,
    //     .stop_bits = UART_STOP_BITS_1,
    //     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    // };

    // Configure UART parameters
    // uart_param_config(UART_PORT_NUM, &uart_config);
    // Set UART pins
    // uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    // Install UART driver
    uart_driver_install(UART_PORT_NUM, 1024 * 2, 0, 0, NULL, 0);

    // Configure the IOMUX register for pad LED_PIN
    esp_rom_gpio_pad_select_gpio(LED_PIN);

    // gpio_pad_select_gpio (LED_PIN);
    // Set the GPIO as a push/pull output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

	while (1) {
        // Toggle the LED state
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
		// printf("Hello World\n");
        const char *message = "Hello World\r\n";
        uart_write_bytes(UART_PORT_NUM, message, strlen(message));

		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}