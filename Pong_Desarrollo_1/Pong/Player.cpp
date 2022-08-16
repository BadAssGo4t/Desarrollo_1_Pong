#include "Player.h"

Player InitPlayer()
{
    Player player1;
    Player player2;

    return player1, player2;
}

void UpdatePlayer(Screen& screen, Player& player1, Player& player2)
{
    player1.position = { (float)80, (float)screen.screenHeight / 2 - 40 };
    player2.position = { (float)screen.screenWidth - 40,  (float)screen.screenHeight / 2 - 40 };
}
void DrawPLayer(Player& player1, Player& player2)
{

}
