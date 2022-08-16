#pragma once
#include "Game.h"

Player InitPlayer();

void UpdatePlayer(Screen& screen,Player& player1, Player& player2);

void DrawPLayer(Player& player1, Player& player2);

struct Player {
    Vector2 position;
    float speed;
    int Width;
    int Height;
};
