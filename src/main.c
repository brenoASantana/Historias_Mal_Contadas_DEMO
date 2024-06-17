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
    if (!InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO"))
    {
        printf("Failed to initialize window.\n");
        exit(1);
    }

    // Get half of the monitor resolution
    int monitorIndex = 0;
    int monitorWidth = GetMonitorWidth(monitorIndex);
    int monitorHeight = GetMonitorHeight(monitorIndex);

    // Check if monitor resolution is valid
    if (monitorWidth == 0 || monitorHeight == 0)
    {
        printf("Failed to get monitor resolution.\n");
        exit(1);
    }

    // Adjust window size to monitor resolution
    screenWidth = monitorWidth / 2;
    screenHeight = monitorHeight / 2;
    if (!SetWindowSize(screenWidth, screenHeight))
    {
        printf("Failed to set window size.\n");
        exit(1);
    }

    // Set target frames per second
    SetTargetFPS(60);
}

int main(void)
{
    // Inicializa a janela com resolução responsiva
    if (!InitWindowWithResponsiveResolution())
    {
        printf("Failed to initialize window.\n");
        return 1;
    }

    InitAudioDevice();

    int currentLevel = 1; // Começa na introdução

    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
        switch (currentLevel)
        {
            
        case 1:
            if (!LevelOneInit())
            {
                printf("Failed to initialize level one.\n");
                return 1;
            }
            while (currentLevel == 1 && !WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

                if (!LevelOneUpdate() || !LevelOneDraw())
                {
                    printf("Failed to update or draw level one.\n");
                    return 1;
                }

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
            if (!LevelTwoInit())
            {
                printf("Failed to initialize level two.\n");
                return 1;
            }
            while (currentLevel == 2 && !WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

                if (!LevelTwoUpdate() || !LevelTwoDraw())
                {
                    printf("Failed to update or draw level two.\n");
                    return 1;
                }

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
