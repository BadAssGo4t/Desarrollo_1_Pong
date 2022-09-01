#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Game.h"
using namespace std;


#define PLAYER_MAX_LIFE         5


// players
typedef struct Player {
	Rectangle plyRec;
	Vector2 position;
	Vector2 size;
	bool active;
	int life;
} P1, P2;

typedef struct Ball {
	Vector2 position;
	Vector2 speed;
	int radius;
	bool active;
} Ball;

// Global Variables Declaration
//------------------------------------------------------------------------------------


static int screenUpperLimit = 40;

static int gameOver = 0;
static bool pause = false;
static int dir = 0;
static int dirspeed = false;
static P1 p1 = { 0 };
static P2 p2 = { 0 };
static Ball ball = { 0 };
static Vector2 brickSize = { 0 };

// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)





//------------------------------------------------------------------------------------
int RunGame(void)
{
	srand(time(NULL));

	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "Pong");

	InitGame();

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update and Draw
		UpdateDrawFrame();
	}

	// De-Init
	UnloadGame();         // Unload loaded data (textures, sounds, models...)

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

void InitGame(void)
{


	// Init player 1
	p1.position = { 40, screenHeight / 2 };
	p1.size = { 20, screenHeight / 10 + 20 };
	p1.life = PLAYER_MAX_LIFE;
	p1.active = false;
	// Init player 2
	p2.position = { screenWidth - 40, screenHeight / 2 };
	p2.size = { 20, screenHeight / 10 + 20 };
	p2.life = PLAYER_MAX_LIFE;
	p1.active = false;

	// Initialize ball
	ball.position = { screenWidth / 2, screenHeight / 2 };
	ball.speed = { 0, 0 };
	ball.radius = 7;
	ball.active = false;

}

// Game update
void UpdateGame(void)

{

	if (gameOver != 1 && gameOver != 2)
	{
		if (IsKeyPressed('P')) pause = !pause;

		if (!pause)
		{
			if (p1.active == true)
			{
				// Player mov
				// X axis Posible power up
				/*
				if (IsKeyDown(KEY_LEFT)) p1.position.x -= 5;
				if ((p1.position.x - p1.size.x / 2) <= 0) p1.position.x = p1.size.x / 2;
				if (IsKeyDown(KEY_RIGHT)) p1.position.x += 5;
				if ((p1.position.x + p1.size.x / 2) >= screenWidth) p1.position.x = screenWidth - p1.size.x / 2;
				*/

				// Y axis
				if (IsKeyDown(KEY_UP)) p1.position.y -= 5;
				if (IsKeyDown(KEY_DOWN)) p1.position.y += 5;
				if ((p1.position.y) >= GetScreenHeight())
				{
					p1.position.y = GetScreenHeight() - p1.size.y / 3;
				}
				else if (p1.position.y <= screenUpperLimit) p1.position.y = screenUpperLimit;
			}

			if (p1.active == true)
			{
				// X axis Posible power up
				/*
				if (IsKeyDown(KEY_A)) p2.position.x -= 5;
				if ((p2.position.x - p2.size.x / 2) <= 0) p2.position.x = p2.size.x / 2;
				if (IsKeyDown(KEY_D)) p2.position.x += 5;
				if ((p2.position.x + p2.size.x / 2) >= screenWidth) p2.position.x = screenWidth - p2.size.x / 2;
				*/

				// Y axis
				if (IsKeyDown(KEY_W)) p2.position.y -= 5;
				if (IsKeyDown(KEY_S)) p2.position.y += 5;
				if ((p2.position.y + 20) >= GetScreenHeight())
				{
					p2.position.y = GetScreenHeight() - p2.size.y / 3;
				}
				else if (p2.position.y <= screenUpperLimit) p2.position.y = screenUpperLimit;
			}

			//----------------------- ( Ball ) ------------------------------

			 // Ball movement logic
			if (!ball.active)
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					dir = rand() % 10 + 1;
					ball.active = true;
					p1.active = true;
					p2.active = true;

					if (dir >= 5)
					{
						dirspeed = 5;
					}
					else
					{
						dirspeed = -5;
					}
					ball.speed = { (float)dirspeed, 0 };

				}
			}
			if (ball.active)
			{
				ball.position.x += ball.speed.x;
				ball.position.y += ball.speed.y;
			}
			else
			{
				ball.position = { screenWidth / 2, screenHeight / 2 };
			}


			// Collision logic: ball vs walls 
			if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0)) ball.speed.x *= -1;
			if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;
			if ((ball.position.y + ball.radius) >= GetScreenHeight())ball.speed.y *= -1;


			// Player 1 loses life
			if ((ball.position.x - ball.radius) <= 0)
			{
				ball.speed = { 0, 0 };
				ball.active = false;
				p1.active = false;
				p2.active = false;
				p1.position.y = screenHeight / 2;
				p2.position.y = screenHeight / 2;
				p1.life--;
			}
			// player 2 loses life 
			else
				if (((ball.position.x + ball.radius) >= screenWidth))
				{
					ball.speed = { 0, 0 };
					ball.active = false;
					p1.active = false;
					p2.active = false;
					p1.position.y = screenHeight / 2;
					p2.position.y = screenHeight / 2;
					p2.life--;
				}

			// Collision ball vs player1
			if (CheckCollisionCircleRec(ball.position, ball.radius, { p1.position.x - p1.size.x / 2, p1.position.y - p1.size.y / 2, p1.size.x, p1.size.y }))
			{
				if (ball.speed.y > 0 || ball.speed.x != 0)
				{
					ball.speed.y = (ball.position.y - p1.position.y) / (p1.size.y / 2) * 5;
					ball.speed.x = (ball.position.x - p1.position.x) / (p1.size.x / 2) * 5;
				}
			}

			// Collision ball vs player2
			if (CheckCollisionCircleRec(ball.position, ball.radius, { p2.position.x - p2.size.x / 2, p2.position.y - p2.size.y / 2, p2.size.x, p2.size.y }))

			{
				if (ball.speed.y > 0 || ball.speed.x != 0)
				{
					ball.speed.y = (ball.position.y - p2.position.y) / (p2.size.y / 2) * 5;
					ball.speed.x = (ball.position.x - p2.position.x) / (p2.size.x / 2) * 5;
				}

			}



			// Game over logic
			if (p1.life <= 0) gameOver = 1;
			else
			{
				if (p2.life <= 0)
				{
					gameOver = 2;
				}
			}
		}

	}
	else
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			EndDrawing();
			gameOver = false;
			RunGame();
		}
	}
}

