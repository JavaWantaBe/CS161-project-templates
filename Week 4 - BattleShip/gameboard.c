#include "gameboard.h"
#include "terminal.h"

#define MAX_BOARD_SIZE 8
#define MAX_SHIPS      8

static char game_board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

/*
 *  Used to generate 2 random numbers representing a x and y location
 */
static int is_game_over( void );

// Returns true if game is over
static int is_game_over()
{
    int i, j;
    int win = 1;
    
    for( i = 0; i < MAX_BOARD_SIZE; i++ )
    {
         for( j = 0; j < MAX_BOARD_SIZE; j++ )
         {
             if( game_board[i][j] == 'T' )
             {
                 win = 0;
             }
         }
    }
    
    return win;
}

// Board Initialization
void board_init( unsigned int seed )
{
    srand( seed );
    board_reset();  // Reset the board
}

// Checks for board hit
int is_board_hit( char coordinate_x, char coordinate_y )
{
   if( game_board[coordinate_x][coordinate_y] == 'T' )
   {
       game_board[coordinate_x][coordinate_y] = 'X';
       
       return( is_game_over() ) ? LOOSE : HIT;
   }
   else
   {
      return MISS;
   }
}

// Reset board
void board_reset( )
{
    int i, j;
    char random_set[2];

    for( i = 0; i < MAX_BOARD_SIZE; i++ )
    {
        for( j = 0; j < MAX_BOARD_SIZE; j++ )
        {
            game_board[i][j] = 0;
        }
    }

    for( i = 0; i < MAX_SHIPS; i++ )
    {
        do
        {
            //srand( ( i + 1 ) + ( j + 1 ) * 3 );
            random_set[0] = rand() & 0x07;
            random_set[1] = rand() & 0x07;
        } while( game_board[random_set[0]][random_set[1]] != 0 );

        game_board[random_set[0]][random_set[1]] = 'T';
    }
}

// Board hit count
char board_hit_count( )
{
    char count = 0;
    int i, j;
    
    for( i = 0; i < MAX_BOARD_SIZE; i++ )
    {
       for( j = 0; j < MAX_BOARD_SIZE; j++ )
       {
           if( game_board[i][j] == 'X' )
           {
               count++;
           }
       }
    }
    
    return count;
}