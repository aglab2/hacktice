#pragma once

#include "level_conv.h"

namespace Config
{
    void onPause();

    enum class StickStyle
    {
        OFF,
        VALUE,
        GRAPHICS,  
    };
    StickStyle showStick();

    bool showButtons();

    enum class ButtonAction
    {
        OFF,
        ACT_SELECT,
        LEVEL_RESET,
        LEVEL_RESET_WARP,
        LEVITATE,
        LOAD_STATE,
    };
    ButtonAction action();

    LevelConv::PlainLevels warpId();
    LevelConv::PlainLevels warpIdAndReset();

    bool showWallkickFrame();
    bool showDistanceFromClosestRed();
    bool showDistanceFromClosestSecret();

    bool showSpeed();

    bool timerShow();
    enum class TimerStyle
    {
        GRAB,
        XCAM,
    };
    TimerStyle timerStyle();
    bool timerStopOnCoinStar();

    enum class StateSaveStyle
    {
        BUTTON,
        PAUSE,
    };
    StateSaveStyle saveStateStyle();

    bool muteMusic();
    
    bool checkpointWallkick();
    bool checkpointDoor();
    bool checkpointPole();
    bool checkpointLava();
    bool checkpointGroundpound();
    bool checkpointBurning();
    bool checkpointCannon();
    bool checkpointWarp();
    bool checkpointRed();
};
