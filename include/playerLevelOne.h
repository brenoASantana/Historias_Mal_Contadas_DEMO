#ifndef PLAYERLEVELONE_H
#define PLAYERLEVELONE_H

#include "raylib.h"

typedef struct PlayerLevelOne
{
    int position;
    bool hasKey;
} PlayerLevelOne;

/*Posições:
- 0: Player está no spawn
- 1: Player está perto da porta
- 2: Player está perto da mesa
*/

PlayerLevelOne CreatePlayerLevelOne();

#endif // PLAYERLEVELONE_H
