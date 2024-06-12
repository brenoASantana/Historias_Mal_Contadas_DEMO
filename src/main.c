#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/levelTwo.h"
#include "../include/intro.h"//os .h estão sendo inuteis pois não consigo puxar nada deles, somente pelo .c
#include "text.c"
#include "intro.c"
#include "levelOne.c"
#include "levelTwo.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO");
    InitAudioDevice();
    SetTargetFPS(60);

    int currentLevel = 0; // Começa na introdução

    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
        if (currentLevel == 0) {
            IntroInit();
            while (currentLevel == 0 && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(BLACK);

                IntroUpdate();
                IntroDraw();

                if (IsKeyPressed(KEY_ENTER)) { // condição para passar para o próximo nível
                    currentLevel = 1;
                    IntroUnload();
                }

                EndDrawing();
            }
        }
        
        if (currentLevel == 1) {
            LevelOneInit();
            while (currentLevel == 1 && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(BLACK);
                
                LevelOneUpdate();
                LevelOneDraw();
                
                if (IsKeyPressed(KEY_ENTER)) { // condição para passar de nível
                    currentLevel++;
                    LevelOneUnload();
                }

                EndDrawing();
            }
        }
        
        if (currentLevel == 2) {
            LevelTwoInit();
            while (currentLevel == 2 && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(BLACK);

                LevelTwoUpdate();
                LevelTwoDraw();

                if (IsKeyPressed(KEY_ENTER)) { // condição para passar de nível
                    currentLevel++;
                    LevelTwoUnload();
                }

                EndDrawing();
            }
        }
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