// Draw game 
void DrawGame(void)
{
	Texture2D texLife = LoadTexture("../resources/vidasx40.png"); // take out of the Update

	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (!gameOver)
	{
		//Screen text draw
		DrawText("PONG", screenWidth / 2 - 30, 12, 30, BLACK);
		DrawText("Press P for Pause", screenWidth - 230, 12, 20, MAROON);
		DrawText("Press Space to start", 20, 12, 20, MAROON);
		DrawText("Player 1", 70, screenHeight - 70, 20, MAROON);
		DrawText("Player 2", screenWidth - 300, screenHeight - 70, 20, MAROON);

		// Draw P1 
		DrawRectangle(p1.position.x - p1.size.x / 2, p1.position.y - p1.size.y / 2, p1.size.x, p1.size.y, BLACK);
		// Draw P2
		DrawRectangle(p2.position.x - p2.size.x / 2, p2.position.y - p2.size.y / 2, p2.size.x, p2.size.y, BLACK);
		// Draw ball
		DrawCircleV(ball.position, ball.radius, MAROON);

		// Draw P1 lives 
		for (int i = 0; i < p1.life; i++) DrawTexture(texLife, 60 + 45 * i, screenHeight - 45, WHITE);
		// Draw P2 lives 
		for (int i = 0; i < p2.life; i++) DrawTexture(texLife, 610 + 45 * i, screenHeight - 45, WHITE);

		if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
	}
	else
	{
		DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

		// Credits
		DrawText("Creditos:", GetScreenWidth() / 2 - MeasureText("Creditos:", 20), GetScreenHeight() - 100, 20, GRAY);
		DrawText("Alumno: Estanislao Sala Barraquero.", GetScreenWidth() / 2 - MeasureText("Alumno: Estanislao Sala Barraquero.", 20), GetScreenHeight() - 80, 20, GRAY);
		DrawText("Libreria: Raylib.", GetScreenWidth() / 2 - MeasureText("Libreria: Raylib.", 20), GetScreenHeight() - 60, 20, GRAY);
	}


	EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{

	// TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
	UpdateGame();
	DrawGame();
}

