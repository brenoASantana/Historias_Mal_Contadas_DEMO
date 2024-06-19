#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "raylib.h"

#define PLAYERLEVELTWO_SIZE 50
#define ENEMY_SIZE 40
#define SPAWN_INTERVAL_MIN 1
#define SPAWN_INTERVAL_MAX 3
#define PLAYERLEVELTWO_HEALTH 3
#define ATTACK_RANGE 45
#define ATTACK_COOLDOWN 0.5f
#define SPAWN_DISTANCE_MIN 200
#define SPAWN_DISTANCE_MAX 300

typedef enum GameScreen
{
    START,
    GAMEPLAY,
    GAMEOVER
} GameScreen;

void LevelTwoInit(void);
void LevelTwoUpdate(void);
void LevelTwoDraw(void);
void LevelTwoUnload(void);
void StartNextWave(void);
void DrawPixelatedBackground(void);

#endif // LEVELTWO_H
