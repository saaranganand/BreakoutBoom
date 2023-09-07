#pragma once

#include<vector>
#include <raylib.h>

enum TileType
{
    REGULAR,
    BOMB,
    POWERUP
};

struct Tile {
    Rectangle rect;
    TileType type;
    int points;
    bool destroyed;
};

class Tiles 
{
    public:
        Tiles();
        void GenerateTiles();
        void Draw();
        bool Cleared();
        std::vector<Tile>& GetTiles();

    private:
        std::vector<Tile> tiles;
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
};