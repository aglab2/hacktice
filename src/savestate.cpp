#include "savestate.h"

#include "cfg.h"
#include "text_manager.h"

extern "C"
{
    #include "game/area.h"
    #include "game/camera.h"
    #include "game/game.h"
    #include "game/print.h"
    #include "game/level_update.h"
    #include "libc/string.h"

    extern "C" void set_play_mode(s16 playMode);
}

constexpr int StateSize = 0x26B28;

struct State
{
    s8 level;
    s8 area;
    char memory[StateSize];
};

static bool mustSaveState = true;

static void resetCamera()
{
    auto m = gMarioStates;
    if (CAMERA_MODE_BEHIND_MARIO  == gCamera->mode
     || CAMERA_MODE_WATER_SURFACE == gCamera->mode
     || CAMERA_MODE_INSIDE_CANNON == gCamera->mode
     || CAMERA_MODE_CLOSE         == gCamera->mode)
    {
        set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    }

    m->area->camera->cutscene = 0;
}

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
                resetCamera();
            }
        }
    }
}

void SaveState::onPause()
{
    if ((Config::saveStateStyle() == Config::StateSaveStyle::PAUSE  && !mustSaveState)
     || (Config::saveStateStyle() == Config::StateSaveStyle::BUTTON && Config::action() == Config::ButtonAction::LOAD_STATE))
    {
        mustSaveState = true;
        TextManager::addLine("STATE SET", 30);
    }
}
