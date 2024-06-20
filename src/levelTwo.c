#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h> // Incluir a biblioteca para manipulação de arquivos

#include "../include/playerLevelTwo.h"
#include "../include/enemy.h"

PlayerLevelTwo playerLevelTwo;
Enemy *enemies;
int enemyCount = 2;
int defeatedEnemies = 0;
float spawnTimer = 0;
float gameTime = 0;
int currentWave = 0;
int enemiesPerWave = 2;
float timeBetweenWaves = 5.0f;
float waveTimer = 0;
float startTime = 0;
GameScreen currentScreen = START;

Texture2D startScreenImage;

void StartNextWave(void)
{
    currentWave++;
    enemyCount = enemiesPerWave * currentWave;
    enemies = (Enemy *)realloc(enemies, enemyCount * sizeof(Enemy));
    for (int i = 0; i < enemyCount; i++)
    {
        enemies[i].active = false;
        enemies[i].color = RED;
    }
    EnimiesSpawn();
}

// Função para salvar as informações no arquivo score.txt
void SaveScore(float survivedTime, int defeatedEnemies)
{
    FILE *file = fopen("score.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "Tempo sobrevivido: %.2f segundos\n", survivedTime);
        fprintf(file, "Inimigos derrotados: %d\n", defeatedEnemies);
        fclose(file);
    }
    else
    {
        printf("Erro ao criar o arquivo score.txt\n");
    }
}

// Desenha o white noise do game over
void DrawPixelatedBackground(void)
{
    // Define fundo White Noise
    Color stoneGray1 = (Color){100, 100, 100, 255};
    Color stoneGray2 = (Color){120, 120, 120, 255};
    Color stoneGray3 = (Color){140, 140, 140, 255};
    Color stoneGray4 = (Color){160, 160, 160, 255};

    // Define as cores
    Color stoneColors[4] = {stoneGray1, stoneGray2, stoneGray3, stoneGray4};

    // Define tamanho do bloco
    int pixelSize = 10;

    // Desenha o fundo
    for (int y = 0; y < GetScreenHeight(); y += pixelSize)
    {
        for (int x = 0; x < GetScreenWidth(); x += pixelSize)
        {
            // Troca aleatoriamente
            Color color = stoneColors[rand() % 4];
            DrawRectangle(x, y, pixelSize, pixelSize, color);
        }
    }
}

static Music soundTrack;
static Music jumpscare;
static Music gameOver;

void LevelTwoInit(void)
{
    soundTrack = LoadMusicStream("../assets/sounds/soundtracks/heilag_vagga.mp3");
    SetMusicVolume(soundTrack, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(soundTrack);

    jumpscare = LoadMusicStream("../assets/sounds/effects/jumpscare.ogg");
    //SetMusicVolume(jumpscare, 0.20); // Set volume for music (1.0 is max level)

    gameOver = LoadMusicStream("../assets/sounds/soundtracks/white_noise.mp3");
    SetMusicVolume(gameOver, 0.20); // Set volume for music (1.0 is max level)

    PlayMusicStream(jumpscare);

    playerLevelTwo.position = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
    playerLevelTwo.health = PLAYERLEVELTWO_HEALTH;
    playerLevelTwo.color = BLUE;
    playerLevelTwo.isAttacking = false;
    playerLevelTwo.attackCooldown = 0;

    currentWave = 0;
    waveTimer = 0;

    enemies = NULL;
    srand(time(NULL));
    gameTime = 0;
    defeatedEnemies = 0;
    StartNextWave();

    startScreenImage = LoadTexture("../assets/images/jumpscare.png");
}

void LevelTwoUpdate(void)
{
    UpdateMusicStream(soundTrack);
    UpdateMusicStream(jumpscare);
    UpdateMusicStream(gameOver);
    switch (currentScreen)
    {
    case START:
        if (GetTime() - startTime > 3.0)
        {
            StopMusicStream(jumpscare);
            currentScreen = GAMEPLAY;
        }
        break;

    case GAMEPLAY:
        float deltaTime = GetFrameTime();
        gameTime += deltaTime;
        spawnTimer += deltaTime;
        waveTimer += deltaTime;

        PlayerLevelTwoUpdate(deltaTime);
        EnimiesUpdate();

        bool allEnemiesDefeated = true;
        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i].active)
            {
                allEnemiesDefeated = false;
                break;
            }
        }

        if (allEnemiesDefeated)
        {
            if (waveTimer >= timeBetweenWaves)
            {
                waveTimer = 0;
                StartNextWave();
            }
        }
        else
        {
            waveTimer = 0;
        }

        if (playerLevelTwo.health <= 0)
        {
            currentScreen = GAMEOVER;
            SaveScore(gameTime, defeatedEnemies); // Salva as informações quando o jogo acaba
        }
        break;

    case GAMEOVER:
        StopMusicStream(soundTrack);
        PlayMusicStream(gameOver);
        break;

    default:
        break;
    }
}

void LevelTwoDraw(void)
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (currentScreen)
    {
    case START:
    {
        int centerX = (GetScreenWidth() - startScreenImage.width) / 2;
        int centerY = (GetScreenHeight() - startScreenImage.height) / 2;
        DrawTexture(startScreenImage, centerX, centerY, WHITE);
        DrawText("BEM-VINDO AO INFERNO!", GetScreenWidth() / 2 - MeasureText("BEM-VINDO AO INFERNO!", 20) / 2, GetScreenHeight() / 3 - 10, 20, RED);
    }
    break;

    case GAMEPLAY:
        DrawCircleV(playerLevelTwo.position, PLAYERLEVELTWO_SIZE / 2, playerLevelTwo.color);
        if (playerLevelTwo.isAttacking)
        {
            DrawCircleLines(playerLevelTwo.position.x, playerLevelTwo.position.y, ATTACK_RANGE, YELLOW);
        }
        for (int i = 0; i < enemyCount; i++)
        {
            if (enemies[i].active)
            {
                DrawCircleV(enemies[i].position, ENEMY_SIZE / 2, enemies[i].color);
            }
        }
        DrawText(TextFormat("Vida: %d", playerLevelTwo.health), 10, 10, 20, RED);
        DrawText("Use as setas do teclado para se mover. Pressione a barra de espaço para atacar.", 10, 60, 20, RED);
        DrawText(TextFormat("Tempo: %.2f", gameTime), GetScreenWidth() / 2 - MeasureText(TextFormat("Tempo: %.2f", gameTime), 20) / 2, 10, 20, RED);
        DrawText(TextFormat("Onda: %d", currentWave), GetScreenWidth() - 100, 10, 20, RED);
        break;

    case GAMEOVER:
        DrawPixelatedBackground();
        DrawText("FIM DE JOGO", GetScreenWidth() / 2 - MeasureText("FIM DE JOGO", 40) / 2, GetScreenHeight() / 2 - 40, 40, RED);
        DrawText(TextFormat("Tempo sobrevivido: %.2f segundos", gameTime), GetScreenWidth() / 2 - MeasureText(TextFormat("Tempo sobrevivido: %.2f segundos", gameTime), 20) / 2, GetScreenHeight() / 2, 20, RED);
        DrawText(TextFormat("Inimigos derrotados: %d", defeatedEnemies), GetScreenWidth() / 2 - MeasureText(TextFormat("Inimigos derrotados: %d", defeatedEnemies), 20) / 2, GetScreenHeight() / 2 + 30, 20, RED);
        DrawText("Confira sua pontuação no arquivo 'score.txt' criado.", GetScreenWidth() / 2 - MeasureText("Confira sua pontuação no arquivo 'score.txt' criado.", 20) / 2, GetScreenHeight() / 2 + 60, 20, RED);
        break;

    default:
        break;
    }

    EndDrawing();
}

void LevelTwoUnload(void)
{
    UnloadMusicStream(soundTrack);
    UnloadMusicStream(jumpscare);
    UnloadMusicStream(gameOver);
    UnloadTexture(startScreenImage);
    free(enemies);
}
