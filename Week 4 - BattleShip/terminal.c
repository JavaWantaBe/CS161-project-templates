#include "terminal.h"

// Init function
void terminal_init( unsigned int baud )
{
    // Calculate the USART prescaler
    unsigned long int baud_pre = ( ( Get_Fosc_kHz() * 1000 ) / ( baud * 16UL ) ) -1;
    // Enable recieve and transmit
    UCSRB |= ( 1 << RXEN ) | ( 1 << TXEN );
    // Use standard 8 bit, 1 stop, no parity
    UCSRC |= ( 1 << URSEL ) | ( 1 << UCSZ0 ) | ( 1 << UCSZ1 );
    // Datasheet says to write high value of the prescaler first
    UBRRH = ( baud_pre >> 8 );
    // Write remaining 8 bits of prescaler
    UBRRL = baud_pre;

    //Just for fun, lets see how far we are off with our baud rate
    //baud_error = ( ( Get_Fosc_kHz() * 1000 ) / ( 16 * ( baud_pre + 1 ) ) );
}

// Put char on uart buffer
void terminal_putc( char c )
{
   // While the Data Register Empty flag is 0, wait
   while( !( UCSRA & ( 1 << UDRE ) ) );
   // Buffer free, place the data on the UDR register
   UDR = c;
}

// Put a string on uart
void terminal_put_string( char *s )
{
   while( *s != '\0' )
   {
       terminal_putc( *s++ );
   }
}

// Checks to see if data is on uart buffer
int terminal_has_data()
{
   return ( UCSRA & ( 1 << RXC ) ) ? 1 : 0;
}

// Gets char from uart buffer
char terminal_getc()
{
    // While the USART Receive Complete flag is not 0 wait
    while( !( UCSRA & ( 1 << RXC ) ) );
    // Yeah, got something, lets read it from the UDR register
    return UDR;
}