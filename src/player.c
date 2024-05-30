#include "player.h"

Player CreatePlayer(Vector2 position)
{
    Player player = { position, LoadTexture("assets/sprites/player.png"), 100 };
    return player;
}

void UpdatePlayer(Player *player)
{
    // Atualização da lógica do jogador
}

void DrawPlayer(Player player)
{
    DrawTexture(player.texture, player.position.x, player.position.y, RAYWHITE);
}
