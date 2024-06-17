#ifndef PLAYERLEVELONE_H
#define PLAYERLEVELONE_H

#include "raylib.h"

typedef struct PlayerLevelOne {
    int position;
    bool hasKey;
} PlayerLevelOne;

/*Posições
0 - Está no spawn
1 - Está perto da porta
2 - Está perto da mesa
*/

PlayerLevelOne CreatePlayerLevelOne();

#endif // PLAYERLEVELONE_H
