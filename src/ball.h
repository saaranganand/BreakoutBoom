#pragma once
#include "paddle.h" // Include the paddle header file

class Ball
{
public:
    Ball();
    void Update(Paddle& paddle); // Add the paddle as a parameter
    void Draw();

private:
    float x;
    float y;
    float speedX;
    float speedY;
    float radius;
};
