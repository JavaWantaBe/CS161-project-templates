#ifndef TWI_EEPROM_H
#define TWI_EEPROM_H

void twi_eeprom_init( void );
void twi_eeprom_write( unsigned char address, unsigned char _data );
unsigned char twi_eeprom_read( unsigned char address );


#endif