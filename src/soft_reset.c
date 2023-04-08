#include "soft_reset.h"

#include "types.h"
#include "game/game.h"
#include "game/level_update.h"
#include "cfg.h"

extern u16 gRandomSeed16;
void SoftReset_onFrame()
{
    const int ResetCombo = L_TRIG | Z_TRIG;
    if (Hacktice_gConfig.softReset && (ResetCombo == (gPlayer1Controller->buttonDown & ResetCombo)))
    {
        sCurrPlayMode = 4;
        sWarpDest.type = 1;
        sWarpDest.levelNum = 1;
        gRandomSeed16 = 0;
    }
}
