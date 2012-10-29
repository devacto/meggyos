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
    snake->length = 1;
    snake->dir = None;
    snake->life = 3;
}

void welcomeRingTone(uint16_t sound)
{
    uint8_t tmp = sound % 9;
    switch (sound) {
        case 0: playTone(ToneF3, 40); break;
        case 1: playTone(ToneE3, 30); break;
        case 2: playTone(ToneD3, 35); break;
        case 3: playTone(ToneC4, 40); break;
        case 4: playTone(ToneG4, 30); break;
        case 5: playTone(ToneF4, 50); break;
        default: break;
    }
}

void showSplashScreen(uint16_t cnt)
{
    uint8_t i, j;
    // cnt % 4
    uint8_t rem = cnt % 4;
    enum color_index color1 = yellowIndex, color2 = greenIndex, color3 = blueIndex,
                     color4 = iceIndex;
    
    cleanFrameBuffer();

    // the innermost circle of lights
    if (rem == 0) {
        for (i = 3; i <= 4; ++i) {
            for (j = 3; j <= 4; ++j) {
                drawPixel(j, i, color1);
            }
        }
    // the second circle of lights
    } else if (rem == 1) {
        for (i = 2; i <= 5; ++i) {
            for (j = 2; j <= 5; ++j) {
                if (i == 2 || i == 5 || j ==2 || j == 5) {
                    drawPixel(j, i, color2);
                }
            }
        }
    // third
    } else if (rem == 2) {
        for (i = 1; i <= 6; ++i) {
            for (j = 1; j <= 6; ++j) {
                if (i == 1 || i == 6 || j == 1 || j == 6) {
                    drawPixel(j, i, color3);
                }
            }
        }
    // the outermost circle of lights
    } else {
        for (i = 0; i <= 7; ++i) {
            for (j = 0; j <= 7; ++j) {
                if (i == 0 || i == 7 || j == 0 || j == 7) {
                    drawPixel(j, i, color4);
                }
            }
        }
    }
    // write to the slate
    drawFrameBuffer();
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

    // write to the slate
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

void checkCollision(Gamestage* stage, Snake* snake, Fruit* fruit)
{
    uint8_t i;
    uint8_t tmpLifePt;
    
    // compare the coorinate of the head to each element of the body
    for (i = 0; i < snake->bodyShown; ++i) {
        if (snake->x == snake->body[i].x && snake->y == snake->body[i].y) {
            playTone(ToneD7, 5);
            // every time it collides, life point decrements by 1
            // as soon as it reaches 0, the game will be over
            snake->life--;
            if (snake->life == 0) {
                *stage = Over;
            } else {
                *stage = Ongoing;
                // since snakeInit will reset the life point to 3, we may first 
                // store it in a tmp and the assigns it back
                tmpLifePt = snake->life;
                snakeInit(snake);
                snake->life = tmpLifePt;
                fruitInit(fruit, snake);
            }
            break;
        }
    }
}
