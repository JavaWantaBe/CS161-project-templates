/**
 * @file BattleShip.c
 *
 * @brief CS161 Battleship Game.  Uses 2 development boards to play the
 * classic game of battleship.
 *
 * @copyright: (c) Richard Lowe, 1/28/2014
 * @version Revision History:
 *   1.0 - Initial Release
 *
 * Status:
 *   80% completed.
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR 7
 *   Oscillator:      8Mhz
 *   Ext. Modules:    LCD
 *   SW:              MikroC 6.0
 *
 * @note
 *     This is a 2 mcu game.  Linking 2 development boards together to play
 *     a guessing game.
 */

#include "terminal.h"
#include "scoreboard.h"
#include "gameboard.h"
#include "sound.h"

#define NO_BTN  PORTA0
#define YES_BTN PORTA1
#define GO_BTN  PORTA7

#define BUFFER_SIZE 16

/**********************
 *  Globals
 *********************/
// LCD module connections
sbit LCD_RS at PORTA2_bit;
sbit LCD_EN at PORTD6_bit;
sbit LCD_D4 at PORTC4_bit;
sbit LCD_D5 at PORTC5_bit;
sbit LCD_D6 at PORTC6_bit;
sbit LCD_D7 at PORTC7_bit;

sbit LCD_RS_Direction at DDA2_bit;
sbit LCD_EN_Direction at DDD6_bit;
sbit LCD_D4_Direction at DDC4_bit;
sbit LCD_D5_Direction at DDC5_bit;
sbit LCD_D6_Direction at DDC6_bit;
sbit LCD_D7_Direction at DDC7_bit;
// End LCD module connections

/**
 *  @struct USART Buffer
 *
 */
typedef struct
{
    char buffer[BUFFER_SIZE]; // Buffer to hold usart communications
    unsigned char index;      // Index to buffer
} buffer_t;

/**
 *  @enum Defines code received
 *
 */
enum
{
   CODE_ERROR = 0,
   CODE_OK,
   CODE_WIN
};


volatile unsigned int seed;


/***********************
 *  Prototypes
 **********************/

/*
 *  Sets up System Board
 */
static void system_setup( void );

/**
 *  @brief Processes input from opponent
 *
 *  @param unsigned char *command - char array with command in it.
 *
 *  @return code_t - response code from processing command
 *    @retval CODE_OK - Code is valid
 *    @retval CODE_ATTACK -
 *    @retval CODE_WIN -
 *    @retval CODE_LOOSE -
 *
 */
static int process_code( char *command );

static char start_game( void );


/***********************
 *  Implimentations
 **********************/
// Sets up system for play
static void system_setup()
{
    /* LCD Initialization that animates like a 80's computer screen.  Phrase
       is from an 80's game called "War Games" with Mathew Broadrick. */
    Lcd_Init();
    Lcd_Cmd( _LCD_CLEAR );
    Lcd_Cmd( _LCD_CURSOR_OFF );
    
    // Setup buttons and seed generator
    DDRA &= ~( 1 << NO_BTN ) | ( 1 << YES_BTN ) | ( 1 << GO_BTN );
    PORTA &= ~( 1 << NO_BTN ) | ( 1 << YES_BTN ) | ( 1 << GO_BTN );
    // Timer setup
    TCCR0 |= ( 1 << CS02 ) | ( 1 << CS00 );
    TIMSK |= ( 1 << TOIE0 );
    SREG |= ( 1 << SREG_I );
    
    /* TODO: Added Timer2 as timeout timer.  If player doesn't send a value
       within a certain amount of time, you automatically win.
    */
}

// Processes the codes returning from the other player
static int process_code( char *command )
{
    int response_code;
    
    // character , is found in the string then process coordinates
    if( strchr( command, ',' ) != 0 )
    {
        char first = 0, second = 0;
        char number[5] = {0};
        char transmit_string[25], temp_txt[4];
        
        // string copy only the characters from beginning to where it found ,
        strncpy( number, command, ( strchr( command, ',' ) - command ) );
        // convert into int
        first = atoi( Ltrim( number ) );
        // copy the string starting from the , + 1 to number
        strcpy( number, ( strchr( command, ',' ) + 1 ) );
        // convert into int
        second = atoi( Ltrim( number ) );

        switch( is_board_hit( first, second ) )
        {
            case MISS:
                Lcd_Out( 2, 1, "They MISSED!" );
                strcpy( transmit_string, "M" );
                ByteToStr( board_hit_count(), temp_txt );
                strcat( transmit_string, Ltrim( temp_txt ) );
                terminal_put_string( transmit_string );
                break;
            case HIT:
                Lcd_Out( 2, 1, "They HIT US!" );
                strcpy( transmit_string, "H" );
                ByteToStr( board_hit_count(), temp_txt );
                strcat( transmit_string, Ltrim( temp_txt ) );
                terminal_put_string( transmit_string );
                break;
            case LOOSE:
                Lcd_Out( 2, 1, "We LOST!    " );
                break;
        }
        
        response_code = CODE_OK;
    }
    else if ( command[0] == 'M' )
    {
        scoreb_set_hits( atoi( &command[1] ) );
        response_code = CODE_OK;
    }
    else if ( command[0] == 'H' )
    {
        scoreb_set_hits( atoi( &command[1] ) );
        response_code = ( scoreb_get_hits() == 8 ) ? CODE_WIN : CODE_OK;
    }
    else
    {
         response_code = CODE_ERROR;
    }
    
    return response_code;
}

