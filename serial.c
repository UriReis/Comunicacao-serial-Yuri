#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h" // chamada da biblioteca
#include "inter.h"
#include "inicializacao.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"
#include "include/font.h"



uint8_t led_r = 200; // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 0;   // Intensidade do blue



int main()
{
    stdio_init_all();
    pio();
    inicializacao();
    limpa_led();
    inii2();


    inter();

    

    
    while (true)
    {
        sleep_ms(1000);
        
        if (stdio_usb_connected())
        { // Certifica-se de que o USB está conectado
            char tecla;
           

            if (scanf("%c", &tecla) == 1)
            { // Lê caractere da entrada padrão
                printf("Recebido: '%c'\n", tecla);
               

                switch (tecla)
                {
                case '0':
                    set_one_led(led_r, led_g, led_b, 0);
                    

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

                case ';':
                
                    limpa_led(led_r,led_g, led_r);
                    break;

                default:
                    break;
                }
               
            }
            sleep_ms(1000);
        }
        
    }
}
