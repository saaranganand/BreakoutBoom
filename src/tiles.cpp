// tiles.cpp
#include "tiles.h"
#include <cstdlib>
#include <ctime>

Tiles::Tiles() {
    rows = 5;
    columns = 12;
    tileWidth = 86;
    tileHeight = 20;

    GenerateTiles();
}

void Tiles::GenerateTiles() 
{
    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Tile tile;
            tile.rect.x = j * tileWidth + j * 5.0f;
            tile.rect.y = i * tileHeight + i * 5.0f + 50.0f;
            tile.rect.width = (float)tileWidth;
            tile.rect.height = (float)tileHeight;

            int randNum = rand() % 100 + 1;

            if (randNum <= 60) 
            { // 60% chance a tile could be regular
                tile.type = REGULAR;

                if (i == 0) // last row tile
                    tile.points = 40;
                else if (i == 1) // third row tile
                    tile.points = 30;
                else if (i == 2) // second row
                    tile.points = 20;
                else // first row tile
                    tile.points = 10;
            } 
            else if (randNum > 60 && randNum <= 90) 
            { // 30% chance a tile could be a bomb
                tile.type = BOMB;
                tile.points = (-10);
            } 
            else 
            { // WIP - Powerup tile (10%): Ideas - slow down ball, increase ball size
                tile.type = POWERUP;
                tile.points = 0;
            }

            tile.destroyed = false;

            tiles.push_back(tile);
        }
    }
}

void Tiles::Draw() 
{
    for (Tile& tile : tiles) 
    {
        if (!tile.destroyed) 
        {
            if (tile.type == REGULAR)
                DrawRectangleRec(tile.rect, WHITE);
            else if (tile.type == BOMB)
                DrawRectangleRec(tile.rect, RED);
            else
                DrawRectangleRec(tile.rect, GREEN);
        }
    }
}

std::vector<Tile>& Tiles::GetTiles() {
    return tiles;
}
