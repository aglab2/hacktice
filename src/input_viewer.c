#include "input_viewer.h"

#include "binary.h"
#include "types.h"
#include "game/ingame_menu.h"
#include "game/print.h"
#include "libc/string.h"

#include "array_size.h"
#include "cfg.h"

#define ABS(x) (x > 0 ? x : -x)
#define POSITIVE(x) (x > 0)

typedef struct ButtonDescriptor
{
    const char* name;
    u16 mask; 
} ButtonDescriptor;

static ButtonDescriptor sButtonDescriptors[] = {
    { "A", A_BUTTON },
    { "B", B_BUTTON },
    { "*", Z_TRIG },
    { "C", R_TRIG },
    { "DU", U_JPAD },
    { "DL", L_JPAD },
    { "DR", R_JPAD },
    { "DD", D_JPAD },
    { "U", U_CBUTTONS },
    { "L", L_CBUTTONS },
    { "R", R_CBUTTONS },
    { "D", D_CBUTTONS },
};

void InputViewer_onNormal()
{
    Config_StickStyle stickStyle = Config_showStick();

    int x = gControllers->rawStickX;
    int y = gControllers->rawStickY;
    
    if (Config_StickStyle_VALUE == stickStyle)
    {
        print_text_fmt_int(270, 40, "%d", ABS(x));
        print_text_fmt_int(270, 20, "%d", ABS(y));
        if (x)
            print_text(250, 40, POSITIVE(x) ? "R" : "L");

        if (y)
            print_text(250, 20, POSITIVE(y) ? "U" : "D");
    }
    if (Config_StickStyle_GRAPHICS == stickStyle)
    {
        print_text(280, 30, "0");

        x = x * 20 / 120;
        y = y * 20 / 120;

        print_text(280 + x, 30 + y, "0");
    }

    bool showButtons = Config_showButtons();
    if (showButtons)
    {
        int activeButtons = gControllers->buttonPressed | gControllers->buttonDown;
        int off = 0;
        for (int i = 0; i < ARRAY_SIZE(sButtonDescriptors); i++)
        {
            ButtonDescriptor* desc = &sButtonDescriptors[i];
            if (activeButtons & desc->mask)
            {
                print_text(230 - off, 20, desc->name);
                off += 15 * strlen(desc->name);
            }
        }
    }
}