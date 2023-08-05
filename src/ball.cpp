// ball.cpp
#include "ball.h"
#include <raylib.h>

Ball::Ball()
{
    x = 540.0f; // centre
    y = 400.0f; // centre
    speedX = 5.0f;
    speedY = 10.0f;
    radius = 15.0f;
    hitPaddle = true;
    countdown = 3;
    moving = false;
    elapsedTime = 0.0f;
    hitFloor= false;
}

void Ball::Reset()
{
    x = 540.0f; // centre
    y = 400.0f; // centre
    speedX = 5.0f;
    speedY = 10.0f;
    radius = 15.0f;
    hitPaddle = true;
    countdown = 3;
    moving = false;
    elapsedTime = 0.0f;
    hitFloor= false;
}

void Ball::Update(Paddle& paddle, Tiles& tiles, int& score) // Pass the paddle as a reference
{
    if(countdown > 0)
    {
        elapsedTime += GetFrameTime();
        if(elapsedTime >= 1.0f)
        {
            countdown--;
            elapsedTime = 0.0f;
            if(countdown == 0)
                moving = true;
        }
        return;
    }

    if(moving)
    {
        x += speedX;
        y += speedY;

        // Check collision with paddle
        if (CheckCollisionCircleRec({x, y}, radius, {(float)paddle.x,(float)paddle.y,(float)paddle.width,(float)paddle.height }))
        {
            speedY = -speedY; // Reverse the ball's vertical direction
            speedX += GetRandomValue(-3, 3); // Add some randomness to the ball's horizontal direction
            hitPaddle = true;
        }

        // Check collision with tiles
        if (hitPaddle) {
            bool collisiondDetected = false;
            for(Tile& tile : tiles.GetTiles())
            {
                if(!tile.destroyed && CheckCollisionCircleRec({x, y}, radius, tile.rect))
                {
                    tile.destroyed = true;
                    score += tile.points;
                    if(!collisiondDetected)
                    {
                        speedY = -speedY; // Reverse the ball's vertical direction
                        collisiondDetected = true;
                    }
                    speedX += GetRandomValue(-3, 3); // Add some randomness to the ball's horizontal direction
                    hitPaddle = false;
                }
            }
        }

        // Check collision with floor
        if (y + radius >= GetScreenHeight())
        {
            hitFloor = true;
            moving = false;
        }

        if (x + radius >= GetScreenWidth() || x - radius <= 0)
            speedX *= -1.0f;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
            speedY *= -1.0f;
    }
}

bool Ball::FloorHit()
{
    if(hitFloor)
        return true;
    return false;
}

void Ball::Draw()
{
    DrawCircle((int)x, (int)y, (int)radius, WHITE);
}