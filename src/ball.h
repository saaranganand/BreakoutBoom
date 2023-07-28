#pragma once
#include "paddle.h" // Include the paddle header file
#include "tiles.h" // Include the tiles header file

class Ball
{
public:
    Ball();
    void Update(Paddle& paddle, Tiles& tiles, int& score); // Add the paddle as a parameter
    void Draw();
    bool FloorHit();

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
};
