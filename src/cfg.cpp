#include "cfg.h"
extern "C"
{
    #include "types.h"
    #include "game/game.h"
    #include "game/ingame_menu.h"
    #include "engine/math_util.h"
}
#include "array_size.h"
#include "string_conv.h"
#include "strings.h"

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

static char sSpeed = 0;
static char sStickStyle = 0;
static char sShowButtons = 0;
static char sLAction = 0;
static char sLRAction = 0;
static char sXAction = 0;
static char sXRAction = 0;
static char sYAction = 0;
static char sYRAction = 0;
static char sCButtonsAction = 0;
static char sDpadDownAction = 0;
static char sWarp = 0;
static char sWallkickFrame = 0;
static char sDistanceFromClosestRed = 0;
static char sDistanceFromClosestSecret = 0;
static char sTimerShow = true;
static char sTimerStyle = (char) Config::TimerStyle::GRAB;
static char sTimerStopOnCoinStar = false;
static char sStateSaveStyle = 0;

static char sCheckpointWallkick = false;
static char sCheckpointDoor = false;
static char sCheckpointPole = false;
static char sCheckpointLava = false;
static char sCheckpointGroundpound = false;
static char sCheckpointBurning = false;
static char sCheckpointCannon = false;

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

// Config::ButtonAction
static u8* lActionNames[]    = { uOFF, uACT_SELECT, uLEVEL_RESET, uLEVEL_RESET_WARP, uLEVITATE, uLOAD_STATE };
#define VALUE_NAMES(x) x, ARRAY_SIZE(x)

// Checkpoints
static ConfigDescriptor sCheckpointsDescriptors[] =
{
    { sCheckpointBurning,     uBURNING,     VALUE_NAMES(onOffValueNames) },
    { sCheckpointCannon,      uCANNON,      VALUE_NAMES(onOffValueNames) },
    { sCheckpointDoor,        uDOOR,        VALUE_NAMES(onOffValueNames) },
    { sCheckpointGroundpound, uGROUNDPOUND, VALUE_NAMES(onOffValueNames) },
    { sCheckpointLava,        uLAVA,        VALUE_NAMES(onOffValueNames) },
    { sCheckpointPole,        uPOLE,        VALUE_NAMES(onOffValueNames) },
    { sCheckpointWallkick,    uWALLKICK,    VALUE_NAMES(onOffValueNames) },
};
constexpr int sCheckpointsMaxAllowedOption = sizeof(sCheckpointsDescriptors) / sizeof(*sCheckpointsDescriptors) - 1;

// General
static ConfigDescriptor sGeneralDescriptors[] = 
{
    { sDistanceFromClosestRed,    uDISTANCE_TO_RED, VALUE_NAMES(onOffValueNames) },
    { sDistanceFromClosestSecret, uDISTANCE_TO_SECRET, VALUE_NAMES(onOffValueNames) },
    
    { sShowButtons,   uBUTTONS,       VALUE_NAMES(onOffValueNames) },
    { sStickStyle,    uSTICK,         VALUE_NAMES(inputValueNames) },

    { sLAction,       uLACTION,           VALUE_NAMES(lActionNames) },
    { sLRAction,      uLRACTION,          VALUE_NAMES(lActionNames) },
    { sCButtonsAction,u4_CBUTTONS_ACTION, VALUE_NAMES(lActionNames) },
    { sDpadDownAction,uDPAD_DOWN_ACTION,  VALUE_NAMES(lActionNames) },
    /*
    { sXAction,     uXACTION,  VALUE_NAMES(lActionNames) },
    { sXRAction,    uXRACTION, VALUE_NAMES(lActionNames) },
    { sYAction,     uYACTION,  VALUE_NAMES(lActionNames) },
    { sYRAction,    uYRACTION, VALUE_NAMES(lActionNames) },
    */

    { sStateSaveStyle, uSSAVESTYLE,   VALUE_NAMES(stateSaveNames) },
    { sSpeed,         uSPEED,         VALUE_NAMES(onOffValueNames) },
    { sTimerShow,     uTIMER,         VALUE_NAMES(onOffValueNames) },
    { sTimerStyle,    uTIMERSTYLE,    VALUE_NAMES(timerValueNames) },
    { sTimerStopOnCoinStar, uTIMER100,VALUE_NAMES(onOffValueNames) },
    { sWallkickFrame, uWALLKICKFRAME, VALUE_NAMES(onOffValueNames) },
};
constexpr int sGeneralMaxAllowedOption = sizeof(sGeneralDescriptors) / sizeof(*sGeneralDescriptors) - 1;

