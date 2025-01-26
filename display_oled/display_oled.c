#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h" // Biblioteca para controle do OLED

#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

// Configuração do display OLED
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
ssd1306_t oled;

#define LED_R_PIN 2
#define LED_G_PIN 3
#define LED_B_PIN 4
#define BTN_A_PIN 5

void init_oled() {
    printf("Inicializando OLED...\n");
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    if (ssd1306_init(&oled, i2c_default, 0x3C, OLED_WIDTH, OLED_HEIGHT)) {
        printf("OLED inicializado com sucesso!\n");
    } else {
        printf("Falha na inicialização do OLED!\n");
    }
    ssd1306_clear(&oled);
    ssd1306_show(&oled);
}

void display_message(const char* message) {
    ssd1306_clear(&oled);
    ssd1306_draw_string(&oled, 0, 0, message, 1);
    ssd1306_show(&oled);
}

void SinalAberto() {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    display_message("SINAL ABERTO - ATRAVESSAR COM CUIDADO");
}

void SinalAtencao() {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    display_message("SINAL DE ATENCAO - PREPARE-SE");
}

void SinalFechado() {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    display_message("SINAL FECHADO - AGUARDE");
}

int WaitWithRead(int timeout_ms) {
    int elapsed = 0;
    while (elapsed < timeout_ms) {
        if (gpio_get(BTN_A_PIN) == 0) {
            return 1;
        }
        sleep_ms(10);
        elapsed += 10;
    }
    return 0;
}

int main() {
    // Inicialização de LEDs e Botão
    printf("Inicializando LEDs e Botão...\n");
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);

    // Inicialização do OLED
    init_oled();

    while (true) {
        SinalAberto();
        int A_state = WaitWithRead(8000);

        if (A_state) {
            SinalAtencao();
            sleep_ms(5000);

            SinalFechado();
            sleep_ms(10000);
        } else {
            SinalAtencao();
            sleep_ms(2000);

            SinalFechado();
            sleep_ms(8000);
        }
    }

    return 0;
}
