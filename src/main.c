#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/levelTwo.h"
#include "text.c"
#include "levelOne.c"
#include "levelTwo.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void InitWindowWithResponsiveResolution() {
    // Inicializa a janela com uma resolução padrão (800x600)
    InitWindow(800, 600, "Histórias Mal Contadas DEMO");
    
    // Obtém a resolução do monitor principal (0)
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    // Ajusta a janela para a resolução do monitor em tela cheia
    SetWindowSize(screenWidth, screenHeight);
    
    // Alterna para tela cheia
    ToggleFullscreen();
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
                    
                    if (isDoorOpen == 1) { // Player conseguiu abrir a porta do level 1
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
