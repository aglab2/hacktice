#include "cfg.h"
#include "array_size.h"
#include "binary.h"
#include "shared.h"
#include "string_conv.h"
#include "strings.h"

#include "types.h"
#include "game/ingame_menu.h"
#include "engine/math_util.h"

#include "stdio.h"

char Config_gWarp;
char Config_gMusicNumber;
char Config_gOnDeathAction;

Config Hacktice_gConfig = {
    .magic = HACKTICE_CONFIG_CANARY,
    .selfSize = sizeof(Config),
    .timerShow = true,
    .warpWheel = true,
    .customText = "PRACTICE",

    .lAction = 5,
};

typedef struct ConfigDescriptor
{
    char* value;
    const HC* name;
    const HC* const* valueNames;
    char maxValueCount;
} ConfigDescriptor;

// Config_StickStyle
static const HC* const inputValueNames[] = { uOFF, uTEXT, uGRAPHICS };
static const HC* const onOffValueNames[] = { uOFF, uON };
static const HC* const timerValueNames[] = { uGRAB, uXCAM };
static const HC* const stateSaveNames[]  = { uBUTTON, uPAUSE };
static const HC* const deathActionNames[] = { uOFF, uACT_SELECT, uLEVEL_RESET, uLOAD_STATE };

// Config_ButtonAction
static const HC* const actionNames[]    = { uOFF, uACT_SELECT, uLEVEL_RESET, uLEVEL_RESET_WARP, uLEVITATE, uLOAD_STATE };

static HC lMusicNumber[] = { "00" };
static const HC* const lMusicNumbers[] = { lMusicNumber, NULL };

#define VALUE_NAMES(x) x, ARRAY_SIZE(x)
#define INT_NAMES(x, cnt) x, cnt

// Checkpoints
static const ConfigDescriptor sCheckpointsDescriptors[] =
{
    { &Hacktice_gConfig.checkpointBurning,     uBURNING,     VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointCannon,      uCANNON,      VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointCoin,        uCOIN,        VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointDoor,        uDOOR,        VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointGroundpound, uGROUNDPOUND, VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointLava,        uLAVA,        VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointObject,      uOBJECT,      VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointPlatform,    uPLATFORM,    VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointPole,        uPOLE,        VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointRed,         uRED,         VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointWallkick,    uWALLKICK,    VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.checkpointWarp,        uWARP,        VALUE_NAMES(onOffValueNames) },
};
#define sCheckpointsMaxAllowedOption (sizeof(sCheckpointsDescriptors) / sizeof(*sCheckpointsDescriptors) - 1)

// Visuals
static const ConfigDescriptor sVisualsDescriptors[] =
{
    { &Hacktice_gConfig.showButtons,   uBUTTONS,       VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.stickStyle,    uSTICK,         VALUE_NAMES(inputValueNames) },

    { &Hacktice_gConfig.speed,         uSPEED,         VALUE_NAMES(onOffValueNames) },

    { &Hacktice_gConfig.timerShow,     uTIMER,         VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.timerStyle,    uTIMERSTYLE,    VALUE_NAMES(timerValueNames) },
    { &Hacktice_gConfig.timerStopOnCoinStar, uTIMER100,VALUE_NAMES(onOffValueNames) },

    { &Hacktice_gConfig.wallkickFrame, uWALLKICKFRAME, VALUE_NAMES(onOffValueNames) },

    { &Hacktice_gConfig.distanceFromClosestRed,    uDISTANCE_TO_RED, VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.distanceFromClosestSecret, uDISTANCE_TO_SECRET, VALUE_NAMES(onOffValueNames) }, 

    { &Hacktice_gConfig.showCustomText, uCUSTOM_TEXT, VALUE_NAMES(onOffValueNames) },
#ifdef BINARY
    { &Hacktice_gConfig.showCollision, uSHOW_COLLISION, VALUE_NAMES(onOffValueNames) },
#endif
};
#define sVisualsMaxAllowedOption (sizeof(sVisualsDescriptors) / sizeof(*sVisualsDescriptors) - 1)

// General
static const ConfigDescriptor sGeneralDescriptors[] =
{
    { &Hacktice_gConfig.muteMusic,     uMUTE_MUSIC,    VALUE_NAMES(onOffValueNames) },
    
    { &Hacktice_gConfig.deathAction,   uDEATH_ACTION,  VALUE_NAMES(deathActionNames) },

    { &Hacktice_gConfig.stateSaveStyle, uSSAVESTYLE,   VALUE_NAMES(stateSaveNames) },
    { &Config_gMusicNumber,    uMUSIC_NUMBER,  lMusicNumbers, 64 },

    { &Hacktice_gConfig.warpWheel,     uWARP_WHEEL, VALUE_NAMES(onOffValueNames) },
    { &Hacktice_gConfig.softReset,     uSOFT_RESET, VALUE_NAMES(onOffValueNames) },
};
#define sGeneralMaxAllowedOption (sizeof(sGeneralDescriptors) / sizeof(*sGeneralDescriptors) - 1)

// Shortcuts
static const ConfigDescriptor sShortcutsDescriptors[] =
{
    { &Hacktice_gConfig.lAction,       uLACTION,           VALUE_NAMES(actionNames) },
    { &Hacktice_gConfig.lRAction,      uLRACTION,          VALUE_NAMES(actionNames) },
    { &Hacktice_gConfig.cButtonsAction,u4_CBUTTONS_ACTION, VALUE_NAMES(actionNames) },
    { &Hacktice_gConfig.dpadDownAction,uDPAD_DOWN_ACTION,  VALUE_NAMES(actionNames) },
    { &Hacktice_gConfig.dpadUpAction,  uDPAD_UP_ACTION  ,  VALUE_NAMES(actionNames) },
};
#define sShortcutsMaxAllowedOption (sizeof(sShortcutsDescriptors) / sizeof(*sShortcutsDescriptors) - 1)

static const u8 kWarpTargets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, /*25,*/ 26, 27, 28 };

// Warp
static const ConfigDescriptor sWarpDescriptors[] = {
    { &Config_gWarp, uSELECT_WARP_TARGET, NULL, sizeof(kWarpTargets) },
};
#define sWarpMaxAllowedOption 0

// Common
typedef enum Pages
{
    Pages_CHECKPOINTS,
    Pages_VISUALS,
    Pages_GENERAL,
    Pages_SHORTCUTS,
    Pages_WARP,
    Pages_PagesCount,
} Pages;

static unsigned char sPage = Pages_GENERAL;
// poor man constexpr
#define sMaxAllowedPage (Pages_PagesCount - 1)

typedef struct PageDescriptor
{
    const HC* name;
    const ConfigDescriptor* configs;
    char maxAllowedOption;
} PageDescriptor;

#define PAGE_CONFIG(desc) desc, sizeof(desc)/sizeof(*desc) - 1
static const PageDescriptor sPageDescriptors[] = 
{
    { uCHECKPOINTS, PAGE_CONFIG(sCheckpointsDescriptors) },
    { uVISUALS    , PAGE_CONFIG(sVisualsDescriptors) },
    { uGENERAL    , PAGE_CONFIG(sGeneralDescriptors) },
    { uSHORTCUTS  , PAGE_CONFIG(sShortcutsDescriptors) },
    { uWARP       , PAGE_CONFIG(sWarpDescriptors) },
};

static unsigned char sPickedOptions[] = {
    sCheckpointsMaxAllowedOption / 2,
    sVisualsMaxAllowedOption     / 2,
    sGeneralMaxAllowedOption     / 2,
    sShortcutsMaxAllowedOption   / 2,
    sWarpMaxAllowedOption        / 2,
};

static void print_generic_string_centered(s16 x, s16 y, const HC *str)
{
#ifdef BINARY
    s16 newX = get_str_x_pos_from_center(x, (HC*) str, 0);
    print_generic_string(newX, y, str);
#else
    print_generic_string_aligned(x, y, str, TEXT_ALIGN_CENTER);
#endif
}

static HC* launder(char* line)
{
    char* p;
    for (p = line; *p != '\0'; ++p)
    {
        char sym = *p;
        switch (sym)
        {
            case '0': sym = 0x00; break;
            case '1': sym = 0x01; break;
            case '2': sym = 0x02; break;
            case '3': sym = 0x03; break;
            case '4': sym = 0x04; break;
            case '5': sym = 0x05; break;
            case '6': sym = 0x06; break;
            case '7': sym = 0x07; break;
            case '8': sym = 0x08; break;
            case '9': sym = 0x09; break;
            case 'A': sym = 0x0A; break;
            case 'B': sym = 0x0B; break;
            case 'C': sym = 0x0C; break;
            case 'D': sym = 0x0D; break;
            case 'E': sym = 0x0E; break;
            case 'F': sym = 0x0F; break;
            case 'G': sym = 0x10; break;
            case 'H': sym = 0x11; break;
            case 'I': sym = 0x12; break;
            case 'J': sym = 0x13; break;
            case 'K': sym = 0x14; break;
            case 'L': sym = 0x15; break;
            case 'M': sym = 0x16; break;
            case 'N': sym = 0x17; break;
            case 'O': sym = 0x18; break;
            case 'P': sym = 0x19; break;
            case 'Q': sym = 0x1A; break;
            case 'R': sym = 0x1B; break;
            case 'S': sym = 0x1C; break;
            case 'T': sym = 0x1D; break;
            case 'U': sym = 0x1E; break;
            case 'V': sym = 0x1F; break;
            case 'W': sym = 0x20; break;
            case 'X': sym = 0x21; break;
            case 'Y': sym = 0x22; break;
            case 'Z': sym = 0x23; break;
            case 'a': sym = 0x24; break;
            case 'b': sym = 0x25; break;
            case 'c': sym = 0x26; break;
            case 'd': sym = 0x27; break;
            case 'e': sym = 0x28; break;
            case 'f': sym = 0x29; break;
            case 'g': sym = 0x2A; break;
            case 'h': sym = 0x2B; break;
            case 'i': sym = 0x2C; break;
            case 'j': sym = 0x2D; break;
            case 'k': sym = 0x2E; break;
            case 'l': sym = 0x2F; break;
            case 'm': sym = 0x30; break;
            case 'n': sym = 0x31; break;
            case 'o': sym = 0x32; break;
            case 'p': sym = 0x33; break;
            case 'q': sym = 0x34; break;
            case 'r': sym = 0x35; break;
            case 's': sym = 0x36; break;
            case 't': sym = 0x37; break;
            case 'u': sym = 0x38; break;
            case 'v': sym = 0x39; break;
            case 'w': sym = 0x3A; break;
            case 'x': sym = 0x3B; break;
            case 'y': sym = 0x3C; break;
            case 'z': sym = 0x3D; break;
            case '\'': sym = 0x3E; break;
            case '.': sym = 0x3F; break;
            case ' ': sym = 0x9E; break;
        }

        *p = sym;
    }
    *p = 0xff;

    return (HC*) line;
}


