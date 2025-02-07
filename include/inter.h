#ifndef INTER_H
#define INTER_H



void inter();
void gpio_irq_handler(uint gpio, uint32_t events);
void inii2();
void display(const char *tecla,int x, int y);


#endif