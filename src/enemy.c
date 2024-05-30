#include "enemy.h"

Enemy CreateEnemy(Vector2 position)
{
    Enemy enemy = { position, LoadTexture("assets/sprites/enemy.png"), 50 };
    return enemy;
}

void UpdateEnemy(Enemy *enemy)
{
    // Atualização da lógica do inimigo
}

void DrawEnemy(Enemy enemy)
{
    DrawTexture(enemy.texture, enemy.position.x, enemy.position.y, RAYWHITE);
}
