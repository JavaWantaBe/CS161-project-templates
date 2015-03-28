/**
 * @file execution.h
 *
 * @brief Executes the Command Passed
 *
 * @copyright:
 *   (c) Richard Lowe, 2/19/2014
 * @version Revision History:
 *   1.0 -
 *
 * Status:
 *   90% completed.
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR7
 *   Oscillator:      8Mhz
 *   Ext. Modules:    x
 *   SW:              MikroC v6.0
 *
 * @note
 *   <all that matters>
 */

#ifndef _EXECUTION_H
#define _EXECUTION_H

#include "command_parser.h"

/**
 *  @brief Executes the Command Passed to it
 *
 *  @param command_t* - command_to_happen
 *
 */
void execute_command( command_t* execute_behavior );

#endif