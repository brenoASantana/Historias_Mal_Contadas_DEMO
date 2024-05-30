#include "raylib.h"
#include "player.h"
#include "enemy.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Jogo com Raylib");
    InitAudioDevice();

    Music music = LoadMusicStream("assets/music/sua_musica.mp3");
    PlayMusicStream(music);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Jogo com Raylib", 10, 10, 20, DARKGRAY);
        DrawText("Pressione ESC para sair", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
