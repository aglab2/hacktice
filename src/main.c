#include "types.h"

#include "game/game.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"

#include "action.h"
#include "checkpoint.h"
#include "cfg.h"
#include "custom_text.h"
#include "death.h"
#include "death_floor.h"
#include "debug_box.h"
#include "distance.h"
#include "input_viewer.h"
#include "interaction.h"
#include "level_reset.h"
#include "levitate.h"
#include "music.h"
#include "savestate.h"
#include "shared.h"
#include "soft_reset.h"
#include "speed.h"
#include "status.h"
#include "text_manager.h"
#include "timer.h"
#include "version.h"
#include "wallkick_frame.h"

#define PLAY_MODE_NORMAL 0
#define PLAY_MODE_PAUSED 2

void Hacktice_onPause()
{
    SaveState_onPause();
    Config_onPause();
}

#ifdef BINARY
static bool sInitialized = 0;
static void Hacktice_onPauseStarDisplay()
{
    gSPDisplayList(gDisplayListHead++, 0x02011cc8);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);

    Hacktice_onPause();

    gSPDisplayList(gDisplayListHead++, 0x02011d50);
}
#endif

void Hacktice_onFrame()
{
    SoftReset_onFrame();

    HackticeSetStatus(HACKTICE_STATUS_ACTIVE);
    if (PLAY_MODE_NORMAL == sCurrPlayMode)
    {
        Death_onNormal();
        Distance_onNormal();
        InputViewer_onNormal();
        LevelReset_onNormal();
        Levitate_onNormal();
        SaveState_onNormal();
        Speed_onNormal();
        WallkickFrame_onNormal();
        Interaction_onNormal();
        Music_onFrame();
        Version_onFrame();
        CustomText_onFrame();

        Checkpoint_onNormal();

        Action_onNormal();
    }

    Timer_onFrame();
    TextManager_onFrame();

#ifdef BINARY
    if (!sInitialized)
    {
        sInitialized = true;
        u32 cmd = ((u32) &Hacktice_onPauseStarDisplay);
        cmd &= 0xffffff;
        cmd /= 4;
        cmd |= 0x0C000000;

        // Star Revenge 8-like star display hook, redirect to my code
        if (0x0C102000U == *(u32*) 0x802DCC48)
        {
            *(u32*) 0x802DCC48 = cmd;
        }

        // Decades Later-like star display hook, redirect to my code
        if (0x0060F809U == *(u32*) 0x802DCC4C)
        {
            *(u32*) 0x802DCC4C = cmd;
        }
    }
#endif
}

uintptr_t Hacktice_start[] = {
    (uintptr_t) Hacktice_onFrame,
    (uintptr_t) Hacktice_onPause,
    (uintptr_t) Music_setVolumeHook,
    (uintptr_t) DeathFloor_checkDeathBarrierHook,
    HACKTICE_CANARY,
#define HACKTICE_VERSION(maj, min, patch) (((maj) << 24) | ((min) << 16) | ((patch))),
#include "xversion.h"
#undef HACKTICE_VERSION
    HACKTICE_STATUS_INIT,
    (uintptr_t) &Hacktice_gConfig,
    (uintptr_t) Hacktice_gState,
    (uintptr_t) LevelReset_onSpawnObjectsFromInfoHook,
#ifdef BINARY
    (uintptr_t) LevelReset_setObjectRespawnInfoBits,
#else
    (uintptr_t) 0 /*ignored*/,
#endif
    (uintptr_t) &DebugBox_renderHook,

    (uintptr_t) &DebugBox_hitboxHook,    
    (uintptr_t) 0 /*reserved*/,
    (uintptr_t) 0 /*reserved*/,
    (uintptr_t) 0 /*reserved*/,
};

#ifndef BINARY
bool Hacktice_gEnabled = true;
#endif
