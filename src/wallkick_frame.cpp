#include "wallkick_frame.h"
extern "C"
{
    #include "game/level_update.h"
    #include "libc/string.h"
}
#include "action.h"
#include "checkpoint.h"
#include "text_manager.h"
#include "sm64.h"

#include "cfg.h"

static const char* sWallkickLines[] = 
{
    "1ST",
    "2ND",
    "3RD",
    "4TH",
    "5TH",
};
static char sPrintedLine[4];

auto sLastWallkickTimer = 0;
void WallkickFrame::onNormal()
{
    if (Action::changed())
    {
        if (gMarioStates->action == ACT_WALL_KICK_AIR && Action::last() != ACT_CLIMBING_POLE && Action::last() != ACT_HOLDING_POLE)
        {
            if (sLastWallkickTimer)
            {
                memcpy(sPrintedLine, sWallkickLines[6 - sLastWallkickTimer], 4);
            }
            else
            {
                memcpy(sPrintedLine, *sWallkickLines, 4);
            }        
            if (Config::showWallkickFrame())
                TextManager::addLine(sPrintedLine, 30);

            if (Config::checkpointWallkick())
                Checkpoint::registerEvent();
        }
    }
    sLastWallkickTimer = gMarioStates->wallKickTimer;
}
