#include "checkpoint.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
    #include "libc/stdio.h"
}
#include "action.h"
#include "cfg.h"
#include "text_manager.h"
#include "sm64.h"

static bool sShow = false;

static void addTimeLine()
{
    static char sLine[] = "X XX XX";

    auto time = gHudDisplay.timer;
    auto ms = (int) (3.33333f * (time % 30));
    auto s = (time / 30) % 60;
    auto m = time / 30 / 60;

    sprintf(sLine, "%01d %02d %02d", m, s, ms);
    TextManager::addLine(sLine, 30);
}

void Checkpoint::onNormal()
{
    if (sShow)
    {
        sShow = false;
        return addTimeLine();
    }

    if (!Action::changed())
        return;

#define ADD_TIME_ON_EVENT(cond, act) if (Config::checkpoint##cond() && gMarioStates->action == act) addTimeLine();
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

void Checkpoint::registerEvent()
{
    sShow = true;
}
