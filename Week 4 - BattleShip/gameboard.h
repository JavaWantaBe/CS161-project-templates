/**
 * @file gameboard.h
 *
 * @brief Game Board Setup
 *
 * @copyright: (c) Richard Lowe, 1/28/2014
 * @version Revision History:
 *   1.0 - Initial Release
 *
 * Status:
 *   10% completed.
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR 7
 *   Oscillator:      8Mhz
 *   Ext. Modules:
 *   SW:              MikroC 6.0
 *
 * @note
 *   <all that matters>
 */

enum { MISS, HIT, LOOSE };

/**
 *  @brief Initialize New Playing Board
 *
 *  This function randomly generates a multidemensional array.  Targets
 *  are populated with 0s for miss and T's for targets.  When a hit happens
 *  the Ts are replaced with X's.  When all the T's are gone, the player has
 *  won / loss.
 *
 */
void board_init( unsigned int seed );

/**
 *  @brief Function Compares to Board for Hit Verification
 *
 *  @param char coordinate_x - value along x
 *  @param char coordinate_y - value along y
 *
 *  @return char - hit
 *    @retval 1 if hit
 *    @retval 0 if miss
 *
 */
int is_board_hit( char coordinate_x, char coordinate_y );

/**
 *  @brief Resets the board configuration
 *
 *
 */
void board_reset( void );

/**
 *  @brief Gets the HIT count
 *
 */
char board_hit_count( void );