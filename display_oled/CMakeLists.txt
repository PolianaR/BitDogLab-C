# Gerado automaticamente pelo CMake para o Raspberry Pi Pico

cmake_minimum_required(VERSION 3.13)

# Configuração do padrão de linguagem
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuração do Raspberry Pi Pico SDK
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

# Configurações de SDK e ferramentas
set(PICO_SDK_PATH "C:/Users/usuario.p/.pico-sdk/pico-sdk") # Ajuste conforme o local no seu sistema
set(PICO_BOARD pico_w CACHE STRING "Board type")
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Pull in Raspberry Pi Pico SDK (deve vir antes do 'project')
include(pico_sdk_import.cmake)

# Nome do projeto
project(display_oled C CXX ASM)

# Inicializar o SDK
pico_sdk_init()

# Adicionar executável (ajuste para o caminho correto dos arquivos)
add_executable(display_oled 
    display_oled/display_oled.c
    display_oled/inc/ssd1306_i2c.c
)

# Configuração do nome e versão do programa
pico_set_program_name(display_oled "display_oled")
pico_set_program_version(display_oled "0.1")

# Habilitar saída UART/USB
pico_enable_stdio_uart(display_oled 0)
pico_enable_stdio_usb(display_oled 1)

# Adicionar as bibliotecas padrão e de hardware (ex.: I2C)
target_link_libraries(display_oled
        pico_stdlib
        hardware_i2c
)

# Incluir diretórios de cabeçalhos
target_include_directories(display_oled PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/display_oled/inc
)

# Gerar arquivos adicionais para o binário
pico_add_extra_outputs(display_oled)
