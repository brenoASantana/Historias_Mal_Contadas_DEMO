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

int main(void)
{

    InitWindow(1280, 720, "Histórias Mal Contadas DEMO");
    SetTargetFPS(60);

    InitAudioDevice();

    int currentLevel = 1; // Começa na introdução

<<<<<<< Updated upstream
    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
=======
    //while (!WindowShouldClose()) { // Loop principal do programa, continua enquanto a janela não for fechada
        // (currentLevel) {
            //case 1:
            LevelOneInit();
            do{
                
               // while (currentLevel == 1 && !WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);
>>>>>>> Stashed changes

        switch (currentLevel)
        {
        case 1:
            LevelOneInit();
            while (currentLevel == 1 && !WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

<<<<<<< Updated upstream
                LevelOneUpdate();
                LevelOneDraw();

                if (isDoorOpen)
                { // Player conseguiu abrir a porta do level 1
                    currentLevel++;
                    LevelOneUnload();
                }

                EndDrawing();
            }
            break;
=======
                    if (isDoorOpen) { // Player conseguiu abrir a porta do level 1
                        currentLevel++;
                        break;
                    }

                    EndDrawing();
              //  }
                
            }while(currentLevel==1 && !WindowShouldClose());            
            LevelOneUnload(); // Unload LevelOne resources
           //     continue;

           // case 2:
            CloseAudioDevice();
    CloseWindow();
    InitWindow(1280, 720, "Histórias Mal Contadas DEMO");
    SetTargetFPS(60);

    InitAudioDevice();
             LevelTwoInit();
           do{
              
              //  while (currentLevel == 2 && !WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);
>>>>>>> Stashed changes

        case 2:
            LevelTwoInit();
            while (currentLevel == 2 && !WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

<<<<<<< Updated upstream
                LevelTwoUpdate();
                LevelTwoDraw();

                EndDrawing();
            }
            break;

        default:
            break;
        }
    }
=======
                    EndDrawing();
              //  } 
                
           }while(currentLevel==2 && !WindowShouldClose());
           LevelTwoUnload(); // Unload LevelTwo resources (if needed)
           //     break;

          //  default:
          //      break;
        //}
   // }
>>>>>>> Stashed changes

    CloseAudioDevice();
    CloseWindow();

    return 0;
}