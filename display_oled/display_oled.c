#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define ssd1306_buffer_length 1024
#define count_of(arr) (sizeof(arr) / sizeof(arr[0]))

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Funções que exibem mensagens no display OLED
void exibir_mensagem(const char* mensagem) {
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);  // Limpa a tela
    ssd1306_draw_string(ssd, 5, 0, mensagem);  // Exibe a mensagem
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    render_on_display(ssd, &frame_area);  // Atualiza o display
}

// Função para o sinal verde
void SinalAberto() {
    exibir_mensagem("SINAL ABERTO - ATRAVESSAR COM CUIDADO");
}

// Função para o sinal amarelo
void SinalAtencao() {
    exibir_mensagem("SINAL DE ATENCAO - PREPARE-SE");
}

// Função para o sinal vermelho
void SinalFechado() {
    exibir_mensagem("SINAL FECHADO - AGUARDE");
}

int main() {
    stdio_init_all();

    // Inicialização do I2C
    i2c_init(i2c1, 400 * 1000);  // 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do SSD1306
    ssd1306_init();

    // Exemplo de lógica do semáforo
    while (true) {
        // Simulação de alternância dos sinais
        SinalAberto();  // Verde
        sleep_ms(5000); // Espera 5 segundos

        SinalAtencao();  // Amarelo
        sleep_ms(2000); // Espera 2 segundos

        SinalFechado();  // Vermelho
        sleep_ms(5000); // Espera 5 segundos
    }

    return 0;
}
