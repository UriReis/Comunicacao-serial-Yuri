#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "inicializacao.h"


void inicializacao(){
    // inicialização dos leds rgb:
    gpio_init(PIN_RED);
    gpio_set_dir(PIN_RED, true);
    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y, true);
    gpio_init(PIN_G);
    gpio_set_dir(PIN_G, true);

    // inicialização dos botões:
    gpio_init(botao_pinA);
    gpio_set_dir(botao_pinA, GPIO_IN);
    gpio_pull_up(botao_pinA);

    gpio_init(botao_pinB);
    gpio_set_dir(botao_pinB, GPIO_IN);
    gpio_pull_up(botao_pinB);
}

