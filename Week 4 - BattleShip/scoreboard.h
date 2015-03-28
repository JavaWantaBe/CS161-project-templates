/**
 * @file scoreboard.h
 *
 * @brief Score Board - Keeps track of sunken ships
 *
 * @copyright: (c) Richard Lowe, 1/28/2014
 * @version Revision History:
 *   1.0 - Initial release
 *
 * Status:
 *   90% completed.
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR 7
 *   Oscillator:      8Mhz
 *   Ext. Modules:    None
 *   SW:              MikroC 6.0
 *
 * @note
 *   This module keeps track of sunken ships on the PORTB LEDs.  Default is
 *   all off.  As the ships are sunk, they light up.
 */
 
#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

/**
 *  @brief Initializes PORTB Leds for Scoreboard purposes
 *
 *  Also intializes the 16bit timer with FAST PWM mode with a 50hz frequency
 *  and a standard duty cycle of 50%.. When a hit is detected, the duty is
 *  turned up to 100%, delayed, down to 10% several times to simulate a hit.
 *
 */
void scoreb_init( void );

/**
 *  @brief Sets the Scoreboard Count
 *
 *  When a hit happens, increment the count and update the scoreboard.
 *
 *  @pre scoreb_init needs to be called before use.
 *
 *  @param unsigned char score - score of hits
 *
 */
void scoreb_set_hits( unsigned char score );

/**
 *  @brief returns number of hits on scoreboard
 *
 *  @return unsigned char - number of hits
 */
unsigned char scoreb_get_hits( void );

#endif