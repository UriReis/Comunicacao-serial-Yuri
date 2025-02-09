#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h" // Biblioteca personalizada para manipulação do PIO
#include "inter.h" // Biblioteca para tratamento de interrupções
#include "inicializacao.h" // Biblioteca para inicialização de periféricos
#include "hardware/i2c.h"
#include "include/ssd1306.h" // Biblioteca para manipulação do display OLED
#include "include/font.h" // Fonte para o display OLED

// Definição das cores do LED RGB
uint8_t led_r = 200; // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 0;   // Intensidade do azul

int main()
{
    stdio_init_all(); // Inicializa a comunicação padrão de entrada/saída (necessária para usar printf e scanf)
    pio(); // Configura o PIO (Processador de Entrada/Saída) para comunicação com LEDs
    inicializacao(); // Inicializa os componentes do hardware
    limpa_led(); // Desliga todos os LEDs
    inii2(); // Inicializa a comunicação I2C e configura o display OLED

    inter(); // Configura as interrupções dos botões

    limpadisplay(); // Limpa o display OLED
    display("Esperando", 3, 18); // Exibe a mensagem "Esperando" na tela

    while (true)
    {
        sleep_ms(1000); // Aguarda 1 segundo antes de continuar o loop

        if (stdio_usb_connected())
        { // Verifica se o USB está conectado para comunicação serial
            char tecla;

            if (scanf("%c", &tecla) == 1)
            { // Lê um caractere da entrada padrão (teclado ou comunicação serial)
                printf("Recebido: '%c'\n", tecla); // Exibe o caractere recebido no console

                char caractere[50]; // Declaração do vetor para armazenar o caractere recebido como string
                snprintf(caractere, sizeof(caractere), "%c", tecla); // Converte o caractere em uma string

                limpadisplay(); // Limpa o display OLED
                display(caractere, 64, 32); // Exibe o caractere na tela do OLED
                
                // Verifica qual tecla foi pressionada e aciona o LED correspondente
                switch (tecla)
                {
                case '0':
                    set_one_led(led_r, led_g, led_b, 0); // Acende o LED na posição 0
                    break;

                case '1':
                    set_one_led(led_r, led_g, led_b, 1);
                    break;

                case '2':
                    set_one_led(led_r, led_g, led_b, 2);
                    break;

                case '3':
                    set_one_led(led_r, led_g, led_b, 3);
                    break;

                case '4':
                    set_one_led(led_r, led_g, led_b, 4);
                    break;

                case '5':
                    set_one_led(led_r, led_g, led_b, 5);
                    break;

                case '6':
                    set_one_led(led_r, led_g, led_b, 6);
                    break;

                case '7':
                    set_one_led(led_r, led_g, led_b, 7);
                    break;

                case '8':
                    set_one_led(led_r, led_g, led_b, 8);
                    break;

                case '9':
                    set_one_led(led_r, led_g, led_b, 9);
                    break;

                case ';': // Caso a tecla ";" seja pressionada, todos os LEDs são desligados
                    limpa_led(led_r, led_g, led_r);
                    break;

                default:
                    break; // Caso nenhuma tecla válida seja pressionada, não faz nada
                }
            }
            sleep_ms(1000); // Aguarda 1 segundo antes de continuar o loop
        }
    }
}
