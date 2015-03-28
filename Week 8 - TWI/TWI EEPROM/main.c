#include "twi_eeprom.h"

unsigned char saved_presses;

void main() 
{
    DDRA = 0x00;
    DDRB = 0xFF;
    
    twi_eeprom_init();
    
    saved_presses = twi_eeprom_read( 0 );

    while( 1 )
    {
        Delay_ms( 80 );
        PORTB = saved_presses;
        
        if( PINA & 0xFF )
        {
            switch( PINA )
            {
                case 1:
                    saved_presses ^= 0x01;
                break;
                case 2:
                    saved_presses ^= 0x02;
                break;
                case 4:
                    saved_presses ^= 0x04;
                break;
                case 8:
                    saved_presses ^= 0x08;
                break;
                case 16:
                    saved_presses ^= 0x10;
                break;
                case 32:
                    saved_presses ^= 0x20;
                break;
                case 64:
                    saved_presses ^= 0x40;
                break;
                case 128:
                    saved_presses ^= 0x80;
                break;
            }
        
            twi_eeprom_write( 0, saved_presses );
        }
    }
}