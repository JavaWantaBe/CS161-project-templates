#include "display.h"

#define DIGIT_1 PORTA &= ~0x0F; PORTA |= 0x01; Delay_ms( 10 );
#define DIGIT_2 PORTA &= ~0x0F; PORTA |= 0x02; Delay_ms( 8 );
#define DIGIT_3 PORTA &= ~0x0F; PORTA |= 0x04; Delay_ms( 5 );
#define DIGIT_4 PORTA &= ~0x0F; PORTA |= 0x08; Delay_ms( 3 );

static const char nums[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void display_init( void )
{
    DDRA = 0x0F;
    DDRC = 0xFF;
    PORTA |= 0x00;
    PORTC = 0x00;
    return;
}

void display_set( unsigned int num )
{
    PORTC = nums[ num % 10 ];
    DIGIT_1;
    
    if( num > 9 )
    {
        PORTC = nums[( num / 10 ) % 10];
        DIGIT_2;
    }
    
    if( num > 99 )
    {
        PORTC = nums[( num / 100 ) % 10];
        DIGIT_3;
    }
    
    if( num > 999 )
    {
        PORTC = nums[( num / 1000 ) % 10];
        DIGIT_4;
    }
    return;
}