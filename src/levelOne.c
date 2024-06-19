#include "raylib.h"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/PlayerLevelOne.h"
#include "playerLevelOne.c"

static char *fileText = NULL;
static int charCount = 0;
static Music soundTrack;
bool isDoorLocked = true;
bool isDoorOpen = false;
int lastXPosition = 10;
int lastYPosition = 10;

PlayerLevelOne playerLevelOne;

void LevelOneInit(void)
{
    soundTrack = LoadMusicStream("../assets/sounds/soundtracks/woodland_shadows.mp3");
    SetMusicVolume(soundTrack, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(soundTrack);

    const char *filePath = "../assets/texts/prologue.txt";
    fileText = ReadTextFile(filePath);
    if (!fileText)
    {
        printf("Failed to read the file.\n");
        return;
    }

    charCount = 0;
    playerLevelOne = CreatePlayerLevelOne();
}

void LevelOneUpdate(void)
{
    UpdateMusicStream(soundTrack);

    if (!enterPressed)
    {
        DrawTextWithDelay(fileText, 10, 60, 20, GREEN, &charCount, 1);
        GetUserInput(inputText, 256, &letterCount);

        // Desenha o texto digitado pelo usuário em tempo real
        DrawText(">", 10, GetScreenHeight() - 30, 20, GREEN);
        DrawText(inputText, 20, GetScreenHeight() - 30, 20, GREEN);

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
    DrawText("Histórias Mal Contadas, uma produção da B2 Studios.", 10, 10, 40, DARKGREEN);

}

void AnalyzeInput(char *inputText)
{
    // Foi definido que, se o jogador executar o mesmo comando duas vezes, não será avisado que esse comando já foi executado; o texto será apenas impresso novamente.
    for (int i = 0; inputText[i]; i++)
    {
        inputText[i] = toupper(inputText[i]);
    }

    if (strcmp(inputText, "IR ATE PORTA") == 0)
    {
        const char *newFilePath = "../assets/texts/goToDoor.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText)
        {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        playerLevelOne.position = 1; // Player está próximo da porta
    }
    else if (strcmp(inputText, "IR ATE MESA") == 0)
    {
        const char *newFilePath = "../assets/texts/goToTable.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText)
        {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        playerLevelOne.position = 2; // Player está próximo da mesa
    }
    else if (strcmp(inputText, "PEGAR CHAVE") == 0)
    {
        if (playerLevelOne.position == 2)
        { // Se o player estiver próximo da mesa
            const char *newFilePath = "../assets/texts/takeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            playerLevelOne.hasKey = true;
        }
        else
        { // Player está longe da mesa
            const char *newFilePath = "../assets/texts/tooFarTakeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    }
    else if (strcmp(inputText, "DESTRANCAR PORTA") == 0)
    {
        if (playerLevelOne.position == 1 && playerLevelOne.hasKey)
        { // Se o  player está próximo da porta e com a chave
            const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorLocked = false;
        }
        else if (playerLevelOne.position == 1 && !playerLevelOne.hasKey)
        { // Se o player está próximo da porta mas sem a chave
            const char *newFilePath = "../assets/texts/tryUnlockDoorWithoutKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
        else
        { // Se o player está longe da porta
            const char *newFilePath = "../assets/texts/tooFarUnlockDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    }
    else if (strcmp(inputText, "ABRIR PORTA") == 0)
    {
        if (playerLevelOne.position == 1 && !isDoorLocked)
        { // Se o player está próximo da porta e a porta está destrancada
            const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorOpen = true;
        }
        else if (playerLevelOne.position == 1 && isDoorLocked)
        { // Se o player está próximo da porta e a porta está trancada
            const char *newFilePath = "../assets/texts/tryOpenLockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
        else
        { // Player está longe da porta
            const char *newFilePath = "../assets/texts/tooFarOpenDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText)
            {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    }
    else
    { // Se o comando for desconhecido
        const char *newFilePath = "../assets/texts/unknow.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText)
        {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
    }
}

void LevelOneUnload(void)
{
    free(fileText);
    UnloadMusicStream(soundTrack);
}
