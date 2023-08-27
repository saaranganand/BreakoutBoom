#include <raylib.h>
#include "ball.cpp"
#include "paddle.cpp"
#include "tiles.cpp"

/* WIP - DYNAMIC FULLSCREEN SCALING
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

void GameEnd() // ball hits floor
{
    ClearBackground(BLACK);
    DrawText("Game Over!", GetScreenWidth() / 2 - MeasureText("Game Over!", 40) / 2, GetScreenHeight() / 2 - 40, 40, RED);
    DrawText("Press Enter To Restart.", GetScreenWidth()/2 - MeasureText("Press Enter To Restart.", 30)/2, GetScreenHeight()/2 - 0.9, 30, WHITE);
}

/*
void Victory() // all tiles cleared
{
    ClearBackground(BLACK);
    DrawText("All Tiles Cleared!", GetScreenWidth() / 2 - MeasureText("All Tiles Cleared!", 40) / 2, GetScreenHeight() / 2 - 40, 40, GREEN);
    DrawText("Press Enter To Restart.", GetScreenWidth()/2 - MeasureText("Press Enter To Restart.", 30)/2, GetScreenHeight()/2 - 0.9, 30, WHITE);
}
*/

void DrawScore(int score)
{
    const char* scoreText = TextFormat("Score: %i", score);
    int scoreTextWidth = MeasureText(scoreText, 20);
    DrawText(scoreText, GetScreenWidth() - scoreTextWidth - 10, 10, 20, WHITE);
}

bool gameOver = false;

void StartGame()
{
    const int screenWidth = 1080;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Breakout: Boom");

    Ball ball = Ball();
    Paddle paddle = Paddle();
    Tiles tiles = Tiles();

    int score = 0;

    paddle.Reset();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

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
}

void MainMenu()
{
    // Draw the game logo
    DrawText("Breakout: Boom", GetScreenWidth() / 2 - MeasureText("Breakout: Boom", 40) / 2, GetScreenHeight() / 4 - 40, 40, WHITE);

    // Draw the play button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 200, 50, BLUE);
    DrawText("Play", GetScreenWidth() / 2 - MeasureText("Play", 30) / 2, GetScreenHeight() / 2 - 40, 30, WHITE);

    // Draw the settings button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 10, 200, 50, BLUE);
    DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 30) / 2, GetScreenHeight() / 2 + 20, 30, WHITE);

    // Draw the local leaderboard button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 200, 50, BLUE);
    DrawText("Local Leaderboard", GetScreenWidth() / 2 - MeasureText("Local Leaderboard", 30) / 2, GetScreenHeight() / 2 + 80, 30, WHITE);

    // Draw other buttons or links as needed

    // Check for user input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        // Check if the play button was clicked
        if (CheckCollisionPointRec(mousePos, {(float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 - 50, 200, 50}))
        {
            // Start the game
            StartGame();
        }

        // Check if the settings button was clicked
        if (CheckCollisionPointRec(mousePos, {(float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 + 10, 200, 50}))
        {
            // Open the settings menu
        }

        // Check if the local leaderboard button was clicked
        if (CheckCollisionPointRec(mousePos, {(float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 + 70, 200, 50}))
        {
            // Open the local leaderboard
        }

        // Check other buttons or links as needed
    }
}

int main()
{
    Color black = Color{0, 0, 0, 0};

    const int screenWidth = 1080;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Breakout: Boom");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // if(IsKeyPressed(KEY_F11))
        //     ToggleFullscreenWindow(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(black);

        MainMenu();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
