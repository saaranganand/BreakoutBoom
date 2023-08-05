#include <raylib.h>
#include "ball.h"
#include "paddle.h"
#include "tiles.h"

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

void resetGame(Ball& ball, Paddle& paddle, Tiles& tiles, int& score)
{
    ball.Reset();
    paddle.Reset();
    tiles.GenerateTiles();
    score = 0;
}

void GameEnd()
{
    ClearBackground(BLACK);
    DrawText("Game Over!", GetScreenWidth() / 2 - MeasureText("Game Over!", 40) / 2, GetScreenHeight() / 2 - 40, 40, WHITE);
}

void DrawScore(int score)
{
    const char* scoreText = TextFormat("Score: %i", score);
    int scoreTextWidth = MeasureText(scoreText, 20);
    DrawText(scoreText, GetScreenWidth() - scoreTextWidth - 10, 10, 20, WHITE);
}

int main()
{
    Color black = Color{0, 0, 0, 0};

    const int screenWidth = 1080;
    const int screenHeight = 800;

    Ball ball = Ball();
    Paddle paddle = Paddle();
    Tiles tiles = Tiles();

    int score = 0;
    bool gameOver = false;

    InitWindow(screenWidth, screenHeight, "Breakout: Boom");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // if(IsKeyPressed(KEY_F11))
        //     ToggleFullscreenWindow(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(black);
        ball.Update(paddle, tiles, score);
        ball.Draw();
        paddle.Move();
        paddle.Draw();
        tiles.Draw();
        DrawScore(score);
        if(ball.FloorHit() == true)
        {
            gameOver = true;
        }
        if(gameOver == true)
        {
            GameEnd();
            if(IsKeyPressed(KEY_ENTER))
            {
                resetGame(ball, paddle, tiles, score);
                gameOver = false;
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}