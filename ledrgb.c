#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ledrgb.h"




void ledrgb(){
    
    gpio_init(PIN_RED);
    gpio_set_dir(PIN_RED, true);
    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y, true);
    gpio_init(PIN_G);
    gpio_set_dir(PIN_G, true);
    
}