#include "cfg.h"
#include "array_size.h"
#include "string_conv.h"
#include "strings.h"

extern "C"
{
    #include "types.h"
    #include "game/game.h"
    #include "game/ingame_menu.h"
    #include "engine/math_util.h"
}

enum Pages
{
    CHECKPOINTS,
    GENERAL,
    WARP,
    PagesCount,
};

static int sPage = Pages::GENERAL;
constexpr int sMaxAllowedPage = (int) Pages::PagesCount - 1;
static u8* lPageNames[] = { uCHECKPOINTS, uGENERAL, uWARP };

static struct
{
    char speed;
    char stickStyle;
    char showButtons;
    char lAction;
    char lRAction;
    char cButtonsAction;
    char dpadDownAction;
    char warp;
    char wallkickFrame;
    char distanceFromClosestRed;
    char distanceFromClosestSecret;
    char timerShow;
    char timerStyle;
    char timerStopOnCoinStar;
    char stateSaveStyle;
    char muteMusic;
    char musicNumber;
    char deathAction;

    char checkpointWallkick;
    char checkpointDoor;
    char checkpointPole;
    char checkpointLava;
    char checkpointGroundpound;
    char checkpointBurning;
    char checkpointCannon;
    char checkpointWarp;
    char checkpointRed;
}
sConfig
{
    .timerShow = true,
    .timerStyle = (char) Config::TimerStyle::GRAB,
};

struct ConfigDescriptor
{
    char& value;
    u8* name;
    u8** valueNames;
    char maxValueCount;
};

// Config::StickStyle
static u8* inputValueNames[] = { uOFF, uTEXT, uGRAPHICS };
static u8* onOffValueNames[] = { uOFF, uON };
static u8* timerValueNames[] = { uGRAB, uXCAM };
static u8* stateSaveNames[]  = { uBUTTON, uPAUSE };
static u8* deathActionNames[] = { uOFF, uACT_SELECT, uLEVEL_RESET, uLOAD_STATE };

// Config::ButtonAction
static u8* lActionNames[]    = { uOFF, uACT_SELECT, uLEVEL_RESET, uLEVEL_RESET_WARP, uLEVITATE, uLOAD_STATE };

static u8 lMusicNumber[] = { 0x00, 0x00, 0xff };
static u8* lMusicNumbers[] = { lMusicNumber, nullptr };

static u8 sOnDeathAction = 0;

#define VALUE_NAMES(x) x, ARRAY_SIZE(x)
#define INT_NAMES(x, cnt) x, cnt

// Checkpoints
static ConfigDescriptor sCheckpointsDescriptors[] =
{
    { sConfig.checkpointBurning,     uBURNING,     VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointCannon,      uCANNON,      VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointDoor,        uDOOR,        VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointGroundpound, uGROUNDPOUND, VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointLava,        uLAVA,        VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointPole,        uPOLE,        VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointRed,         uRED,         VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointWallkick,    uWALLKICK,    VALUE_NAMES(onOffValueNames) },
    { sConfig.checkpointWarp,        uWARP,        VALUE_NAMES(onOffValueNames) },
};
constexpr int sCheckpointsMaxAllowedOption = sizeof(sCheckpointsDescriptors) / sizeof(*sCheckpointsDescriptors) - 1;

// General
static ConfigDescriptor sGeneralDescriptors[] = 
{
    { sConfig.distanceFromClosestRed,    uDISTANCE_TO_RED, VALUE_NAMES(onOffValueNames) },
    { sConfig.distanceFromClosestSecret, uDISTANCE_TO_SECRET, VALUE_NAMES(onOffValueNames) },
    
    { sConfig.showButtons,   uBUTTONS,       VALUE_NAMES(onOffValueNames) },
    { sConfig.stickStyle,    uSTICK,         VALUE_NAMES(inputValueNames) },

    { sConfig.lAction,       uLACTION,           VALUE_NAMES(lActionNames) },
    { sConfig.lRAction,      uLRACTION,          VALUE_NAMES(lActionNames) },
    { sConfig.cButtonsAction,u4_CBUTTONS_ACTION, VALUE_NAMES(lActionNames) },
    { sConfig.dpadDownAction,uDPAD_DOWN_ACTION,  VALUE_NAMES(lActionNames) },
    { sConfig.muteMusic,     uMUTE_MUSIC,    VALUE_NAMES(onOffValueNames) },
    
    { sConfig.deathAction,   uDEATH_ACTION,  VALUE_NAMES(deathActionNames) },

    { sConfig.muteMusic,     uMUTE_MUSIC,    VALUE_NAMES(onOffValueNames) },
    { sConfig.musicNumber,   uMUSIC_NUMBER,  lMusicNumbers, 64 },
    { sConfig.stateSaveStyle, uSSAVESTYLE,   VALUE_NAMES(stateSaveNames) },
    { sConfig.speed,         uSPEED,         VALUE_NAMES(onOffValueNames) },
    { sConfig.timerShow,     uTIMER,         VALUE_NAMES(onOffValueNames) },
    { sConfig.timerStyle,    uTIMERSTYLE,    VALUE_NAMES(timerValueNames) },
    { sConfig.timerStopOnCoinStar, uTIMER100,VALUE_NAMES(onOffValueNames) },
    { sConfig.wallkickFrame, uWALLKICKFRAME, VALUE_NAMES(onOffValueNames) },
};
constexpr int sGeneralMaxAllowedOption = sizeof(sGeneralDescriptors) / sizeof(*sGeneralDescriptors) - 1;

