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
    if (IsKeyPressed(KEY_F11))
    {

        ToggleFullscreen();
    }

    DrawText("F11 para Tela Cheia", 10, 10, 20, RED);
    DrawText("ESC para Sair", 10, 40, 20, RED);
    DrawText("Bem-vindo à Fase 2!", 10, 70, 20, RED);
    DrawFPS(10, 130);
}

void LevelTwoUnload(void)
{
    UnloadMusicStream(music);
}
