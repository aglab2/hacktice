#include "action.h"
extern "C"
{
    #include "game/level_update.h"
}

int sLastAction = 0;
void Action::onNormal()
{
    sLastAction = gMarioStates->action;
}

int Action::last()
{
    return sLastAction;
}

bool Action::changed()
{
    return sLastAction != gMarioStates->action;
}
