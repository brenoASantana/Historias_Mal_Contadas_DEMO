#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"
#include <string.h>
#include <ctype.h> // Adicionado para usar a função toupper

static char *fileText = NULL;
static int charCount = 0;
static Music music;
int doorLocked = 1;
int isWithKey = 0;
int isDoorOpen = 0;
bool isNearDoor = false;
bool isNearTable = false;

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
        // Desenhar qualquer coisa adicional aqui se necessário

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
        if (isNearTable && isWithKey == 0) {
            const char *newFilePath = "../assets/texts/takeKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isWithKey = 1;
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
        if (isNearDoor && isWithKey == 1 && doorLocked == 1) {
            const char *newFilePath = "../assets/texts/unlockDoorWithKey.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            doorLocked = 0;
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
        if (isNearDoor && doorLocked == 0 && isDoorOpen == 0) {
            const char *newFilePath = "../assets/texts/openUnlockedDoor.txt";
            free(fileText);
            fileText = ReadTextFile(newFilePath);
            if (!fileText) {
                printf("Failed to read the file.\n");
                return;
            }
            charCount = 0;
            isDoorOpen = 1;
        } else if (isNearDoor && doorLocked == 1) {
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
    } else if (strcmp(inputText, "AJUDA") == 0) {
        const char *newFilePath = "../assets/texts/help.txt";
        free(fileText);
        fileText = ReadTextFile(newFilePath);
        if (!fileText) {
            printf("Failed to read the file.\n");
            return;
        }
        charCount = 0;
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
