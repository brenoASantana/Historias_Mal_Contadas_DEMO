#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/levelTwo.h"//os .h estão sendo inuteis pois não consigo puxar nada deles, somente pelo .c
#include "text.c"
#include "levelOne.c"
#include "levelTwo.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO");
    InitAudioDevice();
    SetTargetFPS(60);

    int currentLevel = 1; // Começa na introdução
 
    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        switch (currentLevel)
        {
            case 1:
                LevelOneInit();
                while (currentLevel == 1 && !WindowShouldClose())
                {
                    BeginDrawing();
                    ClearBackground(BLACK);

                    LevelOneUpdate();
                    LevelOneDraw();
                    
                    if (isDoorOpen == 0) { // Player conseguiu abrir a porta do level 1
                        currentLevel++;
                        LevelOneUnload();
                    }

                    EndDrawing();
                }
                break;
        
            case 2:
                LevelTwoInit();
                while (currentLevel == 2 && !WindowShouldClose())
                {
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
