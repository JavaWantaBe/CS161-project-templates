#include "scoreboard.h"

#define MIN_DUTY      5000
#define DEFAULT_DUTY  10000
#define MAX_DUTY      19999


static unsigned char enemy_hits;

static void set_duty( unsigned int value );
static void hit( void );

// Private hit function that simulates a hit.
static void hit()
{
    int count = 0;
     
    for( count = 0; count < 8; count++ )
    {
        set_duty( MAX_DUTY );
        Delay_ms( 250 );
        set_duty( MIN_DUTY );
        Delay_ms( 250 );
    }

    set_duty( DEFAULT_DUTY );
}

// Private set_duty function that sets the duty cycle of the PWM
static void set_duty( unsigned int value )
{
   OCR1AH = ( value >> 8 );
   OCR1AL = value;
}


// Public functions

// Initializes scoreboard
void scoreb_init()
{
    // LEDS
    DDRB = 0xFF;
    PORTB = 0xFF;
    Delay_ms( 500 );
    PORTB = 0x00;
    
    

    // PWM Enable 8 prescaler, TOP = 19999, WGM11,12,13
    DDRD |= ( 1 << PORTD5 );
    TCCR1A = ( 1 << COM1A1 ) | ( 1 << WGM11 );
    TCCR1B = ( 1 << CS11 ) | ( 1 << WGM12 ) | ( 1 << WGM13 );
    ICR1H = 0x4E;
    ICR1L = 0x1F;
    
    set_duty( DEFAULT_DUTY );
    enemy_hits = 0;

}

// set the scoreboard display
void scoreb_set_hits( unsigned char score )
{
    if( score > 9 )
    {
        return;
    }
    
    if( score > enemy_hits )
    {
       enemy_hits = score;
       hit();
    }
    
    switch( enemy_hits )
    {
        case 0:
            PORTB = 0x00;
            break;
        case 1:
            PORTB = 0x01;
            break;
        case 2:
            PORTB = 0x03;
            break;
        case 3:
            PORTB = 0x07;
            break;
        case 4:
            PORTB = 0x0F;
            break;
        case 5:
            PORTB = 0x1F;
            break;
        case 6:
            PORTB = 0x3F;
            break;
        case 7:
            PORTB = 0x7F;
            break;
        case 8:
            PORTB = 0xFF;
    }
}

unsigned char scoreb_get_hits()
{
    return enemy_hits;
}