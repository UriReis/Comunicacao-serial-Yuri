#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "inter.h"
#include "inicializacao.h"

bool led_onR = false;
bool led_onY = false;
bool led_onG = false;

void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento (em microssegundos)
    static volatile uint32_t last_timeB = 0; // Armazena o tempo do último evento (em microssegundos)

    if (gpio == botao_pinA) // Verifica se o botão A foi apertado
    {
        if (current_time - last_timeA > 200000)
        { // Debouncing de 200ms
            last_timeA = current_time;
            led_onG=!led_onG;
            gpio_put(PIN_G,led_onG);

        }
    }
    else if (gpio == botao_pinB) // Verifica se o botão B foi apertado
    {
        if (current_time - last_timeB > 200000)
        {
            last_timeB = current_time;
            led_onY=!led_onY;
            gpio_put(PIN_Y,led_onY);
            
        }
    }
}

void inter()
{

    // Chamada da interrupção para os dois botões:
    gpio_set_irq_enabled_with_callback(botao_pinA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_pinB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}