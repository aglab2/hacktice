#include "levitate.h"

#include "cfg.h"
#include "sm64.h"
extern "C"
{
    #include "game/level_update.h"
}

void Levitate::onNormal()
{
    if (Config::ButtonAction::LEVITATE == Config::action())
    {
        gMarioStates->vel[1] = 30.f;
        gMarioStates->action = ACT_JUMP;
    }
}
