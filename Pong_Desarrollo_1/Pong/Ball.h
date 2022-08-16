#pragma once
#include "Game.h"

Ball InitBall();

void UpdateBall(Screen& screen, Ball& ball);

void DrawBall(Screen& screen, Ball& ball);

struct Ball {
    Vector2 position;
    float speed;
    int Radius;
};