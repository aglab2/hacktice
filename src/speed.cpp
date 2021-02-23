#include "speed.h"

#include "cfg.h"
#include "text_manager.h"
extern "C"
{
    #include "game/level_update.h"
    #include "libc/stdio.h"
}

char speedLine[16]{};

void Speed::onNormal()
{
    if (!Config::showSpeed())
        return;

    sprintf(speedLine, "S %.1f", gMarioStates->forwardVel);
    TextManager::addLine(speedLine, 1);
}
