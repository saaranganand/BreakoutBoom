// paddle.h
#pragma once

class Paddle
{
public:
    Paddle();
    void Reset();
    void Move();
    void Draw();

    int x;
    int y;
    int speedX;
    int speedY;
    int width;
    int height;

private:
    float leftArrowPressTime;
    float rightArrowPressTime;
};
