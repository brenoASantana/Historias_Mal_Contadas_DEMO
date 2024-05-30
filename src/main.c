#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEXT_SPEED 5

// Função para ler o conteúdo de um arquivo de texto e retornar como uma string
char *ReadTextFile(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // Abre o arquivo para leitura binária
    if (!file)
    {
        return NULL; // Retorna NULL se o arquivo não puder ser aberto
    }

    fseek(file, 0, SEEK_END);  // Move o cursor para o fim do arquivo
    long length = ftell(file); // Obtém o tamanho do arquivo em bytes
    fseek(file, 0, SEEK_SET);  // Move o cursor de volta para o início do arquivo

    char *buffer = (char *)malloc(length + 1); // Aloca memória para armazenar o conteúdo do arquivo
    if (buffer)
    {
        fread(buffer, 1, length, file); // Lê o conteúdo do arquivo para o buffer
        buffer[length] = '\0';          // Adiciona um terminador nulo ao final da string
    }

    fclose(file);  // Fecha o arquivo
    return buffer; // Retorna o buffer contendo o conteúdo do arquivo
}

// Função para desenhar o texto lentamente na tela
void DrawTextSlowly(const char *text, int x, int y, int fontSize, Color color, int *charCount)
{
    int length = strlen(text);
    if (*charCount < length)
    {
        DrawText(TextSubtext(text, 0, *charCount + 1), x, y, fontSize, color);
        (*charCount)++;
    }
    else
    {
        DrawText(text, x, y, fontSize, color);
    }
}

int main(void)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Histórias Mal Contadas DEMO"); // Inicializa a janela com o título especificado
    InitAudioDevice();

    Music music = LoadMusicStream("/Historias_Mal_Contadas_DEMO/assets/musics/a_warning_before_reading.mp3");
    PlayMusicStream(music);

    SetTargetFPS(60); // Define a taxa de quadros alvo para 60 FPS

    char *prologueText = ReadTextFile("/Historias_Mal_Contadas_DEMO/assets/texts/prologue.txt");
    int charCount = 0;

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

        DrawText("Pressione F11 para deixar em tela cheia", 10, 40, 20, GREEN);
        // DrawFPS(600, 40);
        DrawText("Pressione ESC para sair", 10, 70, 20, GREEN);

        DrawTextSlowly(prologueText, 10, 10, 20, GREEN, &charCount);

        EndDrawing();

        // Ajusta a pausa para controlar a velocidade de impressão do texto
        //if (charCount < strlen(prologueText))
        //    usleep(1000000 / TEXT_SPEED);
    }

    free(prologueText); // Libera a memória alocada para o texto do prólogo
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0; // Retorna 0 indicando que o programa foi executado com sucesso
}