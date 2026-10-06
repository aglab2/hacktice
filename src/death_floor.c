#include "death_floor.h"

#include "audio/external.h"
#include "game/level_update.h"
#include "sm64.h"

#include "binary.h"
#include "cfg.h"
#include "death.h"

void DeathFloor_checkDeathBarrierHook(struct MarioState *m)
{
    Config_DeathAction action = Config_deathAction();
    if (action != Config_DeathAction_OFF)
    {
        Death_TouchedDeathFloor = true;
    }
    else if (level_trigger_warp(m, WARP_OP_WARP_FLOOR) == 20 && !(m->flags & MARIO_FALL_SOUND_PLAYED)) 
    {
        play_sound(SOUND_MARIO_WAAAOOOW, m->marioObj->header.gfx.cameraToObject);
    }
}
