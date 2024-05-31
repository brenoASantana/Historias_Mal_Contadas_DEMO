#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Image GenImageGradientRadialCustom(int width, int height, Color innerColor, Color outerColor) {
    Image image = GenImageColor(width, height, BLANK);
    Color *pixels = (Color *)image.data;

    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float maxDistance = Vector2Distance((Vector2){0, 0}, (Vector2){centerX, centerY});

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float distance = Vector2Distance((Vector2){x, y}, (Vector2){centerX, centerY});
            float t = distance / maxDistance;

            pixels[y * width + x] = (Color){
                (unsigned char)(innerColor.r * (1 - t) + outerColor.r * t),
                (unsigned char)(innerColor.g * (1 - t) + outerColor.g * t),
                (unsigned char)(innerColor.b * (1 - t) + outerColor.b * t),
                (unsigned char)(innerColor.a * (1 - t) + outerColor.a * t)
            };
        }
    }

    return image;
}

int main(void)
{
    // Inicializa a janela e a Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lanterna com Efeito de Luz e Câmera Dinâmica");

    // Carregar a imagem PNG
    Image mapImage = LoadImage("assets/map.png");  // Certifique-se que o arquivo map.png esteja no mesmo diretório do executável
    Texture2D mapTexture = LoadTextureFromImage(mapImage);

    // Liberar a memória usada pela imagem (já não precisamos mais dela)
    UnloadImage(mapImage);

    // Posição do personagem
    Vector2 playerPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    float playerSpeed = 200.0f;  // Velocidade de movimento do personagem

    // Inicializa a textura de renderização para a máscara de luz
    RenderTexture2D lightMask = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Inicializa a câmera
    Camera2D camera = { 0 };
    camera.target = playerPosition;
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    Texture2D gradientTexture; // Declarar a textura de gradiente aqui para evitar redeclaração

     // Cria a imagem de gradiente radial em volta do personagem com cor amarela
    Image gradientImage = GenImageGradientRadialCustom(150, 150, YELLOW, BLANK);
    gradientTexture = LoadTextureFromImage(gradientImage);
    UnloadImage(gradientImage);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Movimento do personagem
        if (IsKeyDown(KEY_W)) playerPosition.y -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_S)) playerPosition.y += playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_A)) playerPosition.x -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_D)) playerPosition.x += playerSpeed * GetFrameTime();
        
        // Atualiza a posição da câmera
        camera.target = playerPosition;

        // Renderiza a máscara de luz
        BeginTextureMode(lightMask);
        ClearBackground(BLACK);
        DrawTexture(gradientTexture, playerPosition.x - gradientTexture.width / 2, playerPosition.y - gradientTexture.height / 2, WHITE);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexture(mapTexture, 0, 0, WHITE);
        EndMode2D();

        DrawTextureRec(lightMask.texture, (Rectangle){ 0, 0, (float)lightMask.texture.width, (float)-lightMask.texture.height }, (Vector2){ 0, 0 }, WHITE);

        DrawText("Use WASD para mover o personagem", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(mapTexture);
    UnloadTexture(gradientTexture);
    UnloadRenderTexture(lightMask);

    CloseWindow();

    return 0;
}
