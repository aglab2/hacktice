#include "checkpoint.h"

#include "game/level_update.h"
#include "game/mario.h"
#include "game/print.h"
#include "game/object_list_processor.h"
#include "libc/stdio.h"

#include "action.h"
#include "cfg.h"
#include "text_manager.h"
#include "sm64.h"

static int sWasLastNumCollidedObjects = 0;
static bool sWasLastPlatform = false;

char Checkpoint_gShow = false;

static void addTimeLine()
{
    static char sLine[] = "X XX XX";

    int time = gHudDisplay.timer;
    int ms = (int) (3.33333f * (time % 30));
    int s = (time / 30) % 60;
    int m = time / 30 / 60;

    sprintf(sLine, "%01d %02d %02d", m, s, ms);
    TextManager_addLine(sLine, 30);
}

void Checkpoint_onNormal()
{
    if (Checkpoint_gShow)
    {
        Checkpoint_gShow = false;
        return addTimeLine();
    }

    if (Config_checkpointObject())
    {
        int lastNumCollidedObjects = sWasLastNumCollidedObjects;
        int numCollidingObjs = gMarioObject ? gMarioObject->numCollidedObjs : 0;
        sWasLastNumCollidedObjects = numCollidingObjs;
        if (numCollidingObjs > lastNumCollidedObjects)
            return addTimeLine();
    }

    if (Config_checkpointPlatform())
    {
        bool wasPlatform = sWasLastPlatform;
        bool isPlatform = gMarioObject && !!gMarioObject->platform;
        sWasLastPlatform = isPlatform;
        if (!wasPlatform && isPlatform)
            return addTimeLine();
    }

    if (!Action_changed())
        return;

#define ADD_TIME_ON_EVENT(cond, act) if (Config_checkpoint##cond() && gMarioStates->action == act) addTimeLine();
    ADD_TIME_ON_EVENT(Door, ACT_PULLING_DOOR)
    ADD_TIME_ON_EVENT(Door, ACT_PUSHING_DOOR)
    ADD_TIME_ON_EVENT(Pole, ACT_GRAB_POLE_SLOW)
    ADD_TIME_ON_EVENT(Pole, ACT_GRAB_POLE_FAST)
    ADD_TIME_ON_EVENT(Lava, ACT_LAVA_BOOST_LAND)
    ADD_TIME_ON_EVENT(Lava, ACT_LAVA_BOOST)
    ADD_TIME_ON_EVENT(Groundpound, ACT_GROUND_POUND_LAND)
    ADD_TIME_ON_EVENT(Groundpound, ACT_GROUND_POUND)
    ADD_TIME_ON_EVENT(Burning, ACT_BURNING_GROUND)
    ADD_TIME_ON_EVENT(Cannon, ACT_IN_CANNON)
}
