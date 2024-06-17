#include "playerLevelTwo.h"


Player CreatePlayerLevelTwo(Vector2 position)
{
    Texture2D texture = LoadTexture("assets/sprites/player.png");
    if (texture.id == 0)
    {
        printf("Error: Failed to load player texture\n");
        return (Player){0};
    }
    
    PlayerLevelTwo player = { position, texture, 100, 0, 0, 0, 0 };
    return player;
}

void UpdatePlayerLevelTwo(Player *player)
{
    if (player == NULL) {
        printf("Error: Player pointer is NULL\n");
        return;
    }

    // Atualização da lógica do jogador
    // Exemplo de atualizações
    player->hp -= player->hit;

    if (player->habilityID != 0) {
        // Aplicar habilidade
    }

    if (player->hasKey) {
        // Lógica para quando o jogador tem uma chave
    }

    if (player->atTable) {
        // Lógica para quando o jogador está na mesa
    }
}

void drawPlayer(Player player)
{
    DrawTextureEx(player.texture, (Vector2){player.position.x, player.position.y}, 0.0f, 1.0f, RAYWHITE);
}
