#include "action.h"
#include "game/level_update.h"

int sLastAction = 0;
void Action_onNormal()
{
    sLastAction = gMarioStates->action;
}

int Action_last()
{
    return sLastAction;
}

bool Action_changed()
{
    return sLastAction != gMarioStates->action;
}
