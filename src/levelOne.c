#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

static char *fileText = NULL;
static int charCount = 0;
static Music music;
int doorLocked = 0;
int isWithKey = 1;
int isDoorOpen = 1;

void LevelOneInit(void)
{
    music = LoadMusicStream("../assets/sounds/musics/a_warning_before_reading.mp3");
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
        DrawText(">", 10, 700, 20, GREEN);
        DrawText(inputText, 20, 700, 20, GREEN);

        if (IsKeyPressed(KEY_ENTER))
        {
            enterPressed = true;
            AnalyzeInput(inputText);
        }
    }
    
    else
    {
        ClearBackground(BLACK);
        //DrawText("Você digitou:", 10, 100, 20, GREEN);
        //DrawText(inputText, 10, 130, 20, GREEN);

        enterPressed = false;
        letterCount = 0;
        memset(inputText, 0, sizeof(inputText)); // Limpa o inputText
    }
    
}

void LevelOneDraw(void)
{
    DrawText("Histórias Mal Contadas por B2 Studios.", 10, 10, 40, GREEN);
    DrawText("F11 para Tela Cheia, ESC para Sair, Digite AJUDA para mais.", 10, 60, 20, GREEN);

    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void AnalyzeInput(char *inputText)
{
    if (strcmp(inputText, "IR ATE PORTA") == 0) {
        const char *newFilePath = "../assets/texts/goToDoor.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
    } else if (strcmp(inputText, "ABRIR PORTA") == 0 && doorLocked==0) { // Tentar abrir a porta trancada
        const char *newFilePath = "../assets/texts/openLockedDoor.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        
    } else if (strcmp(inputText, "ABRIR PORTA") == 0 && doorLocked==1) { // Abrir a porta destrancada
        const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        isDoorOpen = 0;
        
    }else if (strcmp(inputText, "IR ATE MESA") == 0) {
        const char *newFilePath = "../assets/texts/goToTable.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
    }
    else if (strcmp(inputText, "PEGAR CHAVE") == 0) {
        const char *newFilePath = "../assets/texts/takeKey.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        isWithKey = 0; //Pegou a chave
    }
    else if (strcmp(inputText, "DESTRANCAR PORTA") == 0 && isWithKey == 1) { //Tenta destrancar porta sem chave
        const char *newFilePath = "../assets/texts/unlockDoorWithoutKey.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        doorLocked = 1;//Destrancou a porta
    }
    else if (strcmp(inputText, "DESTRANCAR PORTA") == 0 && isWithKey == 0) { //Tenta destrancar porta sem chave
        const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        doorLocked = 1;//Destrancou a porta
    }
    else if (strcmp(inputText, "AJUDA") == 0) {
        const char *newFilePath = "../assets/texts/help.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
    }
   else {
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