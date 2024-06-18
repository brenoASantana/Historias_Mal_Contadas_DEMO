#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Texture2D texture;
    int health;
} Player;

Player CreatePlayer(Vector2 position);
void UpdatePlayer(Player *player);
void DrawPlayer(Player player);

#endif // PLAYER_H
