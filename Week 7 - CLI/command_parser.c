#include "command_parser.h"
#include <stddef.h>

command_status_t command_parse( char* process_str, command_t* process )
{
    char *p_tmp = NULL;
    int i = 0;
    
    if( !isalpha( process_str[0] ) || !strchr( process_str, ':' ) )
    {
        return COMMAND_INVALID;
    }
    
    process->command = process_str[0];
    
    p_tmp = strtok( &process_str[2], "," );
    
    while( p_tmp != NULL && i < 3 )
    {
        process->commands[i++] = atoi( p_tmp );
        p_tmp = strtok( 0, "," );
    }

   return COMMAND_VALID;
}