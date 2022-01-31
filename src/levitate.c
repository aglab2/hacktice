#include "levitate.h"

#include "cfg.h"
#include "sm64.h"

#include "game/level_update.h"

void Levitate_onNormal()
{
    if (Config_ButtonAction_LEVITATE == Config_action())
    {
        gMarioStates->vel[1] = 30.f;
        gMarioStates->action = ACT_JUMP;
    }
}
