#include "speed.h"

#include "cfg.h"
#include "text_manager.h"

#include "game/level_update.h"
#include "libc/stdio.h"

char speedLine[16];

void Speed_onNormal()
{
    if (!Config_showSpeed())
        return;

    sprintf(speedLine, "S %.1f", gMarioStates->forwardVel);
    TextManager_addLine(speedLine, 1);
}
