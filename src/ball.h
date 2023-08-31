// ball.h
#pragma once
#include "paddle.h" // Include the paddle header file
#include "tiles.h" // Include the tiles header file

class Ball
{
public:
    Ball();
    void Reset();
    void Update(Paddle& paddle, Tiles& tiles, int& score); // Add the paddle as a parameter
    void Draw();
    bool FloorHit();
    void Stop();

private:
    float x;
    float y;
    float speedX;
    float speedY;
    float radius;
    bool hitPaddle;
    int countdown;
    bool moving;
    float elapsedTime;
    bool hitFloor;
    bool sizeIncrease; // Tracks if the ball size increase power-up is active
    float sizeIncreaseTimer; // Timer for the power-up effect
    bool slowdown;          // Tracks if the ball slowdown power-up is active
    float slowdownTimer;    // Timer for the power-up effect
    float originalSpeedX;   // Store the original X speed for restoring
    float originalSpeedY;   // Store the original Y speed for restoring
};
