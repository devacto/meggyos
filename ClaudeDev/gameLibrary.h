#include <inttypes.h>
#include <avr/io.h>

#define SNAKECOLOR greenIndex
#define NORMALFRUITCOLOR iceIndex

typedef enum GAMESTAGE {
    Welcome,
    Over,
    Ongoing
} Gamestage;

// enum type of the types of fruit, currently only Normal is supported
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

// the element of the body of the snake
typedef struct BODY {
    int8_t x, y;
} Body;

// Below is the data structures of objects
typedef struct SNAKE
{
    int8_t     x, y; // this is the coordinate of the HEAD!!
    Directions dir; // direction the HEAD is moving towards
    Body       body[1<<6];// EXCLUDING the head of snake
    uint8_t    length;
    uint8_t    bodyShown; // the number of elements that has been shown on screen
    uint8_t    life;
} Snake;

void welcomeRingTone();
void showGraphics(uint16_t);
void eatFruit(Snake*, Fruit*);
void fruitInit(Fruit*, Snake*);
void snakeGrow(Snake*);
void snakeInit(Snake*);
void displayWelcomePage(Gamestage*, Snake*, Fruit*);
void displayGameOverPage( );
void validateCoordinate(int8_t*);
void updateSnakeLocation(Snake*);
void drawSnake(Snake); 
void checkCollision(Gamestage*, Snake*, Fruit*);
