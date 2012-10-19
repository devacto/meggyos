#include <inttypes.h>
#include <avr/io.h>

#define SNAKECOLOR greenIndex

typedef enum GAMESTAGE {
    Welcome,
    Over,
    Ongoing
} Gamestage;

// enum type of the diretions that snake is moving towards
typedef enum DIRECTIONS {
    None, 
    Up, 
    Down, 
    Left, 
    Right
} Directions;

typedef struct BODY {
    int8_t x, y;
} Body;

// Below is the data structures of objects
typedef struct SNAKE
{
    int8_t     x, y;
    Directions dir;
    Body       body[1<<6];
    uint8_t    length;
    uint8_t    bodyShown;
} Snake;

void displayWelcomePage(Gamestage*);
void displayGameOverPage( );
void checkOutOfBound(int8_t*);
void updateSnakeLocation(Snake*);
void drawSnake(Snake); 
