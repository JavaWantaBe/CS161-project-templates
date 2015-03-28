/**
* @file StreetLights.c
*
* @brief Stop Light Signal
*
* @version Revision History:
* .5 - Added button press to increment state
*
* Test configuration:
* MCU: ATMega32
* Dev.Board: EasyAVR 7
* Oscillator: 8Mhz
* Ext. Modules: LEDs on PORTA, PORTB, PORTC
* SW: MikroC 6.0
*
* @note
* SW1.4 in PULLED UP position
* Libraries used: Button
*/


#define SM_RED_LITE PORTA
#define SM_YLW_LITE PORTB
#define SM_GRN_LITE PORTC
#define STATE_CHANGE_BTN PORTD0


/***********************
* Globals
**********************/
unsigned char time_left; // Time spent in each state
volatile unsigned int current_state; // Current state of lights
unsigned char flash_toggle; // Used for flasher state

/**
* @enum Defines states of streetlight
*/
enum {
	SM_STOP, 	/**< State for signal stop */
	SM_WARNING, /**< State for signal warning */
	SM_GO, 	 	/**< State for signal GO */
	SM_FLASHER 	/**< State for signal Flash */
};


/************************
* Prototypes
***********************/
void system_setup( void );
void do_state( void );


/************************
* Implimentation
***********************/
/**
* @brief System setup
*
*/
void system_setup()
{
	SM_RED_LITE = 0xFF; // Set all PORTA to output
	SM_YLW_LITE = 0xFF; // Set all PORTB to output
	SM_GRN_LITE = 0xFF; // Set all PORTC to output
	current_state = SM_STOP; // Initial state is set to STOP
	MCUCR |= ( 1 << ISC01 ) | ( 1 << ISC00 ); // Enable rising edge
	GICR |= ( 1 << INT0 );
	
	// Enable Ext INT0
	asm sei;
	// Global INT enable
	// or ( same thing )
	SREG |= ( 1 << SREG_I );
}

/**
* @brief Handles States
*
* Has different behavior based on what the state of the machine
* is. Turns on and off lights as well has handles a crossing
* warning.
*
*/
void do_state()
{
	switch( current_state )
	{
		case SM_STOP:
			// Red lights are PORTA
			SM_RED_LITE = 0xFF;
			SM_YLW_LITE = 0x00;
			SM_GRN_LITE = 0x00;
		break;
		case SM_WARNING:
			// Yellow lights are PORTB
			SM_RED_LITE = 0x00;
			SM_YLW_LITE = 0xFF;
			SM_GRN_LITE = 0x00;
		break;
		case SM_GO:
			// Green lights are PORTC
			SM_RED_LITE = 0x00;
			SM_YLW_LITE = 0x00;
			SM_GRN_LITE = 0xFF;
		break;
		case SM_FLASHER:
		{
			char count = 8;

			do
			{
				SM_RED_LITE = 0x00;
				SM_YLW_LITE ^= 0xFF;
				SM_GRN_LITE = 0x00;
				Delay_ms( 500 );
			} while( --count > 0 );

			current_state = SM_STOP;
		}
	}
}


// Main
void main()
{
	system_setup();
	
	while( 1 )
	{
		do_state();
		// Button library provides "debouce" for our pressed button
		if( Button( &PIND, STATE_CHANGE_BTN, 80, 1 ) )
		{
			if( current_state == SM_GO )
			{
				current_state = SM_STOP;
			}
			else
			{
				current_state++;
			}
		}
	}
}


/**
* @brief ISR for crosswalk button
*
* @note
* ISR, interrupt sub-routine, runs when external interrupt INT0
* triggered
*/
void crosswalk_isr() iv IVT_ADDR_INT0 ics ICS_AUTO
{
	SREG &= ( 1 << SREG_I ); // Disable global IRQs
	current_state = SM_FLASHER;
	SREG |= ( 1 << SREG_I ); // Enable global IRQs
}