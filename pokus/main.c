/*
 * pokus.c
 *
 * Created: 12.3.2018 22:44:31
 * Author : fkla
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "lcd.h"
#include "uart.h"
#include <util/delay.h>
#include <string.h>

volatile uint8_t cela_cast = 0;
volatile uint16_t desetinna = 0;
volatile float des_tvar = 0;
char buffer[9], buffer2[9];

int main(void)
{
    /* Replace with your application code */
    uart_init();
	lcd_init(LCD_DISP_ON);
    lcd_clrscr();
	
	ADMUX = (1<<REFS1) | (1<<REFS0);
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
    sei();
    while (1) 
    {
        uart_puts(buffer2);
        uart_putc('\n');
        
        lcd_gotoxy(0,0);
        lcd_puts(buffer);
        lcd_putc(',');
        lcd_puts(buffer2);
        lcd_puts("   ");
        
        _delay_ms(250);
        
    }
}

ISR(ADC_vect)
{
    cli();
    des_tvar = (ADC*1.1)/1023.0;
    cela_cast = des_tvar;
    // 
    desetinna = ((float)des_tvar - (float)cela_cast)*1000;
    
    itoa(desetinna,buffer2,10);
    itoa(cela_cast,buffer,10);
    sei();
}

