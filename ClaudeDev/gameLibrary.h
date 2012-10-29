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
    uint8_t    life; // a snake has 3 life points, when it reaches 0 the game is over
} Snake;

void welcomeRingTone(uint16_t); // plays a piece of tone when the machine is turned on
void showSplashScreen(uint16_t); // show splash screen
void eatFruit(Snake*, Fruit*); // the action when snake eats a fruit
void fruitInit(Fruit*, Snake*); // initialize the position of the fruit
void snakeGrow(Snake*); // snake length grows by 1 when eats a fruit
void snakeInit(Snake*); // initialize the position, length etc. of the snake
void displayWelcomePage(Gamestage*, Snake*, Fruit*); // show the screen of 'Hi'
void displayGameOverPage( ); // displays when game is over
void validateCoordinate(int8_t*); // validate the coordinate that is generated 
void updateSnakeLocation(Snake*); // update coordinat of the snake as well as its body
void drawSnake(Snake); // draw snake on the screen
void checkCollision(Gamestage*, Snake*, Fruit*); // check if snake collides with its body
