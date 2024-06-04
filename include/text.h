#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h" // Presumindo que você esteja usando a biblioteca raylib

typedef enum {
    FADE_IN,
    FULL_DISPLAY,
    FADE_OUT
} TextState;

char *ReadTextFile(const char *filename);
void DrawTextWithFade(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, float *alpha, TextState *state);

#endif // TEXT_H
