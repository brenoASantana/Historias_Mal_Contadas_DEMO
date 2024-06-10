#include "raylib.h"
#include "../include/text.h"
#include "text.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEXT_SPEED 5
#define FADE_SPEED 0.01f

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO"); // Inicializa a janela com o título especificado
    InitAudioDevice();

    Music music = LoadMusicStream("../assets/musics/a_warning_before_reading.mp3");
    PlayMusicStream(music);

    SetTargetFPS(60); // Define a taxa de quadros alvo para 60 FPS

    char *prologueText = ReadTextFile("../assets/texts/prologue.txt");
    int charCount = 0;
    float alpha = 0.0f;
    TextState state = FADE_IN;

    if (!prologueText) // Verifica se o conteúdo do arquivo foi lido com sucesso
    {
        CloseAudioDevice();
        CloseWindow();
        printf("Failed to read the file.\n");
        return 1;
    }

    while (!WindowShouldClose()) // Loop principal do programa, continua enquanto a janela não for fechada
    {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_F11)) // Verifica se a tecla F11 foi pressionada para alternar entre tela cheia e janela
        {
            ToggleFullscreen(); // Alterna entre tela cheia e janela
        }
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextWithFade(prologueText, 10, 10, 20, GREEN, &charCount, &alpha, &state);

        EndDrawing();
    }

    free(prologueText); // Libera a memória alocada para o texto do prólogo
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}
