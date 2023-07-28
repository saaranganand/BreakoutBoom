#pragma once

class Paddle
{
public:
    Paddle();
    void Move();
    void Draw();

    int x;
    int y;
    int speedX;
    int speedY;
    int width;
    int height;
};
