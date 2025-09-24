#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 GPIO_NUM_5
#define LED2 GPIO_NUM_18
#define LED3 GPIO_NUM_19
#define LED4 GPIO_NUM_21

#define DELAY_MS 500   


gpio_num_t leds[] = {LED1, LED2, LED3, LED4};


void init_leds() {
    for (int i = 0; i < 4; i++) {
        gpio_reset_pin(leds[i]);
        gpio_set_direction(leds[i], GPIO_MODE_OUTPUT);
        gpio_set_level(leds[i], 0); // Inicia desligado
    }
}


void set_led(int index, int state) {
    gpio_set_level(leds[index], state);
}


void contador_binario() {
    for (int num = 0; num < 16; num++) {
        for (int i = 0; i < 4; i++) {
            int bit = (num >> i) & 0x01;
            set_led(i, bit);
        }
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}


void sequencia_varredura() {
    // Vai para frente
    for (int i = 0; i < 4; i++) {
        set_led(i, 1);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        set_led(i, 0);
    }
    // Volta para trás
    for (int i = 2; i >= 0; i--) {
        set_led(i, 1);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        set_led(i, 0);
    }
}

void app_main() {
    init_leds();

    while (1) {
        contador_binario();     
        sequencia_varredura();  
    }
}
