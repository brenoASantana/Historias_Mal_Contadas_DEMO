#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

extern PlayerLevelTwo playerLevelTwo; // Declaração externa
extern Enemy *enemies;
extern int enemyCount;

void EnimiesSpawn(void)
{
    for (int i = 0; i < enemyCount; i++)
    {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float distance = GetRandomValue(SPAWN_DISTANCE_MIN, SPAWN_DISTANCE_MAX);
        enemies[i].position = (Vector2){
            playerLevelTwo.position.x + cos(angle) * distance,
            playerLevelTwo.position.y + sin(angle) * distance};
        enemies[i].active = true;
    }
}

void EnimiesUpdate(void)
{
    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i].active)
        {
            Vector2 direction = Vector2Subtract(playerLevelTwo.position, enemies[i].position);
            direction = Vector2Normalize(direction);
            enemies[i].position = Vector2Add(enemies[i].position, Vector2Scale(direction, ENEMY_SPEED * GetFrameTime()));
            if (CheckCollisionCircles(playerLevelTwo.position, PLAYERLEVELTWO_SIZE / 2, enemies[i].position, ENEMY_SIZE / 2))
            {
                playerLevelTwo.health--;
                enemies[i].active = false;
                if (playerLevelTwo.health <= 0)
                {
                    currentScreen = GAMEOVER;
                }
            }
        }
    }
}
