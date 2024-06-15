#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SIZE 50
#define ENEMY_SIZE 40
#define SPAWN_INTERVAL_MIN 1
#define SPAWN_INTERVAL_MAX 3
#define PLAYER_HEALTH 3
#define ATTACK_RANGE 45
#define ATTACK_COOLDOWN 0.5f
#define AREA_ATTACK_RANGE 100
#define AREA_ATTACK_COOLDOWN 5.0f
#define SPAWN_DISTANCE_MIN 200
#define SPAWN_DISTANCE_MAX 300
#define PLAYER_SPEED 300.0f // Velocidade do jogador
#define ENEMY_SPEED 100.0f // Velocidade do inimigo

typedef struct Player {
    Vector2 position;
    int health;
    Color color;
    bool isAttacking;
    float attackCooldown;
    float areaAttackCooldown;
    bool isAreaAttacking;
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
Enemy *enemies;
int enemyCount = 2; // Número inicial de inimigos
int defeatedEnemies = 0; // Contador de inimigos derrotados
float spawnTimer = 0;
float gameTime = 0; // Tempo de jogo
GameScreen currentScreen = GAMEPLAY;
int waveCount = 1; // Contador de ondas
float survivalTime = 0; // Tempo de sobrevivência
float finalSurvivalTime = 0; // Tempo final de sobrevivência

// Declaração da função SpawnEnemies
void SpawnEnemies(void);

void InitGame(void) {
    player.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    player.health = PLAYER_HEALTH;
    player.color = BLUE;
    player.isAttacking = false;
    player.attackCooldown = 0;
    player.areaAttackCooldown = 0;
    player.isAreaAttacking = false;

    enemies = (Enemy *)malloc(enemyCount * sizeof(Enemy));
    for (int i = 0; i < enemyCount; i++) {
        enemies[i].active = false;
        enemies[i].color = RED;
    }

    srand(time(NULL));
    gameTime = 0;
    survivalTime = 0; // Reinicia o tempo de sobrevivência
    finalSurvivalTime = 0; // Reinicia o tempo final de sobrevivência
    defeatedEnemies = 0;
    waveCount = 1; // Inicializa a contagem de ondas
    SpawnEnemies();
}

void SpawnEnemies(void) {
    free(enemies); // Libera a memória anteriormente alocada
    enemies = (Enemy *)malloc(enemyCount * sizeof(Enemy));

    for (int i = 0; i < enemyCount; i++) {
        float angle;
        float distance;

        // Garante que os inimigos não apareçam muito próximos ao jogador
        do {
            angle = GetRandomValue(0, 360) * DEG2RAD;
            distance = GetRandomValue(SPAWN_DISTANCE_MIN, SPAWN_DISTANCE_MAX);
            enemies[i].position = (Vector2){
                player.position.x + cos(angle) * distance,
                player.position.y + sin(angle) * distance
            };
        } while (CheckCollisionCircles(player.position, PLAYER_SIZE * 2, enemies[i].position, ENEMY_SIZE / 2));

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
                enemies[i].active = false;
                player.health--;
                if (player.health <= 0) {
                    finalSurvivalTime = survivalTime; // Salva o tempo final de sobrevivência
                    currentScreen = GAMEOVER;
                }
            }
        }
    }
}

void CheckWaveComplete(void) {
    bool allDefeated = true;
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].active) {
            allDefeated = false;
            break;
        }
    }

    if (allDefeated) {
        waveCount++;
        enemyCount++;
        SpawnEnemies();
    }
}

