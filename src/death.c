#include "death.h"
#include "cfg.h"

#include "game/level_update.h"
#include "game/print.h"

void Death_onNormal()
{
    bool dead = gMarioState->action == 0x00021312 || gMarioState->health <= 0xff;
    if (dead)
    {
        Config_DeathAction action = Config_deathAction();
        switch (action)
        {
            case Config_DeathAction_OFF:
            break;
            case Config_DeathAction_ACT_RESET:
            return Config_setOnDeathAction(Config_ButtonAction_ACT_SELECT);
            case Config_DeathAction_LEVEL_RESET:
            return Config_setOnDeathAction(Config_ButtonAction_LEVEL_RESET_WARP);
            case Config_DeathAction_LOAD_STATE:
            return Config_setOnDeathAction(Config_ButtonAction_LOAD_STATE);
        }
    }

    return Config_setOnDeathAction(Config_ButtonAction_OFF);
}
