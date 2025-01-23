# Gerado automaticamente pelo CMake para o Raspberry Pi Pico

cmake_minimum_required(VERSION 3.13)

# Configuração do padrão de linguagem
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
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
        pico_stdlib)

# Incluir diretórios de cabeçalhos (certifique-se de que o diretório "inc" está sendo incluído)
target_include_directories(display_oled PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Gerar arquivos adicionais para o binário
pico_add_extra_outputs(display_oled)
