#include "savestate.h"

#include "cfg.h"
#include "text_manager.h"

#include "game/area.h"
#include "game/camera.h"
#include "game/game.h"
#include "game/print.h"
#include "game/level_update.h"
#include "libc/string.h"

#define StateSize 0x26B28

void set_play_mode(s16 playMode);

static bool mustSaveState = true;

static void resetCamera()
{
    if (CAMERA_MODE_BEHIND_MARIO  == gCamera->mode
     || CAMERA_MODE_WATER_SURFACE == gCamera->mode
     || CAMERA_MODE_INSIDE_CANNON == gCamera->mode
     || CAMERA_MODE_CLOSE         == gCamera->mode)
    {
        set_camera_mode(gMarioStates->area->camera, gMarioStates->area->camera->defMode, 1);
    }

    if (CUTSCENE_ENTER_BOWSER_ARENA != gMarioStates->area->camera->cutscene)
    {
        gMarioStates->area->camera->cutscene = 0;
    }
}

void SaveState_onNormal()
{
    // TODO: Remove hardcode
    State* state = (State*) (0x80026000);
    if (mustSaveState)
    {
        mustSaveState = false;
        state->area  = gCurrAreaIndex;
        state->level = gCurrCourseNum;
        state->size = sizeof(State);
        memcpy(state->memory, &gMarioStates, StateSize);
    }
    else
    {
        if (Config_action() == Config_ButtonAction_LOAD_STATE)
        {
            if (state->area == gCurrAreaIndex && state->level == gCurrCourseNum)
            {
                memcpy(&gMarioStates, state->memory, StateSize);
                resetCamera();
            }
        }
    }
}

void SaveState_onPause()
{
    if ((Config_saveStateStyle() == Config_StateSaveStyle_PAUSE  && !mustSaveState)
     || (Config_saveStateStyle() == Config_StateSaveStyle_BUTTON && Config_action() == Config_ButtonAction_LOAD_STATE))
    {
        mustSaveState = true;
        TextManager_addLine("STATE SET", 30);
    }
}
