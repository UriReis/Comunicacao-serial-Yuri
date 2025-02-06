#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "inter.h"
#include "inicializacao.h"
#include "ssd1306.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

bool led_onR = false;
bool led_onY = false;
bool led_onG = false;

ssd1306_t ssd;

void inii2()
{
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
                                                                  // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    ssd1306_send_data(&ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

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
            led_onG = !led_onG;
            gpio_put(PIN_G, led_onG);

            if (led_onG == true)
            {
                // Atualiza o conteúdo do display com animações
                ssd1306_fill(&ssd, false);                         // Limpa o display
                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10); // Desenha uma string
                ssd1306_draw_string(&ssd, "VERDADEIRO", 20, 30);        // Desenha uma string
                ssd1306_send_data(&ssd);                           // Atualiza o display                       // Atualiza o display
            }
            else
            {
                // Atualiza o conteúdo do display com animações
                ssd1306_fill(&ssd, false); // Limpa o display

                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10); // Desenha uma string
                ssd1306_draw_string(&ssd, "FALSO", 20, 30);        // Desenha uma string
                ssd1306_send_data(&ssd);                           // Atualiza o display
            }
        }
    }
    else if (gpio == botao_pinB) // Verifica se o botão B foi apertado
    {
        if (current_time - last_timeB > 200000)
        {
            last_timeB = current_time;
            led_onY = !led_onY;
            gpio_put(PIN_Y, led_onY);
            if (led_onY == true)
            {
                // Atualiza o conteúdo do display com animações

                ssd1306_fill(&ssd, false); // Limpa o display

                ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
                ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30);   // Desenha uma string
                ssd1306_draw_string(&ssd, "PROF WILTON", 15, 48);   // Desenha uma string
                ssd1306_send_data(&ssd);                            // Atualiza o display
            }
            else
            {
                // Atualiza o conteúdo do display com animações
                ssd1306_fill(&ssd, false); // Limpa o display

                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10); // Desenha uma string
                ssd1306_draw_string(&ssd, "FALSO", 20, 30);        // Desenha uma string
                ssd1306_send_data(&ssd);                           // Atualiza o display
            }
        }
    }
}

void inter() // Chamada da interrupção para os dois botões
{

    gpio_set_irq_enabled_with_callback(botao_pinA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_pinB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}