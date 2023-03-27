#pragma once

#include "game/area.h"

void LevelReset_onNormal();
s32 LevelReset_onSpawnObjectsFromInfoHook(struct SpawnInfo* spawnInfo);
void LevelReset_setObjectRespawnInfoBits(struct Object *obj, u8 bits) ;
