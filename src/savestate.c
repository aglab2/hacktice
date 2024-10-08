#include "savestate.h"

#include "binary.h"
#include "compress.h"
#include "cfg.h"
#include "text_manager.h"

#include "game/area.h"
#include "game/camera.h"
#include "game/display.h"
#include "game/print.h"
#include "game/level_update.h"
#include "libc/string.h"
#include "libc/stdio.h"

void set_play_mode(s16 playMode);

#ifdef BINARY
static u8* _hackticeStateDataStart = (u8*) &gMarioStates;
static u8* _hackticeStateDataEnd = ((u8*) &gMarioStates) + 0x26B28;
#else
State Hacktice_gState[1];
extern u8 _hackticeStateDataStart[];
extern u8 _hackticeStateDataEnd[];
#endif

#define IS_DECADES_LATER (0x8C63E074U == (*(uint32_t*) 0x802C99C4))
extern struct GfxPool gGfxPools[2];

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
        Hacktice_gState->area  = gCurrAreaIndex;
        Hacktice_gState->level = gCurrLevelNum;
        Hacktice_gState->size = sizeof(State);
        uint32_t stateSize = mlz4_compress(_hackticeStateDataStart, _hackticeStateDataEnd - _hackticeStateDataStart, Hacktice_gState->memory);
        // Decades Later extra logic
        if (IS_DECADES_LATER)
        {
            uint32_t exStateSize = mlz4_compress((uint8_t*) gGfxPools, sizeof(gGfxPools), Hacktice_gState->memory + stateSize);
            static char buf[16];
            sprintf(buf, "%d %d", stateSize, exStateSize);
            TextManager_addLine(buf, 30);
        }
    }
    else
    {
        if (Config_action() == Config_ButtonAction_LOAD_STATE)
        {
            if (Hacktice_gState->area == gCurrAreaIndex && Hacktice_gState->level == gCurrLevelNum)
            {
                uint32_t compressedSize = mlz4_decompress(Hacktice_gState->memory, _hackticeStateDataStart);
                if (IS_DECADES_LATER)
                {
                    mlz4_decompress(Hacktice_gState->memory + compressedSize, (uint8_t*) gGfxPools);
                }
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
