#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

/*
#include "../include/enemy.h"
#include "../include/levelTwo.h"
#include "../include/playerLevelTwo.h"
#include "playerLevelTwo.c"
#include "levelTwo.c"
*/
extern Player player;  // Declaração externa
extern Enemy *enemies;
extern int enemyCount;

void SpawnEnemies(void) {
    for (int i = 0; i < enemyCount; i++) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float distance = GetRandomValue(SPAWN_DISTANCE_MIN, SPAWN_DISTANCE_MAX);
        enemies[i].position = (Vector2){
            player.position.x + cos(angle) * distance,
            player.position.y + sin(angle) * distance
        };
        enemies[i].active = true;
    }
}

void UpdateEnemies(void) {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].active) {
            Vector2 direction = Vector2Subtract(player.position, enemies[i].position);
            direction = Vector2Normalize(direction);
            enemies[i].position = Vector2Add(enemies[i].position, Vector2Scale(direction, ENEMY_SPEED * GetFrameTime()));
            if (CheckCollisionCircles(player.position, PLAYER_SIZE / 2, enemies[i].position, ENEMY_SIZE / 2)) {
                player.health--;
                enemies[i].active = false;
                if (player.health <= 0) {
                    currentScreen = GAMEOVER;
                }
            }
        }
    }
}
