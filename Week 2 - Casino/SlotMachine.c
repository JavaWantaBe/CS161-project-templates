/**
 * @file slotmachine.c
 *
 * @brief Slot Machine Lab 2
 *
 * @copyright: (c) Richard Lowe, 01/12/2014
 * @version Revision History:
 *   1.0 - Initial release of demo.
 *
 * Test configuration:
 *   MCU:             ATMega32
 *   Dev.Board:       EasyAVR v7
 *   Oscillator:      8Mhz
 *   SW:              MikroC v6.0
 *
 */

#define LED1 0
#define LED2 1
#define LED3 6
#define LED4 7
#define GO_BUTTON 0

#define JACKPOT 3
#define DIME    2
#define NICKEL  1
#define ZERO    0
 
/*
 *  Global Declaration Space
 */
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

unsigned char first, second, third;  // Columns in the slot machine

enum { BAR, BELL, LEMON, CHERRY };   // Values for each kind

char kind[4][8] = {
    "BAR",
    "BELL",
    "LEMN",
    "CHRY"
};

/**************************
 *  Function prototypes
 *************************/
/**
 *  @brief Setup required hardware
 *
 */
void setup_system( void );

/**
 *  @brief Flashes LEDs number of times requested
 *
 *  @pre LEDs and PORT must be setup prior to use.
 *
 *  @param unsigned char n : number of times to flash
 */
void flash_lights( unsigned char n );

/**
 *  @brief Returns the calculated payout
 *
 *  @return unsigned int : value of returned calculation
 *    @retval DIME
 *    @retval JACKPOT
 */
unsigned int get_payout( void );


/*****************************
 *  Function implementations
 ****************************/
void main()
{
    int total_dollars = 0, total_cents = 0; // Hold my money
    unsigned char seed = 0;                 // Seed for random number generator
    char temp_txt[5];                       // Temporary buffer for conversion


    setup_system();                         // Initialize all hardware
    
    // Send a nice intro message
    Lcd_Out( 1, 1, "CS161 Casino" );
    Lcd_Out( 2, 1, "Press B0 to Roll" );

    while( 1 )
    {
        do
        {
            seed++; // While waiting for a push, increase seed
        } while( !PINB & ( 1 << GO_BUTTON ) );

        /*
         * Generate a random number for each of the columns.
         * & by 0x03 to limit the number from 0 to 3
         */
        srand( seed );
        first  = 0x03 & rand();
        second = 0x03 & rand();
        third  = 0x03 & rand();

        Lcd_Cmd( _LCD_CLEAR );  // Clear screen for roll results
        Lcd_Out( 1, 1, "1st   2nd   3rd" );
        Lcd_Out( 2, 1, kind[first] );
        Lcd_Out( 2, 7, kind[second] );
        Lcd_Out( 2, 13, kind[third] );
        
        flash_lights( 5 );

        Lcd_Cmd( _LCD_CLEAR );

        switch( get_payout() )
        {
            case ZERO:
                Lcd_Out( 1, 1, "Sorry, You Loose" );
                break;
            case NICKEL:
                Lcd_Out( 1, 1, "You win a Nickel" );
                total_cents += 5;
                break;
            case DIME:
                Lcd_Out( 1, 1, "You win a Dime" );
                total_cents += 10;
                break;
            case JACKPOT:
                Lcd_Out( 1, 1, "JACKPOT!!!" );
                total_dollars++;
        }

        Delay_ms( 1000 );
        Lcd_Out( 2, 1, "Total $" );
        ByteToStr( total_dollars, temp_txt );
        Lcd_Out( 2, 8, Ltrim( temp_txt ) );
        Lcd_Chr( 2, 9, '.' );
        ByteToStr( total_cents, temp_txt );
        Lcd_Out( 2, 10, Ltrim( temp_txt ) );
        Delay_ms( 2000 );
        Lcd_Out( 1, 1, "Roll->play again" );
    }

}
 
void setup_system()
{
    // Setup LEDs
    DDRA |= ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 );
    // Setup button
    DDRB &= ~( 1 << GO_BUTTON );
    // Setup LCD Display
    Lcd_Init();                        // Initialize LCD
    Lcd_Cmd(_LCD_CLEAR);               // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
}
 
void flash_lights( unsigned char n )
{
    int count;
    
    for( count = 0; count < n; count++ )
    {
        Delay_ms( 500 );
        PORTA |= ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 );
        Delay_ms( 500 );
        PORTA &= ~( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
    }
}

unsigned int get_payout()
{
   /*
    *  Rules:
    *  All cherries == jackpot
    *  One of the columns is Cherry == Dime
    *  If all are alike, then == Nickel
    */
   if( ( first == CHERRY ) && ( second == CHERRY ) && ( third == CHERRY ) )
   {
       return JACKPOT;
   }
   else if( ( first == CHERRY ) || ( second == CHERRY ) || ( third == CHERRY ) )
   {
       return DIME;
   }
   else if( ( first == second ) && ( second == third ) )
   {
       return NICKEL;
   }
   else
   {
       return ZERO;
   }
}
