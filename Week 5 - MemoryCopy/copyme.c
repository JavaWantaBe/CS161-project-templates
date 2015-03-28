#include <stdint.h>

// Some definitions and globals

typedef struct {
    char first_name[25];
    char last_name[25];
    uint8_t age;
    float gpa;
} student_t;

typedef enum {
    NOT_HAPPY,
    HAPPY,
    SAD,
    MAD,
    FRUSTRATED
} mood_t;

union happy_union {
    uint32_t  big_number;
    uint8_t   little_numbers[4];
    student_t happy_student;
};

void main() 
{
    // Some students
    student_t student1, student2, student3;
    // Array of students
    student_t many_students[10], other_students[5];
    // Array of numbers
    int my_numbers[10], your_numbers[10];
    // Array of moods
    mood_t my_daily_moods[7], your_daily_moods[7];
    // Array of unions
    union happy_union my_unions[4];
    
    UART1_Init( 38400 );
}