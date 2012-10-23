#include <inttypes.h>
#include <avr/io.h>

#include "gameLibrary.h"
#include "meggyLibrary.h"

void fruitInit(Fruit* fruit, Snake* snake)
{
    while (1) {
        // generate coordinate
        fruit->x = (uint8_t)rand( ) % 8;
        fruit->y = (uint8_t)rand( ) % 8;
        // if the point is not occupied by THE HEAD of snake, then break
        // else regenerate it
        if (fruit->x != snake->x || fruit->y != snake->y) {
            break;
        }
    }
    // in the future there might be a super fruit
    fruit->type = Normal;
}

void snakeInit(Snake* snake)
{
    uint8_t i;

    snake->x = (uint8_t)rand( ) % 8;
    snake->y = (uint8_t)rand( ) % 8;
    for (i = 0; i < 2; ++i) {
        snake->body[i].x = snake->x;
        snake->body[i].y = snake->y;
    }
    snake->bodyShown = 0;
    snake->length = 2;
    snake->dir = None;
}

void displayWelcomePage(Gamestage* stage, Snake* snake, Fruit* fruit)
{
    cleanFrameBuffer( );

    // a hi will be displayed
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
        // after pressing, the game will start therefore snake and fruit need to
        // initialized
        *stage = Ongoing;
        snakeInit(snake);
        fruitInit(fruit, snake);
    }
}

void displayGameOverPage(Gamestage* stage)
{
    cleanFrameBuffer( );

    // a cross will show on screen
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

    // if the game has just be started, then nothing need to be updated
    if (snake->dir == None) return ;

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
    
    // update the coordinates of each point of the body
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

void drawFruit(Fruit fruit)
{
    if (fruit.type == Normal) {
        drawPixel(fruit.y, fruit.x, NORMALFRUITCOLOR);
    }
}

void snakeGrow(Snake* snake)
{
    snake->body[snake->length].x = snake->body[snake->length - 1].x;
    snake->body[snake->length].y = snake->body[snake->length - 1].y;
    snake->length++;
}


void eatFruit(Snake* snake, Fruit* fruit)
{
    uint8_t i;
    // check if head reaches the same point as the fruit
    if (snake->x == fruit->x && snake->y == fruit->y) {
        snakeGrow(snake);
        fruitInit(fruit, snake);
    } else {
        // check if the fruit was generated at the same point as any of the
        // point of the body
        for (i = 0; i < snake->bodyShown; ++i) {
            if (snake->body[i].x == fruit->x && 
                snake->body[i].y == fruit->y) {
                snakeGrow(snake);
                fruitInit(fruit, snake);
                break;
            }
        }
    }
}

void checkCollision(Gamestage* stage, Snake snake)
{
    uint8_t i;

    // compare the coorinate of the head to each element of the body
    for (i = 0; i < snake.bodyShown; ++i) {
        if (snake.x == snake.body[i].x && snake.y == snake.body[i].y) {
            playTone(ToneD7, 5);
            *stage = Over;
            break;
        }
    }
}