void UpdatePlayer(void) {
    if (IsKeyDown(KEY_W)) player.position.y -= PLAYER_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_S)) player.position.y += PLAYER_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_A)) player.position.x -= PLAYER_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_D)) player.position.x += PLAYER_SPEED * GetFrameTime();

    // Limita o jogador aos limites da tela
    if (player.position.x < 0) player.position.x = 0;
    if (player.position.x > SCREEN_WIDTH) player.position.x = SCREEN_WIDTH;
    if (player.position.y < 0) player.position.y = 0;
    if (player.position.y > SCREEN_HEIGHT) player.position.y = SCREEN_HEIGHT;

    // Atualiza o cooldown do ataque
    if (player.attackCooldown > 0) player.attackCooldown -= GetFrameTime();
    if (player.areaAttackCooldown > 0) player.areaAttackCooldown -= GetFrameTime();

    // Verifica o ataque em área
    if (IsKeyPressed(KEY_SPACE) && player.areaAttackCooldown <= 0) {
        player.isAreaAttacking = true;
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i].active && CheckCollisionCircles(player.position, AREA_ATTACK_RANGE, enemies[i].position, ENEMY_SIZE / 2)) {
                enemies[i].active = false;
            }
        }
        player.areaAttackCooldown = AREA_ATTACK_COOLDOWN;
    }
}

void UpdateGame(void) {
    if (currentScreen == GAMEPLAY) {
        gameTime += GetFrameTime();
        survivalTime += GetFrameTime(); // Atualiza o tempo de sobrevivência
        UpdatePlayer();
        UpdateEnemies();
        CheckWaveComplete();

        if (player.isAreaAttacking) {
            player.isAreaAttacking = false;
        }
    } else if (currentScreen == PAUSE) {
        if (IsKeyPressed(KEY_P)) {
            currentScreen = GAMEPLAY;
        }
    } else if (currentScreen == GAMEOVER) {
        if (IsKeyPressed(KEY_R)) {
            InitGame();
            currentScreen = GAMEPLAY;
        }
    }
}

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentScreen == GAMEPLAY) {
        DrawText(TextFormat("Onda: %d", waveCount), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Vida: %d", player.health), 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Cooldown do Ataque em Área: %.1f", player.areaAttackCooldown), 10, 70, 20, DARKGRAY);
        DrawText(TextFormat("Tempo de Sobrevivência: %.1f", survivalTime), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Tempo de Sobrevivência: %.1f", survivalTime), 20) / 2, 10, 20, DARKGRAY);
        
        // Desenha o ataque em área se estiver ativo
        if (player.isAreaAttacking) {
            DrawCircleLines(player.position.x, player.position.y, AREA_ATTACK_RANGE, BLUE);
        }

        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i].active) {
                DrawCircleV(enemies[i].position, ENEMY_SIZE / 2, enemies[i].color);
            }
        }
        DrawCircleV(player.position, PLAYER_SIZE / 2, player.color);
    } else if (currentScreen == PAUSE) {
        DrawText("PAUSADO", SCREEN_WIDTH / 2 - MeasureText("PAUSADO", 40) / 2, SCREEN_HEIGHT / 2 - 20, 40, DARKGRAY);
        DrawText("Pressione 'P' para continuar", SCREEN_WIDTH / 2 - MeasureText("Pressione 'P' para continuar", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
    } else if (currentScreen == GAMEOVER) {
        DrawText("FIM DE JOGO", SCREEN_WIDTH / 2 - MeasureText("FIM DE JOGO", 40) / 2, SCREEN_HEIGHT / 2 - 20, 40, RED);
        DrawText(TextFormat("Onda Final: %d", waveCount), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Onda Final: %d", waveCount), 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
        DrawText(TextFormat("Você sobreviveu por: %.1f segundos", finalSurvivalTime), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Você sobreviveu por: %.1f segundos", finalSurvivalTime), 20) / 2, SCREEN_HEIGHT / 2 + 40, 20, DARKGRAY);
        DrawText("Pressione 'R' para reiniciar", SCREEN_WIDTH / 2 - MeasureText("Pressione 'R' para reiniciar", 20) / 2, SCREEN_HEIGHT / 2 + 60, 20, DARKGRAY);
    }

    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Enemy Waves");
    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P) && currentScreen == GAMEPLAY) {
            currentScreen = PAUSE;
        } else if (IsKeyPressed(KEY_P) && currentScreen == PAUSE) {
            currentScreen = GAMEPLAY;
        }
        UpdateGame();
        DrawGame();
    }

    CloseWindow();

    return 0;
}
