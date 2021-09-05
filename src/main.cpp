#include "types.h"

extern "C"
{
    #include "game/level_update.h"
}

#include "cfg.h"
#include "distance.h"
#include "death.h"
#include "input_viewer.h"
#include "level_reset.h"
#include "levitate.h"
#include "savestate.h"
#include "speed.h"
#include "text_manager.h"
#include "timer.h"
#include "wallkick_frame.h"
#include "checkpoint.h"
#include "action.h"
#include "interaction.h"
#include "music.h"

#define PLAY_MODE_NORMAL 0
#define PLAY_MODE_PAUSED 2

void onFrame()
{
    if (PLAY_MODE_NORMAL == sCurrPlayMode)
    {
        Death::onNormal();
        Distance::onNormal();
        InputViewer::onNormal();
        LevelReset::onNormal();
        Levitate::onNormal();
        SaveState::onNormal();
        Speed::onNormal();
        WallkickFrame::onNormal();
        Interaction::onNormal();
        Music::onFrame();

        Checkpoint::onNormal();
        
        Action::onNormal();
    }

    Timer::onFrame();
    TextManager::onFrame();
}

void onPause()
{
    SaveState::onPause();
    Config::onPause();
}

uintptr_t _start[] = {
    (uintptr_t) onFrame,
    (uintptr_t) onPause,
    (uintptr_t) Music::setVolumeHook,
};
