#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>
#include <unistd.h>

// Função para comparar duas cores
bool ColorEqual(Color a, Color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

int main(void) {
    // Inicialização da janela
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Detector de Colisões com Câmera e Raylib");

    // Arquivo de mapa
    const char *mapFilePath = "assets/map.png"; // Inclua a extensão do arquivo

    // Verificando o caminho atual
    char currentPath[1024];
    getcwd(currentPath, sizeof(currentPath));
    printf("Current working directory: %s\n", currentPath);

    // Verificando o arquivo
    FILE *file = fopen(mapFilePath, "r");
    if (file) {
        fclose(file);
    } else {
        printf("Erro: Arquivo %s não encontrado\n", mapFilePath);
        CloseWindow();
        return -1;
    }

    // Carregar o mapa
    Image mapImage = LoadImage(mapFilePath);
    if (mapImage.data == NULL) {
        printf("Erro: Falha ao carregar a imagem %s\n", mapFilePath);
        CloseWindow();
        return -1;
    }

    Texture2D mapTexture = LoadTextureFromImage(mapImage);
    Color *mapPixels = LoadImageColors(mapImage);

    // Definir a cor de colisão - Coloquei (RGB 0, 0, 0) com base no photoshop
    Color collisionColor = (Color){ 0, 0, 0, 255 };

    // Tamanho do bloco (assumindo que os blocos são quadrados)
    int blockSize = 32;

    // Dimensões do mapa
    int mapWidth = mapImage.width;
    int mapHeight = mapImage.height;

    // Calcula as coordenadas X e Y do bloco 300 (Chutei uma posAxi pra ficar dentro do labirinto)
    int blockX = 300 % (mapWidth / blockSize) * blockSize;
    int blockY = 300 / (mapWidth / blockSize) * blockSize;

    // Posição inicial do jogador (centro do bloco 300)
    Vector2 playerPosition = { blockX + blockSize / 2, blockY + blockSize / 2 };
    float playerSpeed = 2.0f;
    float playerRadius = 10.0f;

    // Inicializar a câmera
    Camera2D camera = { 0 };
    camera.target = playerPosition;
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Movimento do jogador com verificação de colisão
        Vector2 newPlayerPosition = playerPosition;

        if (IsKeyDown(KEY_RIGHT)) newPlayerPosition.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT)) newPlayerPosition.x -= playerSpeed;
        if (IsKeyDown(KEY_UP)) newPlayerPosition.y -= playerSpeed;
        if (IsKeyDown(KEY_DOWN)) newPlayerPosition.y += playerSpeed;

        // Verificar colisão
        bool collision = false;
        for (int y = -playerRadius; y <= playerRadius; y++) {
            for (int x = -playerRadius; x <= playerRadius; x++) {
                if (x * x + y * y <= playerRadius * playerRadius) {
                    int checkX = (int)newPlayerPosition.x + x;
                    int checkY = (int)newPlayerPosition.y + y;

                    if (checkX >= 0 && checkX < mapWidth && checkY >= 0 && checkY < mapHeight) {
                        int pixelIndex = checkY * mapWidth + checkX;
                        Color pixelColor = mapPixels[pixelIndex];

                        if (ColorEqual(pixelColor, collisionColor)) {
                            collision = true;
                            break;
                        }
                    }
                }
            }
            if (collision) break;
        }

        if (!collision) {
            playerPosition = newPlayerPosition;
        }

        // Atualizar a câmera
        camera.target = playerPosition;

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        // Desenhar o mapa
        DrawTexture(mapTexture, 0, 0, WHITE);

        // Desenhar o jogador
        DrawCircleV(playerPosition, playerRadius, BLUE);

        EndMode2D();

        EndDrawing();
    }

    // Descarregar recursos
    UnloadImageColors(mapPixels);
    UnloadTexture(mapTexture);
    UnloadImage(mapImage);

    CloseWindow();

    return 0;
}
