#ifndef PLAYERLEVELTWO_H
#define PLAYERLEVELTWO_H

#include "raylib.h"

#define PLAYERLEVELTWO_SPEED 300.0f

typedef struct PlayerLevelTwo
{
    Vector2 position;
    int health;
    Color color;
    bool isAttacking;
    float attackCooldown;
} PlayerLevelTwo;

void PlayerLevelTwoUpdate(float deltaTime);
void PlayerLevelTwoAttack(void);

#endif // PLAYERLEVELTWO_H
