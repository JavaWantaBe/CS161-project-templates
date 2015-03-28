/**
 * @file sound.h
 *
 * @brief Sound generator for battleship game
 *
 * @copyright: (c) Richard, 01/28/2014
 * @version Revision History:
 *   .5 - Initialize sound
 *
 * Status: 10% completed
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR v7
 *   Oscillator:      8Mhz
 *   Ext. Modules:
 *   SW:              MikroC v6.0
 *
 * @note
 *   <all that matters>
 */
 
#ifndef _SOUND_H
#define _SOUND_H

/**
 *  @enum Holds melodies available
 *
 */
enum {
  SOUND_START = 0,
  SOUND_END,
  SOUND_LOOSE,
  SOUND_WIN,
  SOUND_HIT,
  SOUND_MISS
};

/**
 *  @brief Initializes sound generator
 *
 */
void sound_battle_init( void );

/**
 *  @brief Play a selected melody
 *
 *  @pre sound_battle_init() must be called previously
 *
 *  @param int melody
 *
 */
void sound_player( unsigned int melody );

#endif