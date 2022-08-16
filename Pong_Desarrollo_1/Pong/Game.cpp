#include "Game.h"


Screen screen;

void RunGame()
{   
   
    screen = CreateScreen();

    Init(Screen& screen);

    MainLoop(Screen& screen);

    Close();
}

Screen CreateScreen()
{
    screen.screenHeight = 600;
    screen.screenWidth = 1200;

    return screen;
}

void Init(Screen& screen)
{
    InitWindow(screen.screenWidth, screen.screenHeight, "Pong E_Sala_Barraquero");
    SetTargetFPS(60);

    InitBall();
    InitPlayer();
}



void MainLoop(Screen& screen, Player& player1, Player& player2)
{
    while (!WindowShouldClose())
    {
        // Update getframetime() para la pelota


        if (IsKeyDown(KEY_W)) player1.position.y -= 4.0f;
        if (IsKeyDown(KEY_S)) player1.position.y += 4.0f;
        //-----
        if (IsKeyDown(KEY_UP)) player2.position.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN)) player2.position.y += 4.0f;


        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(player1.position.x, player1.position.y, 40, 80, MAROON);
        DrawRectangle(player2.position.x, player2.position.y, 40, 80, MAROON);

        DrawText("Use W_KEY and S_KEY to move left player. Use UP_ARROW and DOWN_ARROW to move right player!", 190, 80, 20, LIGHTGRAY);

        EndDrawing();
    }
}

void Close()
{
    CloseWindow();
}

