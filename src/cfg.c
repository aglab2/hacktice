#include "cfg.h"
#include "array_size.h"
#include "shared.h"
#include "string_conv.h"
#include "strings.h"

#include "types.h"
#include "game/game.h"
#include "game/ingame_menu.h"
#include "engine/math_util.h"

static char sWarp;
static char sMusicNumber;

Config sConfig = {
    .magic = HACKTICE_CONFIG_CANARY,
    .selfSize = sizeof(Config),
    .timerShow = true,
    .warpWheel = true,
};

typedef enum Pages
{
    Pages_CHECKPOINTS,
    Pages_GENERAL,
    Pages_WARP,
    Pages_PagesCount,
} Pages;

static int sPage = Pages_GENERAL;
// poor man constexpr
#define sMaxAllowedPage (Pages_PagesCount - 1)
static const u8* lPageNames[] = { uCHECKPOINTS, uGENERAL, uWARP };

typedef struct ConfigDescriptor
{
    char* value;
    const u8* name;
    const u8* const* valueNames;
    char maxValueCount;
} ConfigDescriptor;

// Config_StickStyle
static const u8* const inputValueNames[] = { uOFF, uTEXT, uGRAPHICS };
static const u8* const onOffValueNames[] = { uOFF, uON };
static const u8* const timerValueNames[] = { uGRAB, uXCAM };
static const u8* const stateSaveNames[]  = { uBUTTON, uPAUSE };
static const u8* const deathActionNames[] = { uOFF, uACT_SELECT, uLEVEL_RESET, uLOAD_STATE };

// Config_ButtonAction
static const u8* const actionNames[]    = { uOFF, uACT_SELECT, uLEVEL_RESET, uLEVEL_RESET_WARP, uLEVITATE, uLOAD_STATE };

static u8 lMusicNumber[] = { 0x00, 0x00, 0xff };
static const u8* const lMusicNumbers[] = { lMusicNumber, NULL };

static u8 sOnDeathAction = 0;

#define VALUE_NAMES(x) x, ARRAY_SIZE(x)
#define INT_NAMES(x, cnt) x, cnt

// Checkpoints
static const ConfigDescriptor sCheckpointsDescriptors[] =
{
    { &sConfig.checkpointBurning,     uBURNING,     VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointCannon,      uCANNON,      VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointCoin,        uCOIN,        VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointDoor,        uDOOR,        VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointGroundpound, uGROUNDPOUND, VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointLava,        uLAVA,        VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointObject,      uOBJECT,      VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointPlatform,    uPLATFORM,    VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointPole,        uPOLE,        VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointRed,         uRED,         VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointWallkick,    uWALLKICK,    VALUE_NAMES(onOffValueNames) },
    { &sConfig.checkpointWarp,        uWARP,        VALUE_NAMES(onOffValueNames) },
};
#define sCheckpointsMaxAllowedOption (sizeof(sCheckpointsDescriptors) / sizeof(*sCheckpointsDescriptors) - 1)

// General
static const ConfigDescriptor sGeneralDescriptors[] =
{
    { &sConfig.distanceFromClosestRed,    uDISTANCE_TO_RED, VALUE_NAMES(onOffValueNames) },
    { &sConfig.distanceFromClosestSecret, uDISTANCE_TO_SECRET, VALUE_NAMES(onOffValueNames) },
    
    { &sConfig.showButtons,   uBUTTONS,       VALUE_NAMES(onOffValueNames) },
    { &sConfig.stickStyle,    uSTICK,         VALUE_NAMES(inputValueNames) },

    { &sConfig.lAction,       uLACTION,           VALUE_NAMES(actionNames) },
    { &sConfig.lRAction,      uLRACTION,          VALUE_NAMES(actionNames) },
    { &sConfig.cButtonsAction,u4_CBUTTONS_ACTION, VALUE_NAMES(actionNames) },
    { &sConfig.dpadDownAction,uDPAD_DOWN_ACTION,  VALUE_NAMES(actionNames) },
    { &sConfig.dpadUpAction,  uDPAD_UP_ACTION  ,  VALUE_NAMES(actionNames) },

    { &sConfig.muteMusic,     uMUTE_MUSIC,    VALUE_NAMES(onOffValueNames) },
    
    { &sConfig.deathAction,   uDEATH_ACTION,  VALUE_NAMES(deathActionNames) },

    { &sMusicNumber,   uMUSIC_NUMBER,  lMusicNumbers, 64 },
    { &sConfig.stateSaveStyle, uSSAVESTYLE,   VALUE_NAMES(stateSaveNames) },
    { &sConfig.speed,         uSPEED,         VALUE_NAMES(onOffValueNames) },
    { &sConfig.timerShow,     uTIMER,         VALUE_NAMES(onOffValueNames) },
    { &sConfig.timerStyle,    uTIMERSTYLE,    VALUE_NAMES(timerValueNames) },
    { &sConfig.timerStopOnCoinStar, uTIMER100,VALUE_NAMES(onOffValueNames) },
    { &sConfig.wallkickFrame, uWALLKICKFRAME, VALUE_NAMES(onOffValueNames) },

    { &sConfig.warpWheel,     uWARP_WHEEL, VALUE_NAMES(onOffValueNames) },
};
#define sGeneralMaxAllowedOption (sizeof(sGeneralDescriptors) / sizeof(*sGeneralDescriptors) - 1)

// Warp
static const ConfigDescriptor sWarpDescriptors[] = {
    { &sWarp, uSELECT_WARP_TARGET, NULL, 25 },
};
#define sWarpMaxAllowedOption 0

// Common
static const ConfigDescriptor* const sDescriptors[] = 
{
    sCheckpointsDescriptors,
    sGeneralDescriptors,
    sWarpDescriptors,
};
static int sPickedOptions[3] = {
    sCheckpointsMaxAllowedOption / 2,
    sGeneralMaxAllowedOption     / 2,
    sWarpMaxAllowedOption        / 2,
};
static const int sMaxAllowedOptions[3] = {
    sCheckpointsMaxAllowedOption,
    sGeneralMaxAllowedOption,
    sWarpMaxAllowedOption,
};

s16 get_str_x_pos_from_center(s16 centerPos, const u8 *str);

static void print_generic_string_centered(s16 x, s16 y, const u8 *str)
{
    s16 newX = get_str_x_pos_from_center(x, str);
    print_generic_string(newX, y, str);
}

static void renderOptionAt(const ConfigDescriptor* const desc, int x, int y)
{
    int value = *desc->value;
    
    print_generic_string_centered(x, y,      desc->name);
    if (desc->name == uSELECT_WARP_TARGET)
    {
        const u8* courseName = uOFF;
        if (0 != value)
        {
            u8** courseNameTbl = (u8**) segmented_to_virtual((void*) 0x02010f68);
            int id = value - 1;
            courseName = (u8*) segmented_to_virtual(courseNameTbl[id]);
        }
        print_generic_string_centered(x, y - 20, courseName);
    }
    else
    {
        if (NULL != desc->valueNames[1])
        {
            print_generic_string_centered(x, y - 20, desc->valueNames[(int) value]);
        }
        else
        {
            // TODO: const HACK
            String_convert(value, (u8*) desc->valueNames[0]);
            print_generic_string_centered(x, y - 20, desc->valueNames[0]);
        }
    }
}

static void render()
{
    int pickedOption = sPickedOptions[sPage];
    int maxAllowedOption = sMaxAllowedOptions[sPage]; 
    const ConfigDescriptor* descriptors = sDescriptors[sPage];

    if (0 != sPage)
        print_generic_string(20, 210, uLEFT_Z);

    if (sPage != sMaxAllowedPage)
        print_generic_string(280, 210, uRIGHT_R);

    print_generic_string(80, 125, uRIGHT_DPAD);
    print_generic_string(9, 125, uLEFT_DPAD);
    print_generic_string_centered(72, 145, uC_UP);
    print_generic_string(70, 135, uUP);
    print_generic_string(70, 115, uDOWN);
    print_generic_string_centered(72, 105, uC_DOWN);

    print_generic_string_centered(160, 210, lPageNames[(int) sPage]);

    const int height = 190;
    if (pickedOption >= 2)
    {
        renderOptionAt(&descriptors[pickedOption - 2], 0, height);
    }
    
    if (pickedOption >= 1)
    {
        renderOptionAt(&descriptors[pickedOption - 1], 80, height);
    }

    renderOptionAt(&descriptors[pickedOption], 160, height);

    if (pickedOption <= maxAllowedOption - 1)
    {
        renderOptionAt(&descriptors[pickedOption + 1], 240, height);
    }

    if (pickedOption <= maxAllowedOption - 2)
    {
        renderOptionAt(&descriptors[pickedOption + 2], 320, height);
    }
}

static void processInputs()
{
    int* pickedOption = &sPickedOptions[sPage];
    const ConfigDescriptor* desc = &sDescriptors[sPage][*pickedOption];
    int maxAllowedOption = sMaxAllowedOptions[sPage]; 

    if (gControllers->buttonPressed & L_JPAD)
    {
        if (*pickedOption != 0)
        {
            (*pickedOption)--;
            return;
        }
    }
    if (gControllers->buttonPressed & R_JPAD)
    {
        if ((*pickedOption) != maxAllowedOption)
        {
            (*pickedOption)++;
            return;
        }
    }
    if (gControllers->buttonPressed & U_CBUTTONS)
    {
        if ((*desc->value) != desc->maxValueCount - 1)
        {
            (*desc->value)++;
            return;
        }
    }
    if (gControllers->buttonPressed & D_CBUTTONS)
    {
        if ((*desc->value) != 0)
        {
            (*desc->value)--;
            return;
        }
    }
    if (gControllers->buttonPressed & Z_TRIG)
    {
        if (sPage != 0)
        {
            sPage--;
            return;
        }
    }
    if (gControllers->buttonPressed & R_TRIG)
    {
        if (sPage != sMaxAllowedPage)
        {
            sPage++;
            return;
        }
    }

    if (desc->maxValueCount > 10 && sConfig.warpWheel)
    {
        int controllerDistance = (int)gControllers->rawStickX * (int)gControllers->rawStickX + (int)gControllers->rawStickY * (int)gControllers->rawStickY;
        if (controllerDistance > 1000)
        {
            u16 angle = atan2s(gControllers->rawStickY, gControllers->rawStickX);
            float normalizedAngle = (float) angle / (float) 0x10000;
            *desc->value = (int) (normalizedAngle * desc->maxValueCount);
        }
    }
}

