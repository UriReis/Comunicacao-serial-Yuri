#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h" // chamada da biblioteca
#include "inter.h"
#include "inicializacao.h"









int main()
{
    stdio_init_all();
    pio();
    inicializacao();
  


    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
