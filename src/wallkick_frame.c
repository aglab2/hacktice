#include "wallkick_frame.h"

#include "game/level_update.h"
#include "libc/string.h"

#include "action.h"
#include "checkpoint.h"
#include "libc/stdio.h"
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
static char sPrintedLine[6];
static int sLastWallkickTimer = 0;

void WallkickFrame_onNormal()
{
    if (Action_changed())
    {
        if (gMarioStates->action == ACT_WALL_KICK_AIR && Action_last() != ACT_CLIMBING_POLE && Action_last() != ACT_HOLDING_POLE)
        {
            if (Config_showWallkickFrame())
            {
                if (sLastWallkickTimer)
                {
                    if (1 < sLastWallkickTimer && sLastWallkickTimer <= 6)
                        memcpy(sPrintedLine, sWallkickLines[6 - sLastWallkickTimer], 4);
                    else
                        // this is educated guess
                        sprintf(sPrintedLine, "W %d", 6 - sLastWallkickTimer);
                }
                else
                {
                    memcpy(sPrintedLine, *sWallkickLines, 4);
                }        
                TextManager_addLine(sPrintedLine, 30);
            }

            if (Config_checkpointWallkick())
            {
                Checkpoint_registerEvent();
            }
        }
    }
    sLastWallkickTimer = gMarioStates->wallKickTimer;
}