void Config_onPause()
{
    render();
    processInputs();
}

Config_StickStyle Config_showStick()
{
    return (Config_StickStyle) sConfig.stickStyle;
}

bool Config_showButtons()
{
    return sConfig.showButtons;
}

static inline LevelConv_PlainLevels Config_warpId()
{
    return (LevelConv_PlainLevels) sWarp;
}

LevelConv_PlainLevels Config_warpIdAndReset()
{
    if (sPage != Pages_WARP)
    {
        return LevelConv_PlainLevels_OFF;
    }

    int w = Config_warpId();
    if (0 != w)
    {
        sPage = Pages_GENERAL;
    }

    return w;
}   

#define BUTTONS_PRESSED(mask) (((gControllers->buttonDown) & (mask)) == (mask))

Config_ButtonAction Config_action()
{
    if (sOnDeathAction)
    {
        return (Config_ButtonAction) sOnDeathAction;
    }

    if (sConfig.lRAction && BUTTONS_PRESSED(L_TRIG | R_TRIG))
    {
        return (Config_ButtonAction) sConfig.lRAction;
    }
    else if (sConfig.lAction && BUTTONS_PRESSED(L_TRIG))
    {
        return (Config_ButtonAction) sConfig.lAction;
    }
    else if (sConfig.cButtonsAction && BUTTONS_PRESSED(U_CBUTTONS | D_CBUTTONS | R_CBUTTONS | L_CBUTTONS))
    {
        return (Config_ButtonAction) sConfig.cButtonsAction;
    }
    else if (sConfig.dpadDownAction && BUTTONS_PRESSED(D_JPAD))
    {
        return (Config_ButtonAction) sConfig.dpadDownAction;
    }
    else if (sConfig.dpadUpAction && BUTTONS_PRESSED(U_JPAD))
    {
        return (Config_ButtonAction) sConfig.dpadUpAction;
    }

    return Config_ButtonAction_OFF;
}

bool Config_showWallkickFrame()
{
    return sConfig.wallkickFrame;
}

bool Config_showDistanceFromClosestRed()
{
    return sConfig.distanceFromClosestRed;
}

bool Config_showDistanceFromClosestSecret()
{
    return sConfig.distanceFromClosestSecret;
}

bool Config_showSpeed()
{
    return sConfig.speed;
}

bool Config_timerShow()
{
    return sConfig.timerShow;
}

Config_TimerStyle Config_timerStyle()
{
    return (Config_TimerStyle) sConfig.timerStyle;
}

bool Config_timerStopOnCoinStar()
{
    return sConfig.timerStopOnCoinStar;
}

Config_StateSaveStyle Config_saveStateStyle()
{
    return (Config_StateSaveStyle) sConfig.stateSaveStyle;
}

bool Config_muteMusic()
{
    return sConfig.muteMusic;
}

char Config_musicNumber()
{
    return sMusicNumber;
}

Config_DeathAction Config_deathAction()
{
    return (Config_DeathAction) sConfig.deathAction;
}

void Config_setOnDeathAction(Config_ButtonAction act)
{
    sOnDeathAction = (u8) act;
}

bool Config_checkpointWallkick()
{
    return sConfig.checkpointWallkick;
}

bool Config_checkpointDoor()
{
    return sConfig.checkpointDoor;
}

bool Config_checkpointPole()
{
    return sConfig.checkpointPole;
}

bool Config_checkpointLava()
{
    return sConfig.checkpointLava;
}

bool Config_checkpointGroundpound()
{
    return sConfig.checkpointGroundpound;
}

bool Config_checkpointBurning()
{
    return sConfig.checkpointBurning;
}

bool Config_checkpointCannon()
{
    return sConfig.checkpointCannon;
}

bool Config_checkpointWarp()
{
    return sConfig.checkpointWarp;
}

bool Config_checkpointRed()
{
    return sConfig.checkpointRed;
}

bool Config_checkpointCoin()
{
    return sConfig.checkpointCoin;
}

bool Config_checkpointObject()
{
    return sConfig.checkpointObject;
}

bool Config_checkpointPlatform()
{
    return sConfig.checkpointPlatform;
}
