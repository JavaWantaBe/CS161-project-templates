#include "execution.h"
#include "terminal.h"
#include <built_in.h>

void execute_command( command_t* execute_behavior )
{
    switch( execute_behavior->command )
    {
         case 's':
             Sound_Play( execute_behavior->commands[0], execute_behavior->commands[1] );
         break;
         case 'l':
             while( execute_behavior->commands[0] )
             {
                 terminal_put_string( "Lights\r\n" );
                 PORTA ^= 0xff;
                 VDelay_ms( execute_behavior->commands[1] );
                 PORTA ^= 0xff;
                 execute_behavior->commands[0]--;
             }
         break;
         case 'a':
         {
             int adc_value;
             char tmp_txt[7];
             
             DDRA &= ~( 1 << execute_behavior->commands[0] );
             ADC_Init();
             
             adc_value = ADC_Read( execute_behavior->commands[0] );
             DDRA |= ( 1 << execute_behavior->commands[0] );
             
             IntToStr( adc_value, tmp_txt );

             terminal_put_string( Ltrim( tmp_txt ) );
             terminal_put_string( "\r\n" );
             
         }
         break;
         default:
             asm nop;
    }

}