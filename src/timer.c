#include "timer.h"

#include "game/level_update.h"
#include "game/print.h"

#include "action.h"
#include "cfg.h"
#include "checkpoint.h"
#include "sm64.h"

static bool sGrabTimerSet = false;

void Timer_reset()
{
    sGrabTimerSet = false;
}

void Timer_onFrame()
{
    if (Config_timerShow())
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

    //if (!Action_changed())
    //    return;

    bool grabCondition = gMarioStates->action == ACT_FALL_AFTER_STAR_GRAB;
    bool xcamCondition = gMarioStates->action == ACT_STAR_DANCE_WATER || gMarioStates->action == ACT_STAR_DANCE_EXIT;
    bool timerCondition = grabCondition || xcamCondition;

    if (Config_timerStyle() == Config_TimerStyle_GRAB)
    {
        if (timerCondition)
            sTimerRunning = false;
    }

    if (Config_timerStyle() == Config_TimerStyle_XCAM)
    {
        if (xcamCondition)
            sTimerRunning = false;
        
        if (grabCondition && !sGrabTimerSet)
        {
            sGrabTimerSet = true;
            Checkpoint_registerEvent();
        }
    }

    if (gMarioStates->action == ACT_STAR_DANCE_NO_EXIT)
        if (!Config_timerStopOnCoinStar())
        {
            sTimerRunning = true;
        }
}