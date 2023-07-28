#include <raylib.h>
#include "ball.h"
#include "paddle.h"

/*
void ToggleFullscreenWindow(int windowWidth, int windowHeight)
{
    if(!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else
    {
        ToggleFullscreen();
        SetWindowSize(windowWidth, windowHeight);
    }
}
*/

int main()
{
    Color black = Color{0, 0, 0, 0};

    const int screenWidth = 1080;
    const int screenHeight = 800;

    Ball ball = Ball();
    Paddle paddle = Paddle();

    InitWindow(screenWidth, screenHeight, "Breakout: Boom");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // if(IsKeyPressed(KEY_F11))
        //     ToggleFullscreenWindow(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(black);
        ball.Update(paddle);
        ball.Draw();
        paddle.Move();
        paddle.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}