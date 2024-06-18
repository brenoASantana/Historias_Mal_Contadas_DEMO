#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include "../include/PlayerLevelOne.h"
#include "playerLevelOne.c"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

static char *fileText = NULL;
static int charCount = 0;
static Music music;
bool isDoorLocked = true;
bool isDoorOpen = false;
int lastXPosition = 10;
int lastYPosition = 10;

PlayerLevelOne player;

void LevelOneInit(void)
{
    music = LoadMusicStream("../assets/sounds/musics/woodland_shadows.mp3");
    SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(music);

    const char *filePath = "../assets/texts/prologue.txt";
    fileText = ReadTextFile(filePath);
    if (!fileText)
    {
        printf("Failed to read the file.\n");
        return;
    }

    charCount = 0;
    player = CreatePlayerLevelOne();
}

void LevelOneUpdate(void)
{
    UpdateMusicStream(music);

    if (!enterPressed)
    {
        DrawTextWithDelay(fileText, 10, 100, 20, GREEN, &charCount, 1);
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
    DrawText("Pressione F11 para alternar entre os modos de janela e tela cheia. Pressione ESC para sair.", 10, 60, 20, DARKGREEN);

    if (IsKeyPressed(KEY_F11))
    {

        // Obtém a resolução original
        int screenWidth = GetScreenWidth() * 2;
        int screenHeight = GetScreenHeight() * 2;

        SetWindowSize(screenWidth, screenHeight);
        ToggleFullscreen();
    }
}

void AnalyzeInput(char *inputText)
{
    //Foi definido que, se o jogador executar o mesmo comando duas vezes, não será avisado que esse comando já foi executado; o texto será apenas impresso novamente.
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
        player.position = 1;//Player está próximo da porta
    } else if (strcmp(inputText, "IR ATE MESA") == 0) {
        const char *newFilePath = "../assets/texts/goToTable.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
        player.position = 2;//Player está próximo da mesa
    } else if (strcmp(inputText, "PEGAR CHAVE") == 0) {
        if (player.position == 2) {// Se o player estiver próximo da mesa
            const char *newFilePath = "../assets/texts/takeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            player.hasKey = true;
        } else { // Player está longe da mesa
            const char *newFilePath = "../assets/texts/tooFarTakeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else if (strcmp(inputText, "DESTRANCAR PORTA") == 0) {
        if (player.position==1 && player.hasKey) {//Se o  player está próximo da porta e com a chave
            const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorLocked = false;
        } else if(player.position==1 && !player.hasKey){//Se o player está próximo da porta mas sem a chave
            const char *newFilePath = "../assets/texts/tryUnlockDoorWithoutKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
        else{// Se o player está longe da porta
            const char *newFilePath = "../assets/texts/tooFarUnlockDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else if (strcmp(inputText, "ABRIR PORTA") == 0) {
        if (player.position==1 && !isDoorLocked) {//Se o player está próximo da porta e a porta está destrancada
            const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorOpen = true;
        } else if (player.position==1 && isDoorLocked) {//Se o player está próximo da porta e a porta está trancada
            const char *newFilePath = "../assets/texts/tryOpenLockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        } else {// Player está longe da porta
            const char *newFilePath = "../assets/texts/tooFarOpenDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
        }
    } else {//Se o comando for desconhecido
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
