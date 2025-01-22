#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"


#define ssd1306_buffer_length 1024
#define count_of(arr) (sizeof(arr) / sizeof(arr[0]))

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main() {
    stdio_init_all();

    // Inicialização do I2C
    i2c_init(i2c1, 400 * 1000); // 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do SSD1306
    ssd1306_init();

    // Área de renderização
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // Limpar o display
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Exibir texto no display
    char *text[] = {
        "  Bem-vindos!   ",
        "  Embarcatech   "
    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++) {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    return 0;
}
