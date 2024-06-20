#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

typedef struct {
    Texture2D down;
    Texture2D left;
    Texture2D right;
    Texture2D up;
    Texture2D cross_down;
    Texture2D cross_left;
    Texture2D cross_right;
    Texture2D cross_up;
} PlayerTextures;

extern PlayerLevelTwo playerLevelTwo; // Declaração externa
extern Enemy *enemies;
extern int enemyCount;
extern int defeatedEnemies;

// Declaração das texturas

PlayerTextures LoadPlayerTextures(void);
void UnloadPlayerTextures(PlayerTextures textures);
void PlayerLevelTwoUpdate(float deltaTime);
void PlayerLevelTwoAttack(void);
void DrawPlayerLevelTwo(PlayerTextures textures);

PlayerTextures LoadPlayerTextures(void)
{
    PlayerTextures textures;
    textures.down = LoadTexture("../assets/images/sprites/player_down");
    textures.left = LoadTexture("../assets/images/sprites/player_left");
    textures.right = LoadTexture("../assets/images/sprites/player_right");
    textures.up = LoadTexture("../assets/images/sprites/player_up");
    textures.cross_down = LoadTexture("../assets/images/sprites/player_cross_down.png");
    textures.cross_left = LoadTexture("../assets/images/sprites/player_cross_left.png");
    textures.cross_right = LoadTexture("../assets/images/sprites/player_cross_right.png");
    textures.cross_up = LoadTexture("../assets/images/sprites/player_cross_up.png");
    return textures;
}


int main(void)
{
    // Carregar as texturas do player
    PlayerTextures playerTextures = LoadPlayerTextures();

    // Inicialização do player
    playerLevelTwo.position = (Vector2){400, 300};
    playerLevelTwo.attackCooldown = 0;
    playerLevelTwo.isAttacking = false;

    // Descarregar as texturas quando não forem mais necessárias
    UnloadPlayerTextures(playerTextures);

    return 0;
}

void PlayerLevelTwoUpdate(float deltaTime)
{
    bool moving = false;

    if (IsKeyDown(KEY_UP)) {
        playerLevelTwo.position.y -= PLAYERLEVELTWO_SPEED * deltaTime;
        moving = true;
    }
    if (IsKeyDown(KEY_DOWN)) {
        playerLevelTwo.position.y += PLAYERLEVELTWO_SPEED * deltaTime;
        moving = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        playerLevelTwo.position.x -= PLAYERLEVELTWO_SPEED * deltaTime;
        moving = true;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        playerLevelTwo.position.x += PLAYERLEVELTWO_SPEED * deltaTime;
        moving = true;
    }

    // Limitar o movimento do player dentro da tela
    if (playerLevelTwo.position.x < PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.x = PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.x > GetScreenWidth() - PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.x = GetScreenWidth() - PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.y < PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.y = PLAYERLEVELTWO_SIZE / 2;
    if (playerLevelTwo.position.y > GetScreenHeight() - PLAYERLEVELTWO_SIZE / 2)
        playerLevelTwo.position.y = GetScreenHeight() - PLAYERLEVELTWO_SIZE / 2;

    if (playerLevelTwo.attackCooldown > 0)
    {
        playerLevelTwo.attackCooldown -= deltaTime;
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        playerLevelTwo.isAttacking = true;
        playerLevelTwo.attackCooldown = ATTACK_COOLDOWN;
        PlayerLevelTwoAttack();
    }
    else
    {
        playerLevelTwo.isAttacking = false;
    }
}

void PlayerLevelTwoAttack(void)
{
    for (int i = 0; i < enemyCount; i++)
    {
        if (enemies[i].active && CheckCollisionCircles(playerLevelTwo.position, ATTACK_RANGE, enemies[i].position, ENEMY_SIZE / 2))
        {
            enemies[i].active = false;
            defeatedEnemies++;
        }
    }
}

void DrawPlayerLevelTwo(PlayerTextures textures)
{
    int spriteIndex = 0;
    Texture2D currentTexture = textures.down;

    // Selecionar a textura correta com base na direção e ataque
    if (playerLevelTwo.isAttacking) {
        if (IsKeyDown(KEY_UP))
            currentTexture = textures.cross_up; // Ataque para cima
        else if (IsKeyDown(KEY_DOWN))
            currentTexture = textures.cross_down; // Ataque para baixo
        else if (IsKeyDown(KEY_LEFT))
            currentTexture = textures.cross_left; // Ataque para a esquerda
        else if (IsKeyDown(KEY_RIGHT))
            currentTexture = textures.cross_right; // Ataque para a direita
    } else {
        if (IsKeyDown(KEY_UP))
            currentTexture = textures.up; // Andando para cima
        else if (IsKeyDown(KEY_DOWN))
            currentTexture = textures.down; // Andando para baixo
        else if (IsKeyDown(KEY_LEFT))
            currentTexture = textures.left; // Andando para a esquerda
        else if (IsKeyDown(KEY_RIGHT))
            currentTexture = textures.right; // Andando para a direita
    }

    // Desenhar a textura do player
    DrawTexture(currentTexture, playerLevelTwo.position.x - currentTexture.width / 2, playerLevelTwo.position.y - currentTexture.height / 2, WHITE);
}

void UnloadPlayerTextures(PlayerTextures textures)
{
    UnloadTexture(textures.down);
    UnloadTexture(textures.left);
    UnloadTexture(textures.right);
    UnloadTexture(textures.up);
    UnloadTexture(textures.cross_down);
    UnloadTexture(textures.cross_left);
    UnloadTexture(textures.cross_right);
    UnloadTexture(textures.cross_up);
}