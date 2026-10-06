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
static u8* _hackticeStateDataStart0 = (u8*) &gMarioStates;
static u8* _hackticeStateDataEnd0 = ((u8*) &gMarioStates) + 0x26B28;
static u8* _hackticeStateDataStart1 = 0;
static u8* _hackticeStateDataEnd1 = 0;
#else
extern u8 _hackticeStateDataStart0[];
extern u8 _hackticeStateDataEnd0[];
extern u8 _hackticeStateDataStart1[];
extern u8 _hackticeStateDataEnd1[];
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
        Hacktice_gState->area  = gCurrAreaIndex;
        Hacktice_gState->level = gCurrLevelNum;
        Hacktice_gState->size = sizeof(State);
        u8* memory = (u8*) Hacktice_gState->memory;
#define STATE_MEM_PUSH(dest, src, size) memcpy(dest, src, size); dest += (size);
        STATE_MEM_PUSH(memory, _hackticeStateDataStart0, _hackticeStateDataEnd0 - _hackticeStateDataStart0);
        // TODO: Does not work yet... Savestate is too short
        // STATE_MEM_PUSH(memory, _hackticeStateDataStart1, _hackticeStateDataEnd1 - _hackticeStateDataStart1);
        // STATE_MEM_PUSH(memory, gMarioAnimsMemAlloc     , MARIO_ANIMS_POOL_SIZE);
        // STATE_MEM_PUSH(memory, &gMarioAnimsBuf         , sizeof(gMarioAnimsBuf));
#undef STATE_MEM_PUSH
    }
    else
    {
        if (Config_action() == Config_ButtonAction_LOAD_STATE)
        {
            if (Hacktice_gState->area == gCurrAreaIndex && Hacktice_gState->level == gCurrLevelNum)
            {
                Vec3f pos = { gMarioStates->pos[0], gMarioStates->pos[1], gMarioStates->pos[2]};
                u8* memory = (u8*) Hacktice_gState->memory;
#define STATE_MEM_POP(dest, src, size) memcpy(dest, src, size); src += (size);
                STATE_MEM_POP(_hackticeStateDataStart0, memory, _hackticeStateDataEnd0 - _hackticeStateDataStart0);
                // STATE_MEM_POP(_hackticeStateDataStart1, memory, _hackticeStateDataEnd1 - _hackticeStateDataStart1);
                // STATE_MEM_POP(gMarioAnimsMemAlloc     , memory, MARIO_ANIMS_POOL_SIZE);
                // STATE_MEM_POP(&gMarioAnimsBuf         , memory, sizeof(gMarioAnimsBuf));
#undef STATE_MEM_POP
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
