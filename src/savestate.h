#pragma once

#include "types.h"

void SaveState_onPause();
void SaveState_onNormal();

typedef struct
{
    s32 size;
    s16 level;
    s16 area;
    char memory[0];
} State;
