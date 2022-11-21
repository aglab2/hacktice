#include "death_floor.h"

#include "audio/external.h"
#include "game/level_update.h"
#include "sm64.h"

void DeathFloor_checkDeathBarrierHook(struct MarioState *m)
{        
    if (level_trigger_warp(m, WARP_OP_WARP_FLOOR) == 20 && !(m->flags & MARIO_UNKNOWN_18)) 
    {
        play_sound(SOUND_MARIO_WAAAOOOW, m->marioObj->header.gfx.cameraToObject);
    }
}
