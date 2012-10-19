#include <inttypes.h>
#include <avr/io.h>

#include "gameLibrary.h"
#include "meggyLibrary.h"

void displayWelcomePage(Gamestage* stage)
{
    drawPixel(0, 0, iceIndex);
    drawPixel(1, 1, iceIndex);
    drawPixel(2, 2, iceIndex);

    drawFrameBuffer( );

    checkButtonsDown( );

    if (Button_A || Button_B) {
        *stage = Ongoing;
    }
}

void displayGameOverPage( )
{
}

void checkOutOfBound(int8_t* x)
{
    if (*x < 0) {
        *x = 7;
    } else if (*x > 7) {
        *x = 0;
    }
}

void updateSnakeLocation(Snake* snake)
{
    uint8_t i;
    int8_t tmpX = snake->x, tmpY = snake->y;
    int8_t preX, preY;
    // decide the direction that snake is moving towards
    switch (snake->dir) {
        case Up:
            snake->y += 1; break;
        case Down:
            snake->y -= 1; break;
        case Left:
            snake->x += 1; break;
        case Right:
            snake->x -= 1; break;
        default: 
            break;
    }

    // check if it moves out of bound
    checkOutOfBound(&snake->x);
    checkOutOfBound(&snake->y);
    
    for (i = 0; i < snake->bodyShown; ++i) {
        preX = snake->body[i].x;
        preY = snake->body[i].y;
        snake->body[i].x = tmpX;
        snake->body[i].x = tmpY;
        tmpX = preX;
        tmpY = preY;
    }

    if (snake->bodyShown < snake->length) snake->bodyShown++;
}

void drawSnake(Snake snake)
{
    int8_t i;

    drawPixel(snake.y, snake.x, SNAKECOLOR);
    for (i = 0; i < snake.bodyShown; ++i) {
        drawPixel(snake.body[i].y, snake.body[i].x, SNAKECOLOR);
    }
}
