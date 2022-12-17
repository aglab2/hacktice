#include "death.h"
#include "cfg.h"

#include "game/level_update.h"
#include "game/print.h"

bool Death_TouchedDeathFloor = false;

void Death_onNormal()
{
    bool dead = Death_TouchedDeathFloor || gMarioState->action == 0x00021312 || gMarioState->health <= 0xff;
    Death_TouchedDeathFloor = false;
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
