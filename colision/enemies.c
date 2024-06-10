#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SIZE 50
#define ENEMY_SIZE 40
#define SPAWN_INTERVAL_MIN 1
#define SPAWN_INTERVAL_MAX 3
#define PLAYER_HEALTH 3
#define ATTACK_RANGE 30
#define ATTACK_COOLDOWN 0.5f
#define SPAWN_DISTANCE_MIN 200
#define SPAWN_DISTANCE_MAX 300

typedef struct Player {
    Vector2 position;
    int health;
    Color color;
    bool isAttacking;
    float attackCooldown;
} Player;

typedef struct Enemy {
    Vector2 position;
    bool active;
    Color color;
} Enemy;

typedef enum GameScreen {
    GAMEPLAY,
    PAUSE,
    GAMEOVER
} GameScreen;

Player player;
Enemy enemies[2];
float spawnTimer = 0;
float spawnInterval = 0;
GameScreen currentScreen = GAMEPLAY;

void InitGame(void) {
    player.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    player.health = PLAYER_HEALTH;
    player.color = BLUE;
    player.isAttacking = false;
    player.attackCooldown = 0;

    for (int i = 0; i < 2; i++) {
        enemies[i].active = false;
        enemies[i].color = RED;
    }

    srand(time(NULL));
    spawnInterval = GetRandomValue(SPAWN_INTERVAL_MIN, SPAWN_INTERVAL_MAX);
}

void SaveGame(void) {
    // Implement saving game state to file
    // For now, we will just print to console
    TraceLog(LOG_INFO, "Game Saved!");
}

void SpawnEnemies(void) {
    for (int i = 0; i < 2; i++) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float distance = GetRandomValue(SPAWN_DISTANCE_MIN, SPAWN_DISTANCE_MAX);
        enemies[i].position = (Vector2){
            player.position.x + cos(angle) * distance,
            player.position.y + sin(angle) * distance
        };
        enemies[i].active = true;
    }
}

void UpdateGame(void) {
    if (IsKeyPressed(KEY_P)) {
        if (currentScreen == GAMEPLAY) currentScreen = PAUSE;
        else if (currentScreen == PAUSE) currentScreen = GAMEPLAY;
    }

    if (currentScreen == GAMEPLAY) {
        if (IsKeyDown(KEY_RIGHT)) player.position.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) player.position.x -= 5.0f;
        if (IsKeyDown(KEY_UP)) player.position.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) player.position.y += 5.0f;

        if (IsKeyPressed(KEY_SPACE) && player.attackCooldown <= 0) {
            player.isAttacking = true;
            player.attackCooldown = ATTACK_COOLDOWN;
        }

        if (player.attackCooldown > 0) {
            player.attackCooldown -= GetFrameTime();
        } else {
            player.isAttacking = false;
        }

        // Enemy spawn logic
        if (!enemies[0].active && !enemies[1].active) {
            spawnTimer += GetFrameTime();
            if (spawnTimer >= spawnInterval) {
                SpawnEnemies();
                spawnTimer = 0;
                spawnInterval = GetRandomValue(SPAWN_INTERVAL_MIN, SPAWN_INTERVAL_MAX);
            }
        }

        // Enemy movement and collision logic
        for (int i = 0; i < 2; i++) {
            if (enemies[i].active) {
                Vector2 direction = {player.position.x - enemies[i].position.x, player.position.y - enemies[i].position.y};
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                direction.x /= length;
                direction.y /= length;

                enemies[i].position.x += direction.x * 2.0f; // Adjust speed as necessary
                enemies[i].position.y += direction.y * 2.0f;

                // Check collision with player
                if (CheckCollisionCircles(player.position, PLAYER_SIZE / 2, enemies[i].position, ENEMY_SIZE / 2)) {
                    player.health--;
                    enemies[i].active = false;

                    if (player.health <= 0) {
                        currentScreen = GAMEOVER;
                    }
                }

                // Check if player is attacking and in range
                if (player.isAttacking && CheckCollisionCircles(player.position, ATTACK_RANGE, enemies[i].position, ENEMY_SIZE / 2)) {
                    enemies[i].active = false;
                }
            }
        }
    } else if (currentScreen == PAUSE) {
        if (IsKeyPressed(KEY_ENTER)) {
            SaveGame();
            CloseWindow();
        }
    } else if (currentScreen == GAMEOVER) {
        if (IsKeyPressed(KEY_ENTER)) {
            InitGame();
            currentScreen = GAMEPLAY;
        }
    }
}

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentScreen == GAMEPLAY) {
        DrawCircleV(player.position, PLAYER_SIZE / 2, player.color);

        if (player.isAttacking) {
            DrawCircleLines(player.position.x, player.position.y, ATTACK_RANGE, BLACK);
        }

        for (int i = 0; i < 2; i++) {
            if (enemies[i].active) {
                DrawCircleV(enemies[i].position, ENEMY_SIZE / 2, enemies[i].color);
            }
        }

        DrawText(TextFormat("Vida: %d", player.health), 10, 10, 20, BLACK);
    } else if (currentScreen == PAUSE) {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        DrawText("Press ENTER to save and exit", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to save and exit", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
        DrawText("Press P to resume", SCREEN_WIDTH / 2 - MeasureText("Press P to resume", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, BLACK);
    } else if (currentScreen == GAMEOVER) {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        DrawText("Press ENTER to restart", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to restart", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
    }

    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HMC");

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();

    return 0;
}
