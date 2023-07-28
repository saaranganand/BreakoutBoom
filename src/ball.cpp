#include "ball.h"
#include <raylib.h>

Ball::Ball()
{
    x = 100.0f;
    y = 100.0f;
    speedX = 5.0f;
    speedY = 10.0f;
    radius = 15.0f;
}

void Ball::Update(Paddle& paddle) // Pass the paddle as a reference
{
    x += speedX;
    y += speedY;

    // Check collision with paddle
    if (CheckCollisionCircleRec({x, y}, radius, {(float)paddle.x,(float)paddle.y,(float)paddle.width,(float)paddle.height }))
    {
        speedY = -speedY; // Reverse the ball's vertical direction
    }

    if (x + radius >= GetScreenWidth() || x - radius <= 0)
        speedX *= -1.0f;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1.0f;
}

void Ball::Draw()
{
    DrawCircle((int)x, (int)y, (int)radius, WHITE);
}
