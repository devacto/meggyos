#include <inttypes.h>
#include <avr/io.h>

#define SNAKECOLOR greenIndex
#define NORMALFRUITCOLOR iceIndex

typedef enum GAMESTAGE {
    Welcome,
    Over,
    Ongoing
} Gamestage;

typedef enum FRUITTYPE {
    Normal,
    Super
} Fruittype;

// enum type of the diretions that snake is moving towards
typedef enum DIRECTIONS {
    None, 
    Up, 
    Down, 
    Left, 
    Right
} Directions;

typedef struct FRUIT {
    uint8_t x, y;
    Fruittype type;
} Fruit;

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

void eatFruit(Snake*, Fruit*);
void fruitInit(Fruit*, Snake*);
void snakeInit(Snake*);
void displayWelcomePage(Gamestage*, Snake*, Fruit*);
void displayGameOverPage( );
void validateCoordinate(int8_t*);
void updateSnakeLocation(Snake*);
void drawSnake(Snake); 
void checkCollision(Gamestage*, Snake);
