#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Definições do display OLED
#define SSD1306_BUFFER_LENGTH 1024
#define COUNT_OF(arr) (sizeof(arr) / sizeof(arr[0]))

// Pinos do I2C
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main() {
    // Inicialização da UART para depuração (opcional)
    stdio_init_all();

    // Inicialização do barramento I2C
    i2c_init(i2c1, 400 * 1000); // Frequência de 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do SSD1306
    if (!ssd1306_init()) {
        printf("Falha ao inicializar o display SSD1306!\n");
        return -1;
    }

    // Configuração da área de renderização
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };

    // Calcular o tamanho do buffer necessário para a renderização
    calculate_render_area_buffer_length(&frame_area);

    // Limpar o display (preencher o buffer com zeros)
    uint8_t ssd[SSD1306_BUFFER_LENGTH];
    memset(ssd, 0, SSD1306_BUFFER_LENGTH);
    render_on_display(ssd, &frame_area);

    // Textos para exibir no display
    char *text[] = {
        "  Bem-vindos!   ",
        "  Embarcatech   "
    };

    // Renderizar os textos no display
    int y = 0; // Coordenada vertical inicial
    for (uint i = 0; i < COUNT_OF(text); i++) {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8; // Avançar para a próxima linha
    }
    render_on_display(ssd, &frame_area);

    while (true) {
        // Loop infinito (necessário em sistemas embarcados)
        tight_loop_contents();
    }

    return 0;
}
