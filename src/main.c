#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/levelOne.h"
#include "../include/levelTwo.h"
#include "levelOne.c"
#include "levelTwo.c"
#include "../include/text.h"
#include "text.c"
#include "../include/playerLevelTwo.h"
#include "playerLevelTwo.c"
#include "../include/enemy.h"
#include "enemy.c"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Histórias Mal Contadas DEMO");
    SetTargetFPS(60);

    InitAudioDevice();

    int currentLevel = 1; // Começa na introdução

    LevelOneInit();
    do
    {

        BeginDrawing();
        ClearBackground(BLACK);

        LevelOneUpdate();
        LevelOneDraw();

        if (isDoorOpen)
        { // Player conseguiu abrir a porta do level 1
            currentLevel++;
            
        }

        EndDrawing();
    } while (currentLevel == 1 && !WindowShouldClose());

    LevelOneUnload();
    CloseAudioDevice();
    CloseWindow();
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Histórias Mal Contadas DEMO");
    SetTargetFPS(60);

    InitAudioDevice();
    LevelTwoInit();
    do
    {

        BeginDrawing();
        ClearBackground(BLACK);

        LevelTwoUpdate();
        LevelTwoDraw();

        EndDrawing();
    } while (currentLevel == 2 && !WindowShouldClose());

    LevelTwoUnload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
