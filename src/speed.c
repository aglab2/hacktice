#include "speed.h"

#include "cfg.h"
#include "text_manager.h"

#include "game/level_update.h"
#include "libc/stdio.h"

static char sSpeedLine[16];

void Speed_onNormal()
{
    if (!Config_showSpeed())
        return;

    sprintf(sSpeedLine, "S %.1f", (f64) gMarioStates->forwardVel);
    TextManager_addLine(sSpeedLine, 1);
}
