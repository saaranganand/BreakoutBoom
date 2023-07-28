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
}

void Paddle::Move()
{
    if (IsKeyDown(KEY_LEFT) && x > 0)
        x -= speedX;
    if (IsKeyDown(KEY_RIGHT) && x < GetScreenWidth() - width)
        x += speedX;
}

void Paddle::Draw()
{
    DrawRectangle(x, y, width, height, WHITE);
}