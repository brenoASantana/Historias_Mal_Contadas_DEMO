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
int currentWave = 0; // Onda atual
int enemiesPerWave = 2; // Número inicial de inimigos por onda
float timeBetweenWaves = 5.0f; // Tempo entre ondas
float waveTimer = 0; // Timer para controlar o tempo entre as ondas
GameScreen currentScreen = GAMEPLAY;

void InitGame(void);
void SpawnEnemies(void);
void UpdateEnemies(void);
void DrawGame(void);
void UpdateGame(void);
void StartNextWave(void);
void UpdatePlayer(float deltaTime);
void PlayerAttack(void);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HMC");

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();

    free(enemies); // Libera a memória alocada

    return 0;
}

void InitGame(void) {
    player.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    player.health = PLAYER_HEALTH;
    player.color = BLUE;
    player.isAttacking = false;
    player.attackCooldown = 0;

    currentWave = 0;
    waveTimer = 0;

    enemies = NULL;
    srand(time(NULL));
    gameTime = 0;
    defeatedEnemies = 0;
    StartNextWave();
}

void StartNextWave(void) {
    currentWave++;
    enemyCount = enemiesPerWave * currentWave;
    enemies = (Enemy *)realloc(enemies, enemyCount * sizeof(Enemy));
    for (int i = 0; i < enemyCount; i++) {
        enemies[i].active = false;
        enemies[i].color = RED;
    }
    SpawnEnemies();
}

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

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentScreen == GAMEPLAY) {
        DrawCircleV(player.position, PLAYER_SIZE / 2, player.color);

        if (player.isAttacking) {
            DrawCircleLines(player.position.x, player.position.y, ATTACK_RANGE, BLACK);
        }

        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i].active) {
                DrawCircleV(enemies[i].position, ENEMY_SIZE / 2, enemies[i].color);
            }
        }

        DrawText(TextFormat("Vida: %d", player.health), 10, 10, 20, BLACK);
        DrawText(TextFormat("Tempo: %.2f", gameTime), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Tempo: %.2f", gameTime), 20) / 2, 10, 20, BLACK);
        DrawText(TextFormat("Onda: %d", currentWave), SCREEN_WIDTH - 100, 10, 20, BLACK); // Desenhar o contador de ondas
    } else if (currentScreen == PAUSE) {
        DrawText("PAUSADO", SCREEN_WIDTH / 2 - MeasureText("PAUSADO", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        DrawText("Pressione ENTER para sair", SCREEN_WIDTH / 2 - MeasureText("Pressione ENTER para sair", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
        DrawText("Pressione P para continuar", SCREEN_WIDTH / 2 - MeasureText("Pressione P para continuar", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, BLACK);
    } else if (currentScreen == GAMEOVER) {
        DrawText("FIM DE JOGO", SCREEN_WIDTH / 2 - MeasureText("FIM DE JOGO", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        DrawText(TextFormat("Tempo sobrevivido: %.2f segundos", gameTime), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Tempo sobrevivido: %.2f segundos", gameTime), 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
        DrawText(TextFormat("Inimigos derrotados: %d", defeatedEnemies), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Inimigos derrotados: %d", defeatedEnemies), 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, BLACK);
        DrawText("Pressione ENTER para reiniciar", SCREEN_WIDTH / 2 - MeasureText("Pressione ENTER para reiniciar", 20) / 2, SCREEN_HEIGHT / 2 + 60, 20, BLACK);
    }

    EndDrawing();
}

void UpdateGame(void) {
    if (currentScreen == GAMEPLAY) {
        float deltaTime = GetFrameTime();
        gameTime += deltaTime;
        spawnTimer += deltaTime;
        waveTimer += deltaTime;

        // Atualizar Jogador
        UpdatePlayer(deltaTime);

        // Atualizar Inimigos
        UpdateEnemies();

        // Verificar se todos os inimigos foram derrotados para iniciar a próxima onda
        bool allEnemiesDefeated = true;
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i].active) {
                allEnemiesDefeated = false;
                break;
            }
        }

        if (allEnemiesDefeated) {
            if (waveTimer >= timeBetweenWaves) {
                waveTimer = 0;
                StartNextWave();
            }
        } else {
            waveTimer = 0; // Reinicia o timer se ainda há inimigos ativos
        }

        // Verifica fim de jogo
        if (player.health <= 0) {
            currentScreen = GAMEOVER;
        }
    } else if (currentScreen == PAUSE) {
        if (IsKeyPressed(KEY_ENTER)) {
            CloseWindow();
        } else if (IsKeyPressed(KEY_P)) {
            currentScreen = GAMEPLAY;
        }
    } else if (currentScreen == GAMEOVER) {
        if (IsKeyPressed(KEY_ENTER)) {
            InitGame();
            currentScreen = GAMEPLAY;
        }
    }
}

void UpdatePlayer(float deltaTime) {
    if (IsKeyDown(KEY_W)) player.position.y -= PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_S)) player.position.y += PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_A)) player.position.x -= PLAYER_SPEED * deltaTime;
    if (IsKeyDown(KEY_D)) player.position.x += PLAYER_SPEED * deltaTime;

    // Limita a posição do jogador à tela
    if (player.position.x < PLAYER_SIZE / 2) player.position.x = PLAYER_SIZE / 2;
    if (player.position.x > SCREEN_WIDTH - PLAYER_SIZE / 2) player.position.x = SCREEN_WIDTH - PLAYER_SIZE / 2;
    if (player.position.y < PLAYER_SIZE / 2) player.position.y = PLAYER_SIZE / 2;
    if (player.position.y > SCREEN_HEIGHT - PLAYER_SIZE / 2) player.position.y = SCREEN_HEIGHT - PLAYER_SIZE / 2;

    // Atualiza o cooldown do ataque
    if (player.attackCooldown > 0) {
        player.attackCooldown -= deltaTime;
    } else if (IsKeyPressed(KEY_SPACE)) {
        player.isAttacking = true;
        player.attackCooldown = ATTACK_COOLDOWN;
        PlayerAttack(); // Executa a função de ataque do jogador
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