// Warp
static ConfigDescriptor sWarpDescriptors[] = {
    { sConfig.warp, uSELECT_WARP_TARGET, nullptr, 25 },
};
constexpr int sWarpMaxAllowedOption = 0;

// Common
static ConfigDescriptor* sDescriptors[] = 
{
    sCheckpointsDescriptors,
    sGeneralDescriptors,
    sWarpDescriptors,
};
static int sPickedOptions[] = 
{
    sCheckpointsMaxAllowedOption / 2,
    sGeneralMaxAllowedOption     / 2,
    sWarpMaxAllowedOption        / 2,
};
constexpr int sMaxAllowedOptions[] = 
{
    sCheckpointsMaxAllowedOption,
    sGeneralMaxAllowedOption,
    sWarpMaxAllowedOption,
};

extern "C" s16 get_str_x_pos_from_center(s16 centerPos, const u8 *str);

static void print_generic_string_centered(s16 x, s16 y, const u8 *str)
{
    auto newX = get_str_x_pos_from_center(x, str);
    print_generic_string(newX, y, str);
}

static void renderOptionAt(ConfigDescriptor& desc, int x, int y)
{
    auto value = desc.value;
    
    print_generic_string_centered(x, y,      desc.name);
    if (desc.name == uSELECT_WARP_TARGET)
    {
        u8* courseName = uOFF;
        if (0 != value)
        {
            auto courseNameTbl = (u8**) segmented_to_virtual((void*) 0x02010f68);
            int id = value - 1;
            courseName = (u8*) segmented_to_virtual(courseNameTbl[id]);
        }
        print_generic_string_centered(x, y - 20, courseName);
    }
    else
    {
        if (nullptr != desc.valueNames[1])
        {
            print_generic_string_centered(x, y - 20, desc.valueNames[(int) value]);
        }
        else
        {
            String::convert(value, desc.valueNames[0]);
            print_generic_string_centered(x, y - 20, desc.valueNames[0]);
        }
    }
}

static void render()
{
    auto pickedOption = sPickedOptions[sPage];
    auto maxAllowedOption = sMaxAllowedOptions[sPage]; 
    auto descriptors = sDescriptors[sPage];

    print_generic_string_centered(160, 210, lPageNames[(int) sPage]);

    constexpr int height = 190;
    if (pickedOption >= 2)
    {
        renderOptionAt(descriptors[pickedOption - 2], 0, height);
    }
    
    if (pickedOption >= 1)
    {
        renderOptionAt(descriptors[pickedOption - 1], 80, height);
    }

    renderOptionAt(descriptors[pickedOption], 160, height);

    if (pickedOption <= maxAllowedOption - 1)
    {
        renderOptionAt(descriptors[pickedOption + 1], 240, height);
    }

    if (pickedOption <= maxAllowedOption - 2)
    {
        renderOptionAt(descriptors[pickedOption + 2], 320, height);
    }
}

