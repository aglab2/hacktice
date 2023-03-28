#pragma once
#include "bool.h"
#include "game/level_update.h"

extern u32 Action_sLastAction;

static inline void Action_onNormal()
{
    Action_sLastAction = gMarioStates->action;
}

static inline u32 Action_last()
{
    return Action_sLastAction;
}

static inline bool Action_changed()
{
    return Action_sLastAction != gMarioStates->action;
}
