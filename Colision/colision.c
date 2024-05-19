#include "raylib.h"

// Tamanho do mapa
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 40

// Definição do mapa (1 = sólido, 0 = passável)
int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int main(void) {
    // Inicialização da janela
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Mapa com Colisões no Raylib");

    // Posição inicial do jogador
    Vector2 playerPosition = { 50, 50 };
    int playerSize = 20;
    float playerSpeed = 200.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Movimentação do jogador
        Vector2 oldPosition = playerPosition; // Salva a posição antiga para restaurar em caso de colisão
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) playerPosition.x -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_UP)) playerPosition.y -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += playerSpeed * GetFrameTime();

        // Colisão
        Rectangle playerRect = { playerPosition.x, playerPosition.y, playerSize, playerSize };
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[x][y] == 1) {
                    Rectangle tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if (CheckCollisionRecs(playerRect, tileRect)) {
                        // Reagir à colisão - restaurar posição antiga
                        playerPosition = oldPosition;
                    }
                }
            }
        }

        // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenhar o mapa
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[x][y] == 1) {
                    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GRAY);
                } else {
                    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
                }
            }
        }

        // Desenhar o jogador
        DrawRectangle(playerPosition.x, playerPosition.y, playerSize, playerSize, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
