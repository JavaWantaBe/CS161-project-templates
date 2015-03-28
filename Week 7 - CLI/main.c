#include <stdint.h>
#include "terminal.h"
#include "command_parser.h"
#include "execution.h"

#define MAX_BUFFER 100

// First, create a struct descriptor that will hold our buffer information
typedef struct {
    char buffer[MAX_BUFFER];  // 100 chars should be enough
    uint8_t index;     // Counter for our index
} uart_buffer_t;

volatile uart_buffer_t rx_buffer;    // Recieve buffer
volatile uint8_t rx_flag;            // Flag for notifying the program we have data

// system initialization prototype
void system_init( void );


void main()
{
    command_t my_command;
    
    system_init();      // Initialize the system
    terminal_put_string( "Enter a Command\r\n" );

    while( 1 )
    {
        if( rx_flag == 1 )
        {
            if( command_parse( rx_buffer.buffer, &my_command ) == COMMAND_VALID )
            {
                 execute_command( &my_command );
            }
            
            terminal_put_string( "Enter a Command\r\n" );
            rx_buffer.index = 0;
            rx_flag = 0;
        }

        /* This puts the fast CPU to sleep.  When a interrupt is triggered,
           it wakes up the cpu.  Runs though the while loop, finds the flag is
           1 and processes the buffer.  When finished it goes back to sleep.
           This gives the program some very large gains in efficiency and
           power reduction */
        asm sleep;
    }
}



// Some implimentations
void system_init()
{
    terminal_init( 38400 );  // Initialize the UART RX and TX to 38400 baud

    /* We are going to be using interrupt driven communications.  For this,
       we need to look up in the datasheet and find the uart register that
       will turn on the RX_complete interrupt. We find that on page 161 */

    UCSRB |= ( 1 << RXCIE );  // Enable RX Interrupts
    asm sei;                  // Enable global interrupts

    Delay_ms( 100 );          // Optional, but gives our UART time to stabilize

    Sound_Init( &PORTD,4 );   // Initialize sound pin
    DDRA = 0xff;              // Port A for LED Outputs
}



/* We need an ISR that will be called when a interrupt is triggered on the
   reception of a byte waiting for us in the UART buffer. */
void rxc_isr() iv IVT_ADDR_USART__RXC ics ICS_AUTO
{
     char tmp_char = UDR;
     
     if( tmp_char == '\r' || rx_buffer.index == MAX_BUFFER - 1 )
     {
        rx_flag = 1;                              // Set the flag
        rx_buffer.buffer[rx_buffer.index] = '\0'; // Terminate the string
        rx_buffer.index = 0;                      // Reset the index
     }
     else
     {
        rx_buffer.buffer[rx_buffer.index++] = tmp_char;
     }

}
