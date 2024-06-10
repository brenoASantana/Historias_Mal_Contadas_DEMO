#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

typedef enum {
    FADE_IN,
    FULL_DISPLAY,
    FADE_OUT
} TextState;

#define FADE_SPEED 0.05f  // Define a velocidade de fade aqui

char *ReadTextFile(const char *filename);
void DrawTextWithFade(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, float *alpha, TextState *state);

#endif // TEXT_H