static void renderOptionAt(const ConfigDescriptor* const desc, int x, int y)
{
    int value = *desc->value;
    
    print_generic_string_centered(x, y,      desc->name);
    if (desc->name == uSELECT_WARP_TARGET)
    {
        char line[32];
        const HC* courseName = uOFF;
        if (0 != value)
        {
            HC** courseNameTbl = (HC**) segmented_to_virtual(sCourseNames);
            int id = kWarpTargets[value] - 1;
            if (LevelConv_PlainLevels_S3 - 1 == id)
            {
                sprintf(line, "ENDING");
                courseName = launder(line);
            }
            else if (LevelConv_PlainLevels_F1 - 1 <= id)
            {
                sprintf(line, "BOWSER FIGHT %d", id - (LevelConv_PlainLevels_F1 - 1) + 1);
                courseName = launder(line);
            }
            else
            {
                courseName = (HC*) segmented_to_virtual(courseNameTbl[id]);
            }
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
            String_convert(value, (HC*) desc->valueNames[0]);
            print_generic_string_centered(x, y - 20, desc->valueNames[0]);
        }
    }
}

static void render()
{
    int pickedOption = sPickedOptions[sPage];
    const PageDescriptor* pageDescriptor = &sPageDescriptors[sPage];
    int maxAllowedOption = pageDescriptor->maxAllowedOption;
    const ConfigDescriptor* descriptors = pageDescriptor->configs;

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

    print_generic_string_centered(160, 210, pageDescriptor->name);

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
    unsigned char* pickedOption = &sPickedOptions[sPage];
    const PageDescriptor* pageDescriptor = &sPageDescriptors[sPage];
    const ConfigDescriptor* desc = &pageDescriptor->configs[*pickedOption];
    int maxAllowedOption = pageDescriptor->maxAllowedOption;

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

    if (desc->maxValueCount > 10 && Hacktice_gConfig.warpWheel)
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

static inline LevelConv_PlainLevels Config_warpId()
{
    return (LevelConv_PlainLevels) Config_gWarp;
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
        sPage = Pages_WARP - 1;
    }

    return kWarpTargets[w];
}   

#define BUTTONS_PRESSED(mask) (((gControllers->buttonDown) & (mask)) == (mask))

Config_ButtonAction Config_action()
{
    if (Config_gOnDeathAction)
    {
        return (Config_ButtonAction) Config_gOnDeathAction;
    }

    if (Hacktice_gConfig.lRAction && BUTTONS_PRESSED(L_TRIG | R_TRIG))
    {
        return (Config_ButtonAction) Hacktice_gConfig.lRAction;
    }
    else if (Hacktice_gConfig.lAction && BUTTONS_PRESSED(L_TRIG))
    {
        return (Config_ButtonAction) Hacktice_gConfig.lAction;
    }
    else if (Hacktice_gConfig.cButtonsAction && BUTTONS_PRESSED(U_CBUTTONS | D_CBUTTONS | R_CBUTTONS | L_CBUTTONS))
    {
        return (Config_ButtonAction) Hacktice_gConfig.cButtonsAction;
    }
    else if (Hacktice_gConfig.dpadDownAction && BUTTONS_PRESSED(D_JPAD))
    {
        return (Config_ButtonAction) Hacktice_gConfig.dpadDownAction;
    }
    else if (Hacktice_gConfig.dpadUpAction && BUTTONS_PRESSED(U_JPAD))
    {
        return (Config_ButtonAction) Hacktice_gConfig.dpadUpAction;
    }

    return Config_ButtonAction_OFF;
}
