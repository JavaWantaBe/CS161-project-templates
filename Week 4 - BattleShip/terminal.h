/**
 * @file terminal.h
 *
 * @brief USART module that initizializes uart and facilitates communication
 *
 * @copyright: (c) Richard Lowe, 1/27/2014
 * @version Revision History:
 *   1.0 - Initial Release
 *
 * Status:
 *   Terminal Initialization completed, polled only
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       x
 *   Oscillator:      8Mhz
 *   Ext. Modules:    x
 *   SW:              MikroC 6.0
 *
 *
 * @note
 *   <all that matters>
 */
 
#ifndef _TERMINAL_H
#define _TERMINAL_H

/**
 *  @brief Inializes the USART
 *
 *  @param unsigned int baud - specified baud rate for USART
 *
 */
void terminal_init( unsigned int baud );

/**
 *  @brief Puts single char on USART buffer
 *
 *  @pre USART needs to be initialized before use.
 *
 *  @param unsigned char c - byte to be sent
 *
 */
void terminal_putc( char c );

/**
 *  @brief Places a string on the USART
 *
 *  @param unsigned char *s - string to be placed on USART
 *
 */
void terminal_put_string( char* s );

/**
 *  @brief Reads if data is on USART buffer
 *
 *
 *  @return uint8_t - data on buffer
 *    @retval 1 = data available on buffer
 *    @retval 0 = no data available on buffer
 *
 */
int terminal_has_data( void );

/**
 *  @brief Gets byte from USART buffer if available
 *
 *  @pre USART needs to be initialized before use.
 *
 *  @return unsigned char - data retrieved from buffer
 *    @retval 'C'
 *
 */
char terminal_getc( void );



#endif