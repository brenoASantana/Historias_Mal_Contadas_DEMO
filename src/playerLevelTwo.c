#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

extern PlayerLevelTwo playerLevelTwo; // Declaração externa
extern Enemy *enemies;
extern int enemyCount;
extern int defeatedEnemies;

void PlayerLevelTwoUpdate(float deltaTime)
{
    if (IsKeyDown(KEY_UP))
        playerLevelTwo.position.y -= PLAYERLEVELTWO_SPEED * deltaTime;
    if (IsKeyDown(KEY_DOWN))
        playerLevelTwo.position.y += PLAYERLEVELTWO_SPEED * deltaTime;
    if (IsKeyDown(KEY_LEFT))
        playerLevelTwo.position.x -= PLAYERLEVELTWO_SPEED * deltaTime;
    if (IsKeyDown(KEY_RIGHT))
        playerLevelTwo.position.x += PLAYERLEVELTWO_SPEED * deltaTime;

    if (playerLevelTwo.position.x < PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.x = PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.x > GetScreenWidth() - PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.x = GetScreenWidth() - PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.y < PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.y = PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.y > GetScreenHeight() - PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.y = GetScreenHeight() / 2;

    if (playerLevelTwo.attackCooldown > 0)
    {
        playerLevelTwo.attackCooldown -= deltaTime;
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        playerLevelTwo.isAttacking = true;
        playerLevelTwo.attackCooldown = ATTACK_COOLDOWN;
        PlayerLevelTwoAttack();
    }
    else
    {
        playerLevelTwo.isAttacking = false;
    }
}

void PlayerLevelTwoAttack(void)
{
    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i].active && CheckCollisionCircles(playerLevelTwo.position, ATTACK_RANGE, enemies[i].position, ENEMY_SIZE / 2))
        {
            enemies[i].active = false;
            defeatedEnemies++;
        }
    }
}