static void processInputs()
{
    auto& pickedOption = sPickedOptions[sPage];
    auto& desc = sDescriptors[sPage][pickedOption];
    auto maxAllowedOption = sMaxAllowedOptions[sPage]; 

    if (gControllers->buttonPressed & L_JPAD)
    {
        if (pickedOption != 0)
        {
            pickedOption--;
            return;
        }
    }
    if (gControllers->buttonPressed & R_JPAD)
    {
        if (pickedOption != maxAllowedOption)
        {
            pickedOption++;
            return;
        }
    }
    if (gControllers->buttonPressed & U_CBUTTONS)
    {
        if (desc.value != desc.maxValueCount - 1)
        {
            desc.value++;
            return;
        }
    }
    if (gControllers->buttonPressed & D_CBUTTONS)
    {
        if (desc.value != 0)
        {
            desc.value--;
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

    if (desc.maxValueCount > 10)
    {
        auto controllerDistance = gControllers->rawStickX * gControllers->rawStickX + gControllers->rawStickY * gControllers->rawStickY;
        if (controllerDistance > 1000)
        {
            u16 angle = atan2s(gControllers->rawStickY, gControllers->rawStickX);
            auto normalizedAngle = (float) angle / (float) 0x10000;
            desc.value = normalizedAngle * desc.maxValueCount;
        }
    }
}

void Config::onPause()
{
    render();
    processInputs();
}

Config::StickStyle Config::showStick()
{
    return (Config::StickStyle) sConfig.stickStyle;
}

bool Config::showButtons()
{
    return sConfig.showButtons;
}

LevelConv::PlainLevels Config::warpId()
{
    return (LevelConv::PlainLevels) sConfig.warp;
}

LevelConv::PlainLevels Config::warpIdAndReset()
{
    auto w = warpId();
    sConfig.warp = 0;
    sPage = Pages::GENERAL;
    return w;
}   

#define BUTTONS_PRESSED(mask) (((gControllers->buttonDown) & (mask)) == (mask))

Config::ButtonAction Config::action()
{
    if (sOnDeathAction)
    {
        return (Config::ButtonAction) sOnDeathAction;
    }

    if (sConfig.lRAction && BUTTONS_PRESSED(L_TRIG | R_TRIG))
    {
        return (Config::ButtonAction) sConfig.lRAction;
    }
    else if (sConfig.lAction && BUTTONS_PRESSED(L_TRIG))
    {
        return (Config::ButtonAction) sConfig.lAction;
    }
    else if (sConfig.cButtonsAction && BUTTONS_PRESSED(U_CBUTTONS | D_CBUTTONS | R_CBUTTONS | L_CBUTTONS))
    {
        return (Config::ButtonAction) sConfig.cButtonsAction;
    }
    else if (sConfig.dpadDownAction && BUTTONS_PRESSED(D_JPAD))
    {
        return (Config::ButtonAction) sConfig.dpadDownAction;
    }

    return ButtonAction::OFF;
}

bool Config::showWallkickFrame()
{
    return sConfig.wallkickFrame;
}

bool Config::showDistanceFromClosestRed()
{
    return sConfig.distanceFromClosestRed;
}

bool Config::showDistanceFromClosestSecret()
{
    return sConfig.distanceFromClosestSecret;
}

bool Config::showSpeed()
{
    return sConfig.speed;
}

bool Config::timerShow()
{
    return sConfig.timerShow;
}

Config::TimerStyle Config::timerStyle()
{
    return (Config::TimerStyle) sConfig.timerStyle;
}

bool Config::timerStopOnCoinStar()
{
    return sConfig.timerStopOnCoinStar;
}

Config::StateSaveStyle Config::saveStateStyle()
{
    return (Config::StateSaveStyle) sConfig.stateSaveStyle;
}

bool Config::muteMusic()
{
    return sConfig.muteMusic;
}

char Config::musicNumber()
{
    return sConfig.musicNumber;
}

Config::DeathAction Config::deathAction()
{
    return (Config::DeathAction) sConfig.deathAction;
}

void Config::setOnDeathAction(ButtonAction act)
{
    sOnDeathAction = (u8) act;
}

bool Config::checkpointWallkick()
{
    return sConfig.checkpointWallkick;
}

bool Config::checkpointDoor()
{
    return sConfig.checkpointDoor;
}

bool Config::checkpointPole()
{
    return sConfig.checkpointPole;
}

bool Config::checkpointLava()
{
    return sConfig.checkpointLava;
}

bool Config::checkpointGroundpound()
{
    return sConfig.checkpointGroundpound;
}

bool Config::checkpointBurning()
{
    return sConfig.checkpointBurning;
}

bool Config::checkpointCannon()
{
    return sConfig.checkpointCannon;
}

bool Config::checkpointWarp()
{
    return sConfig.checkpointWarp;
}

bool Config::checkpointRed()
{
    return sConfig.checkpointRed;
}