#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/levelTwo.h"
#include "levelOne.c"
#include "levelTwo.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int screenWidth;
int screenHeight;

void InitWindowWithResponsiveResolution()
{
    // Set default resolution
    screenWidth = 800;
    screenHeight = 600;

    // Initialize window with default resolution
    InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO");

    // Get half of the monitor resolution
    int monitorIndex = 0;
    int monitorWidth = GetMonitorWidth(monitorIndex);
    int monitorHeight = GetMonitorHeight(monitorIndex);

    // Adjust window size to monitor resolution
    screenWidth = monitorWidth / 2;
    screenHeight = monitorHeight / 2;

    SetWindowSize(screenWidth, screenHeight);

    // Set target frames per second
    SetTargetFPS(60);
}

int main(void)
{
    // Inicializa a janela com resolução responsiva
    InitWindowWithResponsiveResolution();

    InitAudioDevice();

    int currentLevel = 1; // Começa na introdução

    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
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

                if (isDoorOpen)
                { // Player conseguiu abrir a porta do level 1
                    currentLevel++;
                    LevelOneUnload();
                }

                EndDrawing();
            }
            LevelOneUnload();
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
            LevelTwoUnload();
            break;

        default:
            break;
        }
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
