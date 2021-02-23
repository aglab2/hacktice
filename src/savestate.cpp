#include "savestate.h"

extern "C"
{
    #include "game/area.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "libc/string.h"

    extern "C" void set_play_mode(s16 playMode);
}
#include "cfg.h"
#include "text_manager.h"

constexpr int StateSize = 0x26B28;

struct State
{
    s8 level;
    s8 area;
    char memory[StateSize];
};

static bool mustSaveState = true;

void SaveState::onNormal()
{
    auto state = (State*) (0x80026000);
    if (mustSaveState)
    {
        mustSaveState = false;
        state->area  = gCurrAreaIndex;
        state->level = gCurrCourseNum;
        memcpy(state->memory, &gMarioStates, StateSize);
    }
    else
    {
        if (Config::action() == Config::ButtonAction::LOAD_STATE)
        {
            if (state->area == gCurrAreaIndex && state->level == gCurrCourseNum)
            {
                memcpy(&gMarioStates, state->memory, StateSize);
            }
        }
    }
}

void SaveState::onPause()
{
    if ((Config::StateSaveStyle() == Config::StateSaveStyle::PAUSE  && !mustSaveState)
     || (Config::StateSaveStyle() == Config::StateSaveStyle::BUTTON && Config::action() == Config::ButtonAction::LOAD_STATE))
    {
        mustSaveState = true;
        TextManager::addLine("STATE SET", 30);
    }
}
