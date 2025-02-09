#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "inter.h"
#include "inicializacao.h"
#include "ssd1306.h"

// Definições para o I2C e endereço do display OLED
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Variáveis para controlar o estado dos LEDs
bool led_onR = false;
bool led_onY = false;
bool led_onG = false;

// Estrutura para o display SSD1306
ssd1306_t ssd;

// Função de tratamento de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos para debouncing
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento do botão A
    static volatile uint32_t last_timeB = 0; // Armazena o tempo do último evento do botão B

    if (gpio == botao_pinA) // Verifica se o botão A foi pressionado
    {
        if (current_time - last_timeA > 200000) // Debouncing de 200ms
        {
            last_timeA = current_time;
            led_onG = !led_onG; // Alterna o estado do LED verde
            gpio_put(PIN_G, led_onG); // Atualiza o estado físico do LED

            if (led_onG == true)
            {
                // Atualiza o display com o estado do LED verde
                ssd1306_fill(&ssd, false); // Limpa o display
                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10); // Desenha uma string
                ssd1306_draw_string(&ssd, "VERDE", 35, 30);
                ssd1306_draw_string(&ssd, "VERDADEIRO", 20, 50);
                ssd1306_send_data(&ssd); // Atualiza o display
                printf("O estado do led verde foi alterado\n");
            }
            else
            {
                // Atualiza o display com o estado do LED verde (desligado)
                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10);
                ssd1306_draw_string(&ssd, "VERDE FALSO", 15, 30);
                ssd1306_send_data(&ssd);
                printf("O estado do led verde foi alterado\n");
            }
        }
    }
    else if (gpio == botao_pinB) // Verifica se o botão B foi pressionado
    {
        if (current_time - last_timeB > 200000) // Debouncing de 200ms
        {
            last_timeB = current_time;
            led_onY = !led_onY; // Alterna o estado do LED amarelo
            gpio_put(PIN_Y, led_onY); // Atualiza o estado físico do LED

            if (led_onY == true)
            {
                // Atualiza o display com o estado do LED amarelo
                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10);
                ssd1306_draw_string(&ssd, "AZUL", 40, 30);
                ssd1306_draw_string(&ssd, "VERDADEIRO", 15, 50);
                ssd1306_send_data(&ssd);
                printf("O estado do led azul foi alterado\n");
            }
            else
            {
                // Atualiza o display com o estado do LED amarelo (desligado)
                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "ESTADO DO LED", 8, 10);
                ssd1306_draw_string(&ssd, "AZUL FALSO", 15, 30);
                ssd1306_send_data(&ssd);
                printf("O estado do led azul foi alterado\n");
            }
        }
    }
}

// Função para configurar as interrupções dos botões
void inter()
{
    // Habilita as interrupções para os botões A e B
    gpio_set_irq_enabled_with_callback(botao_pinA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_pinB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

// Inicialização do I2C e do display OLED
void inii2()
{
    // Inicializa o I2C com frequência de 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);

    // Configura os pinos SDA e SCL para função I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    // Habilita pull-up nos pinos SDA e SCL
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display SSD1306
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

// Função para exibir texto no display
void display(const char *tecla, int x, int y)
{
    int tamanho = strlen(tecla); // Obtém o tamanho da string
    if (tamanho == 1)
    {
        // Exibe um caractere no display
        ssd1306_draw_string(&ssd, "Caractere:", 30, 20);
        ssd1306_draw_string(&ssd, tecla, x, y);
        ssd1306_send_data(&ssd);
    }
    else
    {
        // Exibe uma string no display
        ssd1306_draw_string(&ssd, tecla, x, y);
        ssd1306_send_data(&ssd);
    }
}

// Função para limpar o display
void limpadisplay()
{
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd); // Atualiza o display
}