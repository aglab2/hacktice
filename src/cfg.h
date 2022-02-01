#pragma once

#include "bool.h"
#include "level_conv.h"

void Config_onPause();

typedef enum Config_StickStyle
{
    Config_StickStyle_OFF,
    Config_StickStyle_VALUE,
    Config_StickStyle_GRAPHICS,  
} Config_StickStyle;
Config_StickStyle Config_showStick();

bool Config_showButtons();

typedef enum Config_ButtonAction
{
    Config_ButtonAction_OFF,
    Config_ButtonAction_ACT_SELECT,
    Config_ButtonAction_LEVEL_RESET,
    Config_ButtonAction_LEVEL_RESET_WARP,
    Config_ButtonAction_LEVITATE,
    Config_ButtonAction_LOAD_STATE,
} Config_ButtonAction;
Config_ButtonAction Config_action();

LevelConv_PlainLevels Config_warpId();
LevelConv_PlainLevels Config_warpIdAndReset();

bool Config_showWallkickFrame();
bool Config_showDistanceFromClosestRed();
bool Config_showDistanceFromClosestSecret();

bool Config_showSpeed();

bool Config_timerShow();
typedef enum Config_TimerStyle
{
    Config_TimerStyle_GRAB,
    Config_TimerStyle_XCAM,
} Config_TimerStyle;
Config_TimerStyle Config_timerStyle();
bool Config_timerStopOnCoinStar();

typedef enum Config_StateSaveStyle
{
    Config_StateSaveStyle_BUTTON,
    Config_StateSaveStyle_PAUSE,
} Config_StateSaveStyle;
Config_StateSaveStyle Config_saveStateStyle();

bool Config_muteMusic();
char Config_musicNumber();

typedef enum Config_DeathAction
{
    Config_DeathAction_OFF,
    Config_DeathAction_ACT_RESET,
    Config_DeathAction_LEVEL_RESET,
    Config_DeathAction_LOAD_STATE,
} Config_DeathAction;
Config_DeathAction Config_deathAction();

void Config_setOnDeathAction(Config_ButtonAction);

bool Config_checkpointWallkick();
bool Config_checkpointDoor();
bool Config_checkpointPole();
bool Config_checkpointLava();
bool Config_checkpointGroundpound();
bool Config_checkpointBurning();
bool Config_checkpointCannon();
bool Config_checkpointWarp();
bool Config_checkpointRed();
bool Config_checkpointCoin();
bool Config_checkpointObject();
bool Config_checkpointPlatform();
