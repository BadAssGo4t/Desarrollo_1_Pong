#pragma once
#include "raylib.h"
#include "Main.h"
#include "Ball.h"
#include "Player.h"


void RunGame();

struct Screen {
    int screenWidth = 1200;
    int screenHeight = 600;
};
Screen CreateScreen();


void Init(Screen& screen);
void MainLoop(Screen& screen, Player& player1, Player& player2);

void CheckInput();
void Draw();

void Close();




