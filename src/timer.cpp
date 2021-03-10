#include "timer.h"
extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
}
#include "action.h"
#include "cfg.h"
#include "checkpoint.h"
#include "sm64.h"

bool sGrabTimerSet = false;

void Timer::reset()
{
    sGrabTimerSet = false;
}

void Timer::onFrame()
{
    if (Config::timerShow())
    {
        if (gHudDisplay.flags & HUD_DISPLAY_FLAG_COIN_COUNT)
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_TIMER;
        else
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
    }
    else
    {
        gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
    }

    //if (!Action::changed())
    //    return;

    bool grabCondition = gMarioStates->action == ACT_FALL_AFTER_STAR_GRAB;
    bool xcamCondition = gMarioStates->action == ACT_STAR_DANCE_WATER || gMarioStates->action == ACT_STAR_DANCE_EXIT;
    bool timerCondition = grabCondition || xcamCondition;

    if (Config::timerStyle() == Config::TimerStyle::GRAB)
    {
        if (timerCondition)
            sTimerRunning = false;
    }

    if (Config::timerStyle() == Config::TimerStyle::XCAM)
    {
        if (xcamCondition)
            sTimerRunning = false;
        
        if (grabCondition && !sGrabTimerSet)
        {
            sGrabTimerSet = true;
            Checkpoint::registerEvent();
        }
    }

    if (gMarioStates->action == ACT_STAR_DANCE_NO_EXIT)
        if (!Config::timerStopOnCoinStar())
        {
            sTimerRunning = true;
        }
}