#include "version.h"

#include "game/print.h"
#include "game/area.h"

void Version_onFrame()
{
    if (__builtin_expect(gCurrLevelNum == 1, 0))
    {
        print_text_centered(160, 214, "HACKTICE "
#define HACKTICE_VERSION(maj, min, patch) #maj " " #min " " #patch
#include "xversion.h"
#undef HACKTICE_VERSION
        );
    };
}
