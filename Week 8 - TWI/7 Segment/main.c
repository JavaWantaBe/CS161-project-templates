#include "display.h"

void timer_init( void );

volatile int g_num = 0;
volatile char change_flag = 0;


void main() 
{
    display_init();
    timer_init();

    asm sei;
    
    while( 1 )
    {
        if( change_flag )
        {
            
            if( g_num >= 9999 )
                g_num = 0;

            change_flag = 0;
        }

        display_set( g_num );
    }
}


void timer_init()
{
    TCCR1A = 0x80;
    TCCR1B = 0x0C;
    OCR1AH = 0x7A;
    OCR1AL = 0x11;
    TIMSK |= ( 1 << OCIE1A );
}


//Timer1 Prescaler = 256; Preload = 31249; Actual Interrupt Time = 1
void Timer1Overflow_ISR() org IVT_ADDR_TIMER1_COMPA
{
    g_num++;
    change_flag = 1;
}