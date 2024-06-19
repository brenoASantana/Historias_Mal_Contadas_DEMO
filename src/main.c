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

int main(void) {
    InitWindow(1280, 720, "Histórias Mal Contadas DEMO");
    SetTargetFPS(60);

    InitAudioDevice();

    int currentLevel = 1; // Começa na introdução

    while (!WindowShouldClose()) { // Loop principal do programa, continua enquanto a janela não for fechada
        switch (currentLevel) {
            case 1:
                LevelOneInit();
                while (currentLevel == 1 && !WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);

                    LevelOneUpdate();
                    LevelOneDraw();

                    if (isDoorOpen) { // Player conseguiu abrir a porta do level 1
                        currentLevel++;
                        LevelOneUnload();
                    }

                    EndDrawing();
                }
                break;

            case 2:
                LevelTwoInit();
                while (currentLevel == 2 && !WindowShouldClose()) {
                    //LevelOneUnload();
                    BeginDrawing();
                    ClearBackground(BLACK);

                    LevelTwoUpdate();
                    LevelTwoDraw();

                    EndDrawing();
                }
                break;

            default:
                break;
        }
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
