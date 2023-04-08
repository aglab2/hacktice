#pragma once

#include "bool.h"
#include "level_conv.h"
#include "types.h"

extern char Config_gWarp;
extern char Config_gMusicNumber;
extern char Config_gOnDeathAction;

typedef struct
{
    u32 magic;
    u32 selfSize;
    char speed;
    char stickStyle;
    char showButtons;
    char lAction;
    char lRAction;
    char cButtonsAction;
    char dpadDownAction;
    char wallkickFrame;
    char distanceFromClosestRed;
    char distanceFromClosestSecret;
    char distanceFromClosestPiranha;
    char distanceFromClosestPanel;
    char timerShow;
    char timerStyle;
    char timerStopOnCoinStar;
    char stateSaveStyle;
    char muteMusic;
    char deathAction;
    char dpadUpAction;
    char warpWheel;

    char checkpointWallkick;
    char checkpointDoor;
    char checkpointPole;
    char checkpointLava;
    char checkpointGroundpound;
    char checkpointBurning;
    char checkpointCannon;
    char checkpointWarp;
    char checkpointRed;
    char checkpointCoin;
    char checkpointObject;
    char checkpointPlatform;

    char customText[27];
    char _customTextReserved; // must be always '\0'

    char showCustomText;
    char softReset;
    char _pad0;
    char _pad1;
} Config;

extern Config Hacktice_gConfig;

void Config_onPause();

typedef enum Config_StickStyle
{
    Config_StickStyle_OFF,
    Config_StickStyle_VALUE,
    Config_StickStyle_GRAPHICS,  
} Config_StickStyle;
static inline Config_StickStyle Config_showStick() { return (Config_StickStyle) Hacktice_gConfig.stickStyle; }
static inline bool Config_showButtons() { return Hacktice_gConfig.showButtons; }

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

LevelConv_PlainLevels Config_warpIdAndReset();

static inline bool Config_showWallkickFrame() { return Hacktice_gConfig.wallkickFrame; }
static inline bool Config_showDistanceFromClosestRed() { return Hacktice_gConfig.distanceFromClosestRed; }
static inline bool Config_showDistanceFromClosestSecret() { return Hacktice_gConfig.distanceFromClosestSecret; }
static inline bool Config_showSpeed() { return Hacktice_gConfig.speed; }
static inline bool Config_timerShow() { return Hacktice_gConfig.timerShow; }

typedef enum Config_TimerStyle
{
    Config_TimerStyle_GRAB,
    Config_TimerStyle_XCAM,
} Config_TimerStyle;
static inline Config_TimerStyle Config_timerStyle() { return (Config_TimerStyle) Hacktice_gConfig.timerStyle; }
static inline bool Config_timerStopOnCoinStar() { return Hacktice_gConfig.timerStopOnCoinStar; }

typedef enum Config_StateSaveStyle
{
    Config_StateSaveStyle_BUTTON,
    Config_StateSaveStyle_PAUSE,
} Config_StateSaveStyle;
static inline Config_StateSaveStyle Config_saveStateStyle() { return (Config_StateSaveStyle) Hacktice_gConfig.stateSaveStyle; }

static inline bool Config_muteMusic() { return Hacktice_gConfig.muteMusic; }
static inline char Config_musicNumber() { return Config_gMusicNumber; }

typedef enum Config_DeathAction
{
    Config_DeathAction_OFF,
    Config_DeathAction_ACT_RESET,
    Config_DeathAction_LEVEL_RESET,
    Config_DeathAction_LOAD_STATE,
} Config_DeathAction;
static inline Config_DeathAction Config_deathAction() { return (Config_DeathAction) Hacktice_gConfig.deathAction; }
static inline void Config_setOnDeathAction(Config_ButtonAction act) { Config_gOnDeathAction = (u8) act; }

static inline bool Config_checkpointWallkick() { return Hacktice_gConfig.checkpointWallkick; }
static inline bool Config_checkpointDoor() { return Hacktice_gConfig.checkpointDoor; }
static inline bool Config_checkpointPole() { return Hacktice_gConfig.checkpointPole; }
static inline bool Config_checkpointLava() { return Hacktice_gConfig.checkpointLava; }
static inline bool Config_checkpointGroundpound() { return Hacktice_gConfig.checkpointGroundpound; }
static inline bool Config_checkpointBurning() { return Hacktice_gConfig.checkpointBurning; }
static inline bool Config_checkpointCannon() { return Hacktice_gConfig.checkpointCannon; }
static inline bool Config_checkpointWarp() { return Hacktice_gConfig.checkpointWarp; }
static inline bool Config_checkpointRed() { return Hacktice_gConfig.checkpointRed; }
static inline bool Config_checkpointCoin() { return Hacktice_gConfig.checkpointCoin; }
static inline bool Config_checkpointObject() { return Hacktice_gConfig.checkpointObject; }
static inline bool Config_checkpointPlatform() { return Hacktice_gConfig.checkpointPlatform; }
