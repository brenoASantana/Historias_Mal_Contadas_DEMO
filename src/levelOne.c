#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/playerLevelOne.h"
#include "text.c"
#include "playerLevelOne.c"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

static char *fileText = NULL;
static int charCount = 0;
static Music music;
bool doorLocked = true;
bool isDoorOpen = false;

PlayerLevelOne player;

void LevelOneInit(void)
{
    // Inicialize o jogador
    player = CreatePlayerLevelOne();

    const char *musicPath = "../assets/sounds/musics/woodland_shadows.mp3";
    if (musicPath != NULL)
    {
        music = LoadMusicStream(musicPath);
        SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
        PlayMusicStream(music);
    }
    else
    {
        printf("Failed to load music file.\n");
    }

    const char *filePath = "../assets/texts/prologue.txt";
    if (filePath != NULL)
    {
        fileText = ReadTextFile(filePath);
        charCount = 0;
    }
    else
    {
        printf("Failed to load file text.\n");
    }
}

void LevelOneUpdate(void)
{
    UpdateMusicStream(music);

    if (!enterPressed)
    {
        DrawTextWithDelay(fileText, 10, 10, 20, GREEN, &charCount, 1);
        // Desenha o texto digitado pelo usuário em tempo real
        DrawText(">", 10, GetScreenHeight() - 30, 20, GREEN);
        DrawText(inputText, 20, GetScreenHeight() - 30, 20, GREEN);

        GetUserInput(inputText, 256, &letterCount);

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
    if (IsKeyPressed(KEY_F11))
    {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        if (screenWidth > 0 && screenHeight > 0)
        {
            screenWidth *= 2;
            screenHeight *= 2;

            SetWindowSize(screenWidth, screenHeight);
            ToggleFullscreen();
        }
        else
        {
            printf("Failed to set window size: screenWidth or screenHeight is zero.\n");
        }
    }

    DrawText("Histórias Mal Contadas por B2 Studios.", 10, 10, 40, GREEN);
    DrawText("F11 para alternar entre modo janela e tela cheia, ESC para Sair.", 10, 50, 20, GREEN);
}

void AnalyzeInput(char *inputText)
{
    if (inputText == NULL)
    {
        printf("Failed to analyze input: inputText is NULL.\n");
        return;
    }

    for (int i = 0; inputText[i]; i++)
    {
        inputText[i] = toupper(inputText[i]);
    }

    if (strcmp(inputText, "IR ATE PORTA") == 0)
    {
        const char *newFilePath = "../assets/texts/goToDoor.txt";
        if (fileText != NULL)
        {
            free(fileText);
        }
        fileText = ReadTextFile(newFilePath);

        charCount = 0;
        player.position = 1; // Player está perto da porta
    }
    else if (strcmp(inputText, "IR ATE MESA") == 0)
    {
        const char *newFilePath = "../assets/texts/goToTable.txt";
        if (fileText != NULL)
        {
            free(fileText);
        }
        fileText = ReadTextFile(newFilePath);

        charCount = 0;
        player.position = 2; // Player está perto da mesa
    }
    else if (strcmp(inputText, "PEGAR CHAVE") == 0)
    {
        if (player.position == 2 && !player.hasKey)
        {
            const char *newFilePath = "../assets/texts/takeKey.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
            player.hasKey = true;
        }
        else
        {
            const char *newFilePath = "../assets/texts/cannotTakeKey.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
        }
    }
    else if (strcmp(inputText, "DESTRANCAR PORTA") == 0)
    {
        if (player.position == 1 && player.hasKey && doorLocked)
        {
            const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
            doorLocked = false;
        }
        else
        {
            const char *newFilePath = "../assets/texts/cannotUnlockDoor.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
        }
    }
    else if (strcmp(inputText, "ABRIR PORTA") == 0)
    {
        if (player.position == 1 && !doorLocked && !isDoorOpen)
        {
            const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
            isDoorOpen = true;
        }
        else if (player.position == 1 && doorLocked)
        {
            const char *newFilePath = "../assets/texts/openLockedDoor.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
        }
        else
        {
            const char *newFilePath = "../assets/texts/cannotOpenDoor.txt";
            if (fileText != NULL)
            {
                free(fileText);
            }
            fileText = ReadTextFile(newFilePath);

            charCount = 0;
        }
    }
    else
    {
        const char *newFilePath = "../assets/texts/unknow.txt";
        if (fileText != NULL)
        {
            free(fileText);
        }
        fileText = ReadTextFile(newFilePath);

        charCount = 0;
    }
}

void LevelOneUnload(void)
{
    free(fileText);
    UnloadMusicStream(music);
}
