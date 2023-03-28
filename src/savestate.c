#include "savestate.h"

#include "binary.h"
#include "cfg.h"
#include "text_manager.h"

#include "game/area.h"
#include "game/camera.h"
#include "game/print.h"
#include "game/level_update.h"
#include "libc/string.h"

void set_play_mode(s16 playMode);

#ifdef BINARY
static u8* _hackticeStateDataStart = (u8*) &gMarioStates;
static u8* _hackticeStateDataEnd = ((u8*) &gMarioStates) + 0x26B28;
#else
State gHacktice_State[1];
extern u8 _hackticeStateDataStart[];
extern u8 _hackticeStateDataEnd[];
#endif

static bool sMustSaveState = 0;

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
    if (sMustSaveState)
    {
        sMustSaveState = false;
        gHacktice_State->area  = gCurrAreaIndex;
        gHacktice_State->level = gCurrLevelNum;
        gHacktice_State->size = sizeof(State);
        memcpy(gHacktice_State->memory, _hackticeStateDataStart, _hackticeStateDataEnd - _hackticeStateDataStart);
    }
    else
    {
        if (Config_action() == Config_ButtonAction_LOAD_STATE)
        {
            if (gHacktice_State->area == gCurrAreaIndex && gHacktice_State->level == gCurrLevelNum)
            {
                memcpy(_hackticeStateDataStart, gHacktice_State->memory, _hackticeStateDataEnd - _hackticeStateDataStart);
                resetCamera();
            }
        }
    }
}

void SaveState_onPause()
{
    if ((Config_saveStateStyle() == Config_StateSaveStyle_PAUSE  && !sMustSaveState)
     || (Config_saveStateStyle() == Config_StateSaveStyle_BUTTON && Config_action() == Config_ButtonAction_LOAD_STATE))
    {
        sMustSaveState = true;
        TextManager_addLine("STATE SET", 30);
    }
}
