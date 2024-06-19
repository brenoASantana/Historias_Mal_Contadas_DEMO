#include "raylib.h"
#include "../include/levelTwo.h"

static Music music;
<<<<<<< Updated upstream

void LevelTwoInit(void)
{
    music = LoadMusicStream("../assets/sounds/musics/heilag_vagga.mp3");
    SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(music);
=======
static Music jumpscare;
void LevelTwoInit(void) {
    music = LoadMusicStream("../assets/sounds/musics/heilag_vagga.mp3");
    SetMusicVolume(music, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(music);
    
    jumpscare = LoadMusicStream("../assets/sounds/musics/sfx_johnPossessed.mp3");
    //SetMusicVolume(jumpscare, 0.20); // Set volume for music (1.0 is max level)
    PlayMusicStream(jumpscare);
    player.position = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
    player.health = PLAYER_HEALTH;
    player.color = BLUE;
    player.isAttacking = false;
    player.attackCooldown = 0;

    currentWave = 0;
    waveTimer = 0;

    enemies = NULL;
    srand(time(NULL));
    gameTime = 0;
    defeatedEnemies = 0;
    StartNextWave();

    startScreenImage = LoadTexture("../assets/Jump.png");
>>>>>>> Stashed changes
}

void LevelTwoUpdate(void)
{
    UpdateMusicStream(music);
<<<<<<< Updated upstream
    // Adicione a lógica de atualização da fase 2 aqui
}
=======
    UpdateMusicStream(jumpscare);
    switch (currentScreen) {
        case START:
            if (GetTime() - startTime > 3.0) {
                StopMusicStream(jumpscare);
                currentScreen = GAMEPLAY;
            }
            break;
>>>>>>> Stashed changes

void LevelTwoDraw(void)
{
    DrawText("Bem vindo ao inferno.", 10, 10, 20, RED);

    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
}

void LevelTwoUnload(void)
{
    UnloadMusicStream(music);
<<<<<<< Updated upstream
=======
    UnloadMusicStream(jumpscare);
    UnloadTexture(startScreenImage);
    free(enemies);
>>>>>>> Stashed changes
}
