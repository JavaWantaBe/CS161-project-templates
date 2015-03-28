/*!
 * \file
 *
 * \brief USART Modules
 *
 * \copyright:
 *   (c) Richard Lowe, 1/27/2014
 * \version Revision History:
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
 *   \page
 *
 * \note
 *   <all that matters>
 */
 
#ifndef _TERMINAL_H
#define _TERMINAL_H


#include <stdint.h>

/*!
 *  \brief Inializes the USART
 *
 *  \param uint16_t baud - specified baud rate for USART
 *
 */
void terminal_init( uint16_t baud );

/*!
 *  \brief Puts single char on USART buffer
 *
 *  \pre USART needs to be initialized before use.
 *
 *  \param unsigned char c - byte to be sent
 *
 */
void terminal_putc( unsigned char c );

/*!
 *  \brief Places a string on the USART
 *
 *  \param unsigned char *s - string to be placed on USART
 *
 */
void terminal_put_string( unsigned char* s );

/*!
 *  \brief Reads if data is on USART buffer
 *
 *
 *  \return uint8_t - data on buffer
 *    \retval 1 = data available on buffer
 *    \retval 0 = no data available on buffer
 *
 */
uint8_t terminal_has_data( void );

/*!
 *  \brief Gets byte from USART buffer if available
 *
 *  \pre USART needs to be initialized before use.
 *
 *  \return unsigned char - data retrieved from buffer
 *    \retval 'C'
 *
 */
unsigned char terminal_getc( void );



#endif