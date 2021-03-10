#include "level_reset.h"
extern "C"
{
    #include "types.h"
    #include "game/camera.h"
    #include "game/game.h"
    #include "game/level_update.h"
    #include "game/envfx_snow.h"
}
#include "cfg.h"
#include "timer.h"

static bool sTimerRunningDeferred = false;

static void resetCamera()
{
    auto m = gMarioStates;
    if (CAMERA_MODE_BEHIND_MARIO  == gCamera->mode
     || CAMERA_MODE_WATER_SURFACE == gCamera->mode
     || CAMERA_MODE_INSIDE_CANNON == gCamera->mode
     || CAMERA_MODE_CLOSE         == gCamera->mode)
     set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
     m->area->camera->cutscene = 0;
}

static void resetCommon()
{
    gMarioStates->health = 0x880;
    gHudDisplay.coins = 0;
    gMarioStates->numCoins = 0;
    gSnowParticleCount = 5;
    gHudDisplay.timer = 0;
    sTimerRunning = true;
    sTimerRunningDeferred = true;
    Timer::reset();
    sWarpDest.type = 2;
    resetCamera();
}

void LevelReset::onNormal()
{
    if (sTimerRunningDeferred)
    {
        sTimerRunningDeferred = false;
        sTimerRunning = true;
        Timer::reset();
        resetCamera();
    }

    auto action = Config::action();
    if (Config::ButtonAction::LEVEL_RESET == action)
    {
        resetCommon();
    }
    
    if (Config::ButtonAction::LEVEL_RESET_WARP == action)
    {
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        resetCommon();
    }

    if (Config::ButtonAction::ACT_SELECT == action)
    {
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
    }

    auto warp = Config::warpIdAndReset();
    if (warp != LevelConv::PlainLevels::OFF)
    {
        auto sm64lvl = LevelConv::toSM64Level(warp);
        
        sWarpDest.levelNum = (u8) sm64lvl;
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
        Timer::reset();
        resetCamera();
    }
}
