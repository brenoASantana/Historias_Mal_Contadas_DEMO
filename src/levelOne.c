#include "raylib.h"
#include "../include/text.h"
#include "../include/levelOne.h"

static char *fileText = NULL;
static int charCount = 0;
static Music music;

void LevelOneInit(void)
{
    music = LoadMusicStream("../assets/musics/a_warning_before_reading.mp3");
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
    DrawTextWithDelay(fileText, 10, 100, 20, GREEN, &charCount, 1);
}

void LevelOneDraw(void)
{
    DrawText("F11 para Tela Cheia", 10, 10, 20, GREEN);
    DrawText("ESC para Sair", 10, 40, 20, GREEN);
    DrawFPS(10, 70);

    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void LevelOneUnload(void)
{
    free(fileText);
    UnloadMusicStream(music);
}
