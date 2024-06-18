#include "raylib.h"
#include "../include/levelTwo.h"

static Music music;

void LevelTwoInit(void)
{
    music = LoadMusicStream("../assets/sounds/musics/heilag_vagga.mp3");
    SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(music);
}

void LevelTwoUpdate(void)
{
    UpdateMusicStream(music);
    // Adicione a lógica de atualização da fase 2 aqui
}

void LevelTwoDraw(void)
{
    DrawText("Bem vindo ao inferno.", 10, 10, 20, RED);

    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
}

void LevelTwoUnload(void)
{
    UnloadMusicStream(music);
}
