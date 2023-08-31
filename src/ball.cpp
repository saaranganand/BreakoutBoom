// ball.cpp
#include "ball.h"
#include <raylib.h>
#include <stdlib.h>

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
    sizeIncrease = false;
    sizeIncreaseTimer = 0.0f;
    slowdown = false;
    slowdownTimer = 0.0f;
    originalSpeedX = 0.0f;
    originalSpeedY = 0.0f;
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
    sizeIncrease = false;
    sizeIncreaseTimer = 0.0f;
    slowdown = false;
    slowdownTimer = 0.0f;
    originalSpeedX = 0.0f;
    originalSpeedY = 0.0f;
}

void Ball::Update(Paddle& paddle, Tiles& tiles, int& score)
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

    if (speedX > 8.0f) {
        speedX = 8.0f;
    }
    if (speedY > 15.0f) {
        speedY = 15.0f;
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

                        if (tile.type == POWERUP) 
                        {
                            // play sparkle sound effect and draw shiny stars aroud ball 

                            int powerUpType = GetRandomValue(1, 2);
                            if (powerUpType == 1) // Size increase
                            {
                                sizeIncrease = true;
                                sizeIncreaseTimer = 10.0f;  // Adjust the duration as needed
                                radius = 25.0f;  // Increase the ball size
                            }
                            if (powerUpType == 2) // temp slowdown
                            {
                                slowdown = true;
                                slowdownTimer = 10.0f;  // Adjust the duration as needed
                                originalSpeedX = speedX;
                                originalSpeedY = speedY;
                                speedX *= 0.5f;  // Slow down the ball
                                speedY *= 0.5f;
                            }
                            // Add more power-up types here
                        }
                        if (tile.type == BOMB)
                        {
                            // play boom sound effect and draw explosion
                        }
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
        {
            speedX *= -1.0f;
        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1.0f;
        }
    }

    if(sizeIncrease) // Size powerup timer
    {
        sizeIncreaseTimer -= GetFrameTime();
        if (sizeIncreaseTimer <= 0.0f) 
        {
            sizeIncrease = false;
            radius = 15.0f;  // Restore original ball radius
        }
    }

    if(slowdown) // slowdown timer
    {
        slowdownTimer -= GetFrameTime();
        if (slowdownTimer <= 0.0f) 
        {
            slowdown = false;
            speedX = std::abs(originalSpeedX) * (speedX > 0.0f ? 1.0f : -1.0f);
            speedY = std::abs(originalSpeedY) * (speedY > 0.0f ? 1.0f : -1.0f);
        }
    }
}

bool Ball::FloorHit()
{
    if(hitFloor)
        return true;
    return false;
}

void Ball::Stop()
{
    speedX = 0.0f;
    speedY = 0.0f;
}

void Ball::Draw()
{
    if (sizeIncrease || slowdown)
        DrawCircle((int)x, (int)y, (int)radius, GREEN);
    else
        DrawCircle((int)x, (int)y, (int)radius, WHITE);
}
