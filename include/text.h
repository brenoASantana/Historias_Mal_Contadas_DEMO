#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

char *ReadTextFile(const char *filename);
void DrawTextWithDelay(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, int textSpeed);
void GetUserInput(char *buffer, int maxLength, int *count);

#endif // TEXT_H
