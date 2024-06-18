#ifndef LEVELONE_H
#define LEVELONE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void LevelOneInit(void);
void LevelOneUpdate(void);
void LevelOneDraw(void);
void LevelOneUnload(void);
void AnalyzeInput(char *inputText);

#endif // LEVELONE_H
