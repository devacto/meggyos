#include <inttypes.h>
#include <avr/io.h>

#include "gameLibrary.h"
#include "meggyLibrary.h"

void displayWelcomePage(Gamestage* stage)
{
    cleanFrameBuffer( );

    drawPixel(2, 6, iceIndex);
    drawPixel(3, 6, iceIndex);
    drawPixel(4, 6, iceIndex);
    drawPixel(5, 6, iceIndex);
    drawPixel(6, 6, iceIndex);
    drawPixel(2, 3, iceIndex);
    drawPixel(3, 3, iceIndex);
    drawPixel(4, 3, iceIndex);
    drawPixel(5, 3, iceIndex);
    drawPixel(6, 3, iceIndex);
    drawPixel(4, 4, iceIndex);
    drawPixel(4, 5, iceIndex);
    drawPixel(2, 1, iceIndex);
    drawPixel(3, 1, iceIndex);
    drawPixel(4, 1, iceIndex);
    drawPixel(6, 1, iceIndex);

    drawFrameBuffer( );

    checkButtonsPress( );

    if (Button_A || Button_B) {
        *stage = Ongoing;
    }
}

void displayGameOverPage(Gamestage* stage)
{
    cleanFrameBuffer( );

    drawPixel(0, 0, magentaIndex);
    drawPixel(1, 1, magentaIndex);
    drawPixel(2, 2, magentaIndex);
    drawPixel(3, 3, magentaIndex);
    drawPixel(4, 4, magentaIndex);
    drawPixel(5, 5, magentaIndex);
    drawPixel(6, 6, magentaIndex);
    drawPixel(7, 7, magentaIndex);
    drawPixel(7, 0, magentaIndex);
    drawPixel(6, 1, magentaIndex);
    drawPixel(5, 2, magentaIndex);
    drawPixel(4, 3, magentaIndex);
    drawPixel(3, 4, magentaIndex);
    drawPixel(2, 5, magentaIndex);
    drawPixel(1, 6, magentaIndex);
    drawPixel(0, 7, magentaIndex);
    drawPixel(0, 0, magentaIndex);

    drawFrameBuffer( );

    checkButtonsPress( );
    if (Button_A || Button_B) {
        *stage = Welcome;
    }
}

void validateCoordinate(int8_t* x)
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
    validateCoordinate(&snake->x);
    validateCoordinate(&snake->y);
    
    for (i = 0; i < snake->bodyShown; ++i) {
        preX = snake->body[i].x;
        preY = snake->body[i].y;
        snake->body[i].x = tmpX;
        snake->body[i].y = tmpY;
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

void checkCollision(Gamestage* stage, Snake snake)
{
    uint8_t i;

    for (i = 0; i < snake.bodyShown; ++i) {
        if (snake.x == snake.body[i].x && snake.y == snake.body[i].y) {
            playTone(ToneD7, 5);
            *stage = Over;
            break;
        }
    }
}

