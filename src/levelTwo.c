#include "raylib.h"
#include "../include/levelTwo.h"

static Music music;

void LevelTwoInit(void)
{
    music = LoadMusicStream("../assets/musics/woodland_shadows.mp3");
    PlayMusicStream(music);
}

void LevelTwoUpdate(void)
{
    UpdateMusicStream(music);
    // Adicione a lógica de atualização da fase 2 aqui
}

void LevelTwoDraw(void)
{
    DrawText("F11 para Tela Cheia", 10, 10, 20, RED);
    DrawText("ESC para Sair", 10, 40, 20, RED);
    DrawText("Pressione 1 para a Fase 1", 10, 70, 20, RED);
    DrawText("Bem-vindo à Fase 2!", 10, 100, 20, RED);
    DrawFPS(10, 130);

    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void LevelTwoUnload(void)
{
    UnloadMusicStream(music);
}
