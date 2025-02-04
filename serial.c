#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h" // chamada da biblioteca
#include "ledrgb.h"




const uint botao_pinA = 5; //Pino respectivo ao botão
const uint botao_pinB = 6; //Pino respectivo ao botão




int main()
{
    stdio_init_all();
    pio();
    ledrgb();
  


    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
