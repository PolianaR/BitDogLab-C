# Gerado automaticamente pelo CMake para o Raspberry Pi Pico

cmake_minimum_required(VERSION 3.13)

# Configuração do padrão de linguagem
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuração do SDK do Raspberry Pi Pico
set(PICO_SDK_PATH "C:/Users/usuario.p/Documents/Rasp/BitDogLab-C/display_oled/pico-sdk")  # Caminho correto do SDK
set(PICO_TOOLCHAIN_PATH "/usr/bin")
include(pico_sdk_import.cmake)

# Nome do projeto
project(display_oled C CXX ASM)

# Inicializar o SDK
pico_sdk_init()

# Adicionar executáveis (ajuste para o caminho correto dos arquivos)
add_executable(display_oled 
    display_oled.c
    inc/ssd1306_i2c.c   # Supondo que o arquivo .c esteja na pasta "inc"
)

# Configuração do nome e versão do programa
pico_set_program_name(display_oled "display_oled")
pico_set_program_version(display_oled "0.1")

# Habilitar saída UART/USB
pico_enable_stdio_uart(display_oled 0)
pico_enable_stdio_usb(display_oled 1)

# Adicionar as bibliotecas padrão
target_link_libraries(display_oled
    pico_stdlib
    pico_binary_info  # Biblioteca pico_binary_info
    hardware_i2c      # Biblioteca para I2C
)

# Incluir diretórios de cabeçalhos (certifique-se de que o diretório "inc" está sendo incluído)
target_include_directories(display_oled PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Gerar arquivos adicionais para o binário
pico_add_extra_outputs(display_oled)
