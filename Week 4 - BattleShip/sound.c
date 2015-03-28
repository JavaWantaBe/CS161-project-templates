#include "sound.h"

#define C  523
#define CD 554
#define D  587
#define DE 622
#define E  659
#define F  698
#define FG 739
#define G  783
#define GA 830
#define A  880
#define AB 932
#define B  987

static void play_note( int note, int duration );
static void play_start( void );
static void play_end( void );
static void play_loose( void );
static void play_win( void );
static void play_hit( void );
static void play_miss( void );

/********************
 *  Private Functions
 *******************/
static void play_note( int note, int duration )
{
    Sound_Play( note, duration );
}

static void play_start()
{
    Delay_ms( 2000 );
}

static void play_end()
{
    Delay_ms( 2000 );
}

static void play_loose()
{
    Delay_ms( 2000 );
}

static void play_win()
{
    Delay_ms( 2000 );
}

static void play_hit()
{
    Delay_ms( 2000 );
}

static void play_miss()
{
    Delay_ms( 2000 );
}

/********************
 *  Public Functions
 *******************/
void sound_battle_init()
{
    Sound_Init( &PORTB, 4 );
}

void sound_player( unsigned int melody )
{
    switch( melody )
    {
        case SOUND_START:
            play_start();
            break;
        case SOUND_END:
            play_end();
            break;
        case SOUND_LOOSE:
            play_loose();
            break;
        case SOUND_WIN:
            play_win();
            break;
        case SOUND_HIT:
            play_hit();
            break;
        case SOUND_MISS:
            play_miss();
            break;
    }
}