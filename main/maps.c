#include "raylib.h"

int main(void)
{
    // Inicializar a janela
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Carregar imagem JPG como mapa no raylib");

    // Carregar a imagem JPG
    Image mapImage = LoadImage("map.jpg");  // Certifique-se que o arquivo map.jpg esteja no mesmo diretório do executável
    Texture2D mapTexture = LoadTextureFromImage(mapImage);

    // Liberar a memória usada pela imagem (já não precisamos mais dela)
    UnloadImage(mapImage);

    // Configurar o jogo ou mapa, se necessário

    // Loop principal do jogo
    while (!WindowShouldClose())    // Detectar a janela de fechamento
    {
        // Começar a desenhar
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Desenhar a textura (mapa) na tela
        DrawTexture(mapTexture, 0, 0, WHITE);

        // Adicionar outros desenhos e lógicas do jogo, se necessário

        EndDrawing();
    }

    // Descarregar a textura (liberar memória)
    UnloadTexture(mapTexture);

    // Fechar janela e limpar recursos
    CloseWindow();

    return 0;
}
