#ifndef PLAYERLEVELTWO_H
#define PLAYERLEVELTWO_H

#include "raylib.h"

typedef struct PlayerLevelTwo {
    Vector2 position;
    Texture2D texture;
    int hp;
    int hit;
    int habilityID;
    int hasKey;
    int atTable;
} PlayerLevelTwo;

Player CreatePlayerLevelTwo(Vector2 position);
void UpdatePlayerLevelTwo(Player *player);
void DrawPlayerLevelTwo(Player player);

#endif // PLAYERLEVELTWO_H
