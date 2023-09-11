// paddle.cpp
#include "paddle.h"
#include <raylib.h>

Paddle::Paddle() // spawn the paddle to the bottom center of the screen
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() + 750;
    speedX = 10;
    speedY = 10;
    width = 80;
    height = 20;
    leftArrowPressTime = 0.0f;
    rightArrowPressTime = 0.0f;
}

void Paddle::Reset()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() - 50;
    speedX = 10;
    speedY = 10;
    width = 80;
    height = 20;
    leftArrowPressTime = 0.0f;
    rightArrowPressTime = 0.0f;
}

void Paddle::Move()
{
    if(IsKeyDown(KEY_LEFT) && x > 0)
    {
        x -= speedX;
    }
    if(IsKeyDown(KEY_RIGHT) && x < GetScreenWidth() - width)
    {
        x += speedX;
    }
    /*
    ----------------------------------
    WORK IN PROGRESS: Trying to implement a boost to the paddle's horizontal speed when the left or right arrow key is pressed twice within 0.2 seconds
    ----------------------------------
    if (IsKeyDown(KEY_LEFT) && x > 0)
    {
        if (leftArrowPressTime < 0.2f) // Check if left arrow key was pressed again within 0.2 seconds
            x -= speedX * 2; // Apply a boost to the paddle's horizontal speed
        else
            x -= speedX;
        leftArrowPressTime = 0.0f; // Reset leftArrowPressTime to 0
    } 
    else 
    {
        leftArrowPressTime += GetFrameTime(); // Increment leftArrowPressTime by the frame time each frame
    }

    if (IsKeyDown(KEY_RIGHT) && x < GetScreenWidth() - width)
    {
        if (rightArrowPressTime < 0.2f) // Check if right arrow key was pressed again within 0.2 seconds
            x += speedX * 2; // Apply a boost to the paddle's horizontal speed
        else
            x += speedX;
        rightArrowPressTime = 0.0f; // Reset rightArrowPressTime to 0
    } 
    else 
    {
        rightArrowPressTime += GetFrameTime();
    }
    */
}

void Paddle::Draw()
{
    DrawRectangle(x, y, width, height, BLUE);
}
