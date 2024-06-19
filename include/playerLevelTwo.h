#ifndef PLAYERLEVELTWO_H
#define PLAYERLEVELTWO_H

#include "raylib.h"

#define PLAYER_SPEED 300.0f

typedef struct Player {
    Vector2 position;
    int health;
    Color color;
    bool isAttacking;
    float attackCooldown;
} Player;

void UpdatePlayer(float deltaTime);
void PlayerAttack(void);

#endif // PLAYERLEVELTWO_H