// Warp
static ConfigDescriptor sWarpDescriptors[] = {
    { sWarp, uSELECT_WARP_TARGET, nullptr, 25 },
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
        print_generic_string_centered(x, y - 20, desc.valueNames[(int) value]);
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
        renderOptionAt(descriptors[pickedOption - 2], 20, height);
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
        renderOptionAt(descriptors[pickedOption + 2], 300, height);
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
    return (Config::StickStyle) sStickStyle;
}

bool Config::showButtons()
{
    return sShowButtons;
}

LevelConv::PlainLevels Config::warpId()
{
    return (LevelConv::PlainLevels) sWarp;
}

LevelConv::PlainLevels Config::warpIdAndReset()
{
    auto w = warpId();
    sWarp = 0;
    return w;
}   

#define BUTTONS_PRESSED(mask) (((gControllers->buttonDown) & (mask)) == (mask))

Config::ButtonAction Config::action()
{
    if (sLRAction && BUTTONS_PRESSED(L_TRIG | R_TRIG))
    {
        return (Config::ButtonAction) sLRAction;
    }
    else if (sLAction && BUTTONS_PRESSED(L_TRIG))
    {
        return (Config::ButtonAction) sLAction;
    }
    else if (sCButtonsAction && BUTTONS_PRESSED(U_CBUTTONS | D_CBUTTONS | R_CBUTTONS | L_CBUTTONS))
    {
        return (Config::ButtonAction) sCButtonsAction;
    }
    else if (sDpadDownAction && BUTTONS_PRESSED(D_JPAD))
    {
        return (Config::ButtonAction) sDpadDownAction;
    }
    else if (sXAction && (gControllers->buttonDown & 0x40))
    {
        return (Config::ButtonAction) sXAction;
    }
    else if (sYAction  && (gControllers->buttonDown & 0x80))
    {
        return (Config::ButtonAction) sYAction;
    }

    return ButtonAction::OFF;
}

bool Config::showWallkickFrame()
{
    return sWallkickFrame;
}

bool Config::showDistanceFromClosestRed()
{
    return sDistanceFromClosestRed;
}

bool Config::showDistanceFromClosestSecret()
{
    return sDistanceFromClosestSecret;
}

bool Config::showSpeed()
{
    return sSpeed;
}

bool Config::timerShow()
{
    return sTimerShow;
}

Config::TimerStyle Config::timerStyle()
{
    return (Config::TimerStyle) sTimerStyle;
}

bool Config::timerStopOnCoinStar()
{
    return sTimerStopOnCoinStar;
}

Config::StateSaveStyle Config::saveStateStyle()
{
    return (Config::StateSaveStyle) sStateSaveStyle;
}

bool Config::checkpointWallkick()
{
    return sCheckpointWallkick;
}

bool Config::checkpointDoor()
{
    return sCheckpointDoor;
}

bool Config::checkpointPole()
{
    return sCheckpointPole;
}

bool Config::checkpointLava()
{
    return sCheckpointLava;
}

bool Config::checkpointGroundpound()
{
    return sCheckpointGroundpound;
}

bool Config::checkpointBurning()
{
    return sCheckpointBurning;
}

bool Config::checkpointCannon()
{
    return sCheckpointCannon;
}
