#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

static char *fileText = NULL;
static int charCount = 0;
static Music music;
bool doorLocked = true;
bool isWithKey = false;
bool isDoorOpen = false;
bool isNearDoor = false;
bool isNearTable = false;
int lastXPosition = 10;
int lastYPosition = 10;

void LevelOneInit(void)
{
    //tres opcoes de musica nas quais fiquei confuso de qual escolher :P
    //music = LoadMusicStream("../assets/sounds/musics/a_warning_before_reading.mp3");
    //music = LoadMusicStream("../assets/sounds/musics/in_the_black_lake.mp3");
    music = LoadMusicStream("../assets/sounds/musics/woodland_shadows.mp3");
    SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(music);

    const char *filePath = "../assets/texts/prologue.txt";
    fileText = ReadTextFile(filePath);
    if (!fileText) {
        printf("Failed to read the file.\n");
        return;
    }

    charCount = 0;
}

void LevelOneUpdate(void)
{
    UpdateMusicStream(music);

    if (!enterPressed)
    {
        DrawTextWithDelay(fileText, 10, 100, 20, GREEN, &charCount, 1);
        GetUserInput(inputText, 256, &letterCount);

        // Desenha o texto digitado pelo usuário em tempo real
        DrawText(">", 10, GetScreenHeight()-30, 20, GREEN);
        DrawText(inputText, 20, GetScreenHeight()-30, 20, GREEN);

        if (IsKeyPressed(KEY_ENTER))
        {
            enterPressed = true;
            AnalyzeInput(inputText);
        }
    }
    else
    {
        ClearBackground(BLACK);

        enterPressed = false;
        letterCount = 0;
        memset(inputText, 0, sizeof(inputText)); // Limpa o inputText
    }
}

void LevelOneDraw(void)
{
    DrawText("Histórias Mal Contadas por B2 Studios.", 10, 10, 40, GREEN);
    DrawText("F11 para Tela Cheia, ESC para Sair.", 10, 60, 20, GREEN);

          if (IsKeyPressed(KEY_F11)) {                
                 
                // Obtém a resolução original
                int screenWidth = GetScreenWidth()*2;
                int screenHeight = GetScreenHeight()*2;
    
                SetWindowSize(screenWidth, screenHeight);
                ToggleFullscreen();
               
        }
}

void AnalyzeInput(char *inputText)
{
    for (int i = 0; inputText[i]; i++) {
        inputText[i] = toupper(inputText[i]);
    }

    if (strcmp(inputText, "IR ATE PORTA") == 0) {
        const char *newFilePath = "../assets/texts/goToDoor.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        isNearDoor = true;
        isNearTable = false;
    } else if (strcmp(inputText, "IR ATE MESA") == 0) {
        const char *newFilePath = "../assets/texts/goToTable.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        isNearDoor = false;
        isNearTable = true;
    } else if (strcmp(inputText, "PEGAR CHAVE") == 0) {
        if (isNearTable && !isWithKey) {
            const char *newFilePath = "../assets/texts/takeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isWithKey = true;
        } else {
            const char *newFilePath = "../assets/texts/cannotTakeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else if (strcmp(inputText, "DESTRANCAR PORTA") == 0) {
        if (isNearDoor && isWithKey == 1 && doorLocked) {
            const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            doorLocked = false;
        } else {
            const char *newFilePath = "../assets/texts/cannotUnlockDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else if (strcmp(inputText, "ABRIR PORTA") == 0) {
        if (isNearDoor && !doorLocked && !isDoorOpen) {
            const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorOpen = true;
        } else if (isNearDoor && doorLocked) {
            const char *newFilePath = "../assets/texts/openLockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        } else {
            const char *newFilePath = "../assets/texts/cannotOpenDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else {
        const char *newFilePath = "../assets/texts/unknow.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
    }
}

void LevelOneUnload(void)
{
    free(fileText);
    UnloadMusicStream(music);
}
