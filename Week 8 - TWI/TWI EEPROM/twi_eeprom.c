#include "twi_eeprom.h"

void twi_eeprom_init()
{
    TWI_Init( 100000 );
    Delay_ms( 100 );
}

void twi_eeprom_write( unsigned char address, unsigned char _data )
{
    TWI_Start();              // issue TWI start signal
    TWI_Write( 0xA2 );        // send byte via TWI (device address + W)
    TWI_Write( address );     // send byte (address of EEPROM location)
    TWI_Write( _data );       // send data (data to be written)
    TWI_Stop();
}

unsigned char twi_eeprom_read( unsigned char address )
{
    unsigned char tmp_data = 0;
    
    TWI_Start();              // issue TWI start signal
    TWI_Write( 0xA2 );          // send byte via TWI (device address + W)
    TWI_Write( address );             // send byte (data address)
    TWI_Start();              // issue TWI signal repeated start
    TWI_Write( 0xA3 );          // send byte (device address + R)
    tmp_data = TWI_Read(0u);     // read data (NO acknowledge)
    TWI_Stop();               // issue TWI stop signal
    
    return tmp_data;
}