// main.cpp
#include <raylib.h>
#include "ball.cpp"
#include "paddle.cpp"
#include "tiles.cpp"

float soundVolume = 0.5f;
float musicVolume = 0.5f;
int difficulty = 3; // Start at medium difficulty

Sound mySound = LoadSound("assets/sounds/boom.wav");
Music myMusic = LoadMusicStream("assets/sounds/boom.wav");
Sound powerupSound = LoadSound("assets/sounds/powerup.wav");

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

void Victory() // all tiles cleared
{
    ClearBackground(BLACK);
    DrawText("All Tiles Cleared!", GetScreenWidth() / 2 - MeasureText("All Tiles Cleared!", 40) / 2, GetScreenHeight() / 2 - 40, 40, GREEN);
    DrawText("Press Enter To Restart.", GetScreenWidth()/2 - MeasureText("Press Enter To Restart.", 30)/2, GetScreenHeight()/2 - 0.9, 30, WHITE);
}

void DrawScore(int score)
{
    const char* scoreText = TextFormat("Score: %i", score);
    int scoreTextWidth = MeasureText(scoreText, 20);
    DrawText(scoreText, GetScreenWidth() - scoreTextWidth - 10, 10, 20, WHITE);
}

bool gameOver = false;

void SettingsMenu()
{
    const int screenWidth = 1080;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "BB: Settings");
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        DrawText("Settings Menu", GetScreenWidth() / 2 - MeasureText("Settings Menu", 40) / 2, GetScreenHeight() / 4 - 40, 40, WHITE);
        
        //Draw sound volume slider
        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 200, 50, BLUE);
        DrawText("Sound Volume", GetScreenWidth() / 2 - MeasureText("Sound Volume", 29) / 2, GetScreenHeight() / 2 - 40, 29, WHITE);
        Rectangle s_vol_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 - 50), 200, 50 };

        //Draw music volume slider
        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 10, 200, 50, BLUE);
        DrawText("Music Volume", GetScreenWidth() / 2 - MeasureText("Music Volume", 29) / 2, GetScreenHeight() / 2 + 20, 29, WHITE);
        Rectangle m_vol_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 + 10), 200, 50 };

        //Draw difficulty slider
        DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 200, 50, BLUE);
        DrawText("Difficulty", GetScreenWidth() / 2 - MeasureText("Difficulty", 30) / 2, GetScreenHeight() / 2 + 80, 30, WHITE);
        Rectangle dif_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 + 70), 200, 50 };

        //Back to Main Menu
        DrawRectangle(10, GetScreenHeight() - 60, 100, 50, BLUE);
        DrawText("Back", MeasureText("Back", 30) / 2 - 10, GetScreenHeight() - 50, 30, WHITE);
        Rectangle set_back_button = { float(10), float(GetScreenHeight() - 60), 200, 50 };

        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, s_vol_button) || CheckCollisionPointRec(mousePos, m_vol_button) || CheckCollisionPointRec(mousePos, dif_button) || CheckCollisionPointRec(mousePos, set_back_button))
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        // Check for user input
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Check if sound volume button was clicked
            if(CheckCollisionPointRec(mousePos, s_vol_button))
            {
                // Calculate the new volume level based on the mouse position.
                soundVolume = (mousePos.x - s_vol_button.x) / s_vol_button.width;
                
                // Make sure the volume is between 0 and 1.
                if (soundVolume < 0) soundVolume = 0;
                if (soundVolume > 1) soundVolume = 1;
                
                // Apply the new volume level to your sounds.
                SetSoundVolume(mySound, soundVolume);
            }
            else if(CheckCollisionPointRec(mousePos, m_vol_button))
            {
                // Calculate the new volume level based on the mouse position.
                musicVolume = (mousePos.x - m_vol_button.x) / m_vol_button.width;
                
                // Make sure the volume is between 0 and 1.
                if (musicVolume < 0) musicVolume = 0;
                if (musicVolume > 1) musicVolume = 1;
                
                // Apply the new volume level to your music.
                SetMusicVolume(myMusic, musicVolume);
            }
            else if (CheckCollisionPointRec(mousePos, dif_button))
            {
                // Calculate the new difficulty level based on the mouse position.
                difficulty = round((mousePos.x - dif_button.x) / dif_button.width * 5);
                
                // Make sure the difficulty is between 1 and 5.
                if (difficulty < 1) difficulty = 1;
                if (difficulty > 5) difficulty = 5;
            }
            else if (CheckCollisionPointRec(mousePos, set_back_button))
            {
                // The back button was clicked.
                // Return to the main menu.
                SetWindowTitle("Breakout: Boom");
                return;
            }
        }
        EndDrawing();
    }

    CloseWindow();
}

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
        if(ball.FloorHit() == true) // game over
        {
            GameEnd();
            if(IsKeyPressed(KEY_ENTER))
            {
                resetGame(ball, paddle, tiles, score);
                gameOver = false;
            }
        }
        if(tiles.Cleared() == true) // victory
        {
            ball.Stop();
            Victory();
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
    /*
    ! PLACEHOLDER ! 
    WIP:
    Change to actual image of game logo once design finished.
    */
    DrawText("Breakout: Boom", GetScreenWidth() / 2 - MeasureText("Breakout: Boom", 40) / 2, GetScreenHeight() / 4 - 40, 40, WHITE);

    // Draw the play button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 200, 50, BLUE);
    DrawText("Play", GetScreenWidth() / 2 - MeasureText("Play", 30) / 2, GetScreenHeight() / 2 - 40, 30, WHITE);
    Rectangle play_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 - 50), 200, 50 };

    // Draw the settings button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 10, 200, 50, BLUE);
    DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 30) / 2, GetScreenHeight() / 2 + 20, 30, WHITE);
    Rectangle settings_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 + 10), 200, 50 };
    
    // Draw the local leaderboard button
    DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 + 70, 300, 50, BLUE);
    DrawText("Local Leaderboard", GetScreenWidth() / 2 - MeasureText("Local Leaderboard", 30) / 2, GetScreenHeight() / 2 + 80, 30, WHITE);
    Rectangle lead_button = { float(GetScreenWidth() / 2 - 150), float(GetScreenHeight() / 2 + 70), 300, 50 };
    
    // Draw other buttons or links as needed

    // Credits:
    DrawText("Created by: ", GetScreenWidth() / 2 - MeasureText("Created by: ", 20) / 2, GetScreenHeight() / 2 + 200, 20, WHITE);
    DrawText("Saarang A. ", GetScreenWidth() / 2 - MeasureText("Saarang A. ", 20) / 2, GetScreenHeight() / 2 + 220, 20, WHITE);

    // Social links using icons from folder:
    // Github:
    DrawRectangle(GetScreenWidth() / 2 - 20, GetScreenHeight() / 2 + 250, 40, 40, BLUE);
    DrawTexture(LoadTexture("src/icons/github-mark.png"), GetScreenWidth() / 2 - 20, GetScreenHeight() / 2 + 250, WHITE);
    Rectangle github_button = { float(GetScreenWidth() / 2 - 20), float(GetScreenHeight() / 2 + 250), 40, 40 };

    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, play_button) || CheckCollisionPointRec(mousePos, settings_button) || CheckCollisionPointRec(mousePos, lead_button) || CheckCollisionPointRec(mousePos, github_button))
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Check for user input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Check if the play button was clicked
        if (CheckCollisionPointRec(mousePos, play_button))
        {
            // Start the game
            StartGame();
        }

        // Check if the settings button was clicked
        else if (CheckCollisionPointRec(mousePos, settings_button))
        {
            // Ideas: Music bar, sound bar, difficulty (number of rows), 
            // Open the settings menu
            SetWindowTitle("BB: Settings");
            SettingsMenu();
        }

        // Check if the local leaderboard button was clicked
        else if (CheckCollisionPointRec(mousePos, lead_button))
        {
            // Open the local leaderboard
        }

        // Check if the github button was clicked
        else if (CheckCollisionPointRec(mousePos, github_button))
        {
            // Open the github page
            OpenURL("https://github.com/saaranganand");
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
        // InitAudioDevice();
        // SetMasterVolume(1.0f);

        BeginDrawing();
        ClearBackground(DARKGREEN);

        MainMenu();

        // UnloadSound(powerupSound);
        // UnloadSound(boomSound);
        // CloseAudioDevice();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
