/**
 * @file command_parser.h
 *
 * @brief This Library Parses Commands from a String
 *
 * @copyright:
 *   (c) Richard Lowe, 2/19/2014
 * @version Revision History:
 *   1.0 - Initial release
 *
 * Status:
 *   90% completed.>
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR7
 *   Oscillator:      8Mhz
 *   Ext. Modules:
 *   SW:              MikroC v6.0
 *
 * @note
 *   <all that matters>
 */

#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include <stdint.h>

/**
 *  @struct Holds commands parsed from string
 *
 */
typedef struct
{
    char command;             /**< Single char command */
    uint16_t commands[3];     /**< First command */
} command_t;

/**
 *  @enum Status of parse
 */
typedef enum
{
    COMMAND_INVALID = 0,
    COMMAND_VALID,
    COMMAND_NOT_FOUND
} command_status_t;

/**
 *  @brief Command Parser
 *
 *  @param char* process_str - string to be processed
 *  @param command_t* process - struct to hold processed string
 *
 *  @return command_status_t
 *    @retval COMMAND_INVALID - invalid string
 *    @retval COMMAND_VALID   - valid string
 *    @retval COMMAND_NOT_FOUND - Not valid or found
 *
 */
command_status_t command_parse( char* process_str, command_t* process );

#endif