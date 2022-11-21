#include "types.h"

#include "game/level_update.h"

#include "action.h"
#include "checkpoint.h"
#include "cfg.h"
#include "death.h"
#include "death_floor.h"
#include "distance.h"
#include "input_viewer.h"
#include "interaction.h"
#include "level_reset.h"
#include "levitate.h"
#include "music.h"
#include "savestate.h"
#include "shared.h"
#include "speed.h"
#include "status.h"
#include "text_manager.h"
#include "timer.h"
#include "wallkick_frame.h"

#define PLAY_MODE_NORMAL 0
#define PLAY_MODE_PAUSED 2

void onFrame()
{
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

        Checkpoint_onNormal();
        
        Action_onNormal();
    }

    Timer_onFrame();
    TextManager_onFrame();
}

void onPause()
{
    SaveState_onPause();
    Config_onPause();
}

uintptr_t _start[] = {
    (uintptr_t) onFrame,
    (uintptr_t) onPause,
    (uintptr_t) Music_setVolumeHook,
    (uintptr_t) DeathFloor_checkDeathBarrierHook,
    HACKTICE_CANARY,
    HACKTICE_MAKE_VERSION(1, 3, 0),
    HACKTICE_STATUS_INIT,
    (uintptr_t) &sConfig,
    (uintptr_t) 0x80026000,
};
