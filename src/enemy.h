#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct Enemy {
    Vector2 position;
    Texture2D texture;
    int health;
} Enemy;

Enemy CreateEnemy(Vector2 position);
void UpdateEnemy(Enemy *enemy);
void DrawEnemy(Enemy enemy);

#endif // ENEMY_H