// Function asks if they would want to play or not
static char start_game( )
{
    char play = 2;
    
    Lcd_Cmd( _LCD_BLINK_CURSOR_ON );
    Lcd_Out( 1, 1, "Shall " );
    Delay_ms( 750 );
    Lcd_Out( 1, 7, "We " );
    Delay_ms( 750 );
    Lcd_Out( 1, 10, "Play A " );
    Delay_ms( 750 );
    Lcd_Out( 2, 1, "Game?" );
    
    // Menu, want to play or no?
    while( play == 2 )
    {
        if( PINA & ( 1 << NO_BTN ) )
        {
            play = 0;
        }
        else if( PINA & ( 1 << YES_BTN ) )
        {
            play = 1;
        }
    }
    
    Lcd_Cmd( _LCD_CLEAR );      // Start LCD with clean screen
    Lcd_Cmd( _LCD_CURSOR_OFF );

    switch( play )
    {
        case 0:
           sound_player( SOUND_END );
           break;
        case 1:
           Lcd_Out( 1, 1, "Generating Board" );
           terminal_init( 38400 );  // Initialize communication system
           scoreb_init();           // Initialize the scoreboard
           sound_battle_init();     // Initialize sound
           board_init( seed );
           sound_player( SOUND_START );
           break;
    }
    
    Lcd_Cmd( _LCD_CLEAR );
    return play;
}



void main() 
{
    char read_char, game_play = 0;
    buffer_t rx_buffer;            // Buffer to hold uart communications
    
    system_setup();
    game_play = start_game();
    
    /*Play the game until game_end is true */
    while( game_play == 1 )
    {
        if( terminal_has_data() )
        {
           read_char = terminal_getc();

           if( read_char != 'E' )
           {
               /* Check to see if we are at the end of the buffer.  If it is
                  at the end, then terminate the buffer with a string terminator
                  and process what we have in the buffer */
               if( rx_buffer.index == BUFFER_SIZE - 1 )
               {
                   rx_buffer.buffer[rx_buffer.index] = '\0';
                   rx_buffer.index = 0;       // Reset the buffer
                   
                   if( process_code( rx_buffer.buffer ) == CODE_WIN )
                   {
                       Lcd_Cmd( _LCD_CLEAR );
                       Lcd_Out( 1, 1, "We Win" );
                       game_play = 0;
                   }
               }
               else
               {
                   rx_buffer.buffer[rx_buffer.index++] = read_char;
               }
           }
           else
           {
               rx_buffer.buffer[rx_buffer.index] = '\0';
               rx_buffer.index = 0;           // Reset the buffer
               // if process code is CODE_WIN we WIN!
               if( process_code( rx_buffer.buffer ) == CODE_WIN )
               {
                   Lcd_Cmd( _LCD_CLEAR );
                   Lcd_Out( 1, 1, "We Win" );
                   game_play = 1;
               }
           }
        }

        if( Button( &PINA, GO_BTN, 80, 1 ) )
        {
            char response[10] = {0};   // Initialize the array to 0
            char temp_txt[4];          // Temporary array for conversions
            
            // Converts byte to str
            ByteToStr( rand() & 0x07, temp_txt );
            // copies to response but first trims off the leading 0s
            strcpy( response, Ltrim( temp_txt ) );
            // Concatenates a comma to split up x and y coordinates
            strcat( response, "," );
            // Convert second byte to str
            ByteToStr( rand() & 0x07, temp_txt );
            // Concatenate that number onto the response minus leading 0s
            strcat( response, Ltrim( temp_txt ) );
            // Our go button for processing
            strcat( response, "E" );
            // Transmit coordinates
            terminal_put_string( response );
        }
    }
    
    TCCR0 &= ~( 1 << CS02 ) | ( 1 << CS00 );
    TIMSK &= ~( 1 << TOIE0 );
    SREG &= ~( 1 << SREG_I );
}


void seed_generator_isr() iv IVT_ADDR_TIMER0_OVF ics ICS_AUTO
{
    seed++;
}