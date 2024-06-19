#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

#define ENEMY_SPEED 100.0f

typedef struct Enemy {
    Vector2 position;
    bool active;
    Color color;
} Enemy;

void SpawnEnemies(void);
void UpdateEnemies(void);

#endif // ENEMY_H
