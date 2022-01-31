#include "level_reset.h"

#include "types.h"
#include "game/camera.h"
#include "game/game.h"
#include "game/level_update.h"
#include "game/envfx_snow.h"

#include "cfg.h"
#include "timer.h"

static bool sTimerRunningDeferred = false;

static void resetCamera()
{
    struct MarioState* m = gMarioStates;
    if (CAMERA_MODE_BEHIND_MARIO  == gCamera->mode
     || CAMERA_MODE_WATER_SURFACE == gCamera->mode
     || CAMERA_MODE_INSIDE_CANNON == gCamera->mode
     || CAMERA_MODE_CLOSE         == gCamera->mode)
    {
        set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    }
    
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
    Timer_reset();
    sWarpDest.type = 2;
    resetCamera();
}

void LevelReset_onNormal()
{
    if (sTimerRunningDeferred)
    {
        sTimerRunningDeferred = false;
        sTimerRunning = true;
        Timer_reset();
        resetCamera();
    }

    Config_ButtonAction action = Config_action();
    if (Config_ButtonAction_LEVEL_RESET == action)
    {
        resetCommon();
    }
    
    if (Config_ButtonAction_LEVEL_RESET_WARP == action)
    {
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        resetCommon();
    }

    if (Config_ButtonAction_ACT_SELECT == action)
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

    LevelConv_PlainLevels warp = Config_warpIdAndReset();
    if (warp != LevelConv_PlainLevels_OFF)
    {
        LevelConv_SM64Levels sm64lvl = LevelConv_toSM64Level(warp);
        
        sWarpDest.levelNum = (u8) sm64lvl;
        sWarpDest.type = 2;
        sWarpDest.areaIdx = 1;
        sWarpDest.nodeId = 0xa;
        gMarioStates->health = 0x880;
        sCurrPlayMode = 0x4;
        gHudDisplay.timer = 0;
        sTimerRunning = true;
        sTimerRunningDeferred = true;
        Timer_reset();
        resetCamera();
    }
}
