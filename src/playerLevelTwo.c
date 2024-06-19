#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>
/*
#include "../include/playerLevelTwo.h"
#include "../include/enemy.h"
#include "enemy.c"
*/
extern Player player;  // Declaração externa
extern Enemy *enemies;
extern int enemyCount;
extern int defeatedEnemies;

void UpdatePlayer(float deltaTime) {
    if (IsKeyDown(KEY_W)) player.position.y -= PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_S)) player.position.y += PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_A)) player.position.x -= PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_D)) player.position.x += PLAYER_SPEED * deltaTime;

    if (player.position.x < PLAYER_SIZE / 2) player.position.x = PLAYER_SIZE / 2;
    if (player.position.x > GetScreenWidth() - PLAYER_SIZE / 2) player.position.x = GetScreenWidth() - PLAYER_SIZE / 2;
    if (player.position.y < PLAYER_SIZE / 2) player.position.y = PLAYER_SIZE / 2;
    if (player.position.y > GetScreenHeight() - PLAYER_SIZE / 2) player.position.y = GetScreenHeight() / 2;

    if (player.attackCooldown > 0) {
        player.attackCooldown -= deltaTime;
    } else if (IsKeyPressed(KEY_SPACE)) {
        player.isAttacking = true;
        player.attackCooldown = ATTACK_COOLDOWN;
        PlayerAttack();
    } else {
        player.isAttacking = false;
    }
}

void PlayerAttack(void) {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].active && CheckCollisionCircles(player.position, ATTACK_RANGE, enemies[i].position, ENEMY_SIZE / 2)) {
            enemies[i].active = false;
            defeatedEnemies++;
        }
    }
}
