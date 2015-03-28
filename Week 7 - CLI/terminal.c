#include "terminal.h"

/*!
 *  \brief Inializes the USART
 *
 *  \param uint16_t baud - specified baud rate for USART
 *
 */
void terminal_init( uint16_t baud )
{
    // Calculate the USART prescaler
    uint32_t baud_pre = ( ( Get_Fosc_kHz() * 1000 ) / ( baud * 16UL ) ) -1;
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

/*!
 *  \brief Puts single char on USART buffer
 *
 *  \pre USART needs to be initialized before use.
 *
 *  \param unsigned char c - byte to be sent
 *
 */
void terminal_putc( unsigned char c )
{
   // While the Data Register Empty flag is 0, wait
   while( !( UCSRA & ( 1 << UDRE ) ) );
   // Buffer free, place the data on the UDR register
   UDR = c;
}

/*!
 *  \brief Places a string on the USART
 *
 *  \param unsigned char *s - string to be placed on USART
 *
 */
void terminal_put_string( unsigned char *s )
{
   while( *s != '\0' )
   {
       terminal_putc( *s++ );
   }
}

/*!
 *  \brief Reads if data is on USART buffer
 *
 *
 *  \return uint8_t - data on buffer
 *    \retval 1 = data available on buffer
 *    \retval 0 = no data available on buffer
 *
 */
uint8_t terminal_has_data()
{
   return ( UCSRA & ( 1 << RXC ) ) ? 1 : 0;
}

/*!
 *  \brief Gets byte from USART buffer if available
 *
 *  \pre USART needs to be initialized before use.
 *
 *  \return unsigned char - data retrieved from buffer
 *    \retval 'C'
 *
 */
unsigned char terminal_getc()
{
    // While the USART Receive Complete flag is not 0 wait
    while( !( UCSRA & ( 1 << RXC ) ) );
    // Yeah, got something, lets read it from the UDR register
    return UDR;
}