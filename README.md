# Comunicacao-serial-Yuri

Projeto: Comunicação Serial e Controle de LEDs com RP2040
Aluno: Yuri Silva Reis
Matrícula: TIC370101506

Descrição

Este projeto foi desenvolvido para explorar as interfaces de comunicação serial do microcontrolador RP2040, utilizando a placa BitDogLab. O objetivo foi implementar funcionalidades que envolvem comunicação UART, controle de LEDs endereçáveis WS2812, debouncing de botões e exibição de caracteres em um display OLED SSD1306 via I2C.

Funcionalidades Implementadas

1. Modificação da Biblioteca font.h

Foram adicionadas letras minúsculas ao conjunto de caracteres originais.

Os caracteres foram projetados para manter a estética do display de 8x8 pixels.

2. Entrada de Caracteres via Serial

O monitor serial do VS Code é utilizado para entrada de caracteres.

O caractere digitado é exibido no display SSD1306.

Caso um número de 0 a 9 seja digitado, o LED correspondente na matriz 5x5 WS2812 é ativado e também exibido no display.

3. Interação com Botões

Botão A (GPIO 5)

Alterna o estado do LED verde (GPIO 13).

Exibe uma mensagem no display OLED informando o estado do LED.

Envia uma mensagem para o monitor serial.

Botão B (GPIO 6)

Alterna o estado do LED azul (GPIO 12).

Exibe uma mensagem no display OLED informando o estado do LED.

Envia um log para o monitor serial.

Estrutura do Código

O código está dividido em módulos para facilitar a organização:

serial.c: Arquivo principal que gerencia a comunicação UART, controle de LEDs e display.

biblio.c: Inicialização da matriz WS2812 e PIO, incluindo funções para "pintar" a matriz.

inicializacao.c: Configuração de GPIOs, botões e LEDs.

inter.c: Implementação de interrupções para os botões e debouncing, além ter funções de incialização do display e "escrever" no mesmo.

ssd1306.c e ssd1306.h: Controle do display OLED via I2C.

font.h: Biblioteca de fontes modificada com caracteres minúsculos.


Como Executar

Compilar o código utilizando o SDK do RP2040.

Carregar o binário na placa BitDogLab.

Abrir o monitor serial no VS Code.

Pressionar os botões para verificar a interação com os LEDs.

Digitar caracteres no monitor serial para exibi-los no display OLED.