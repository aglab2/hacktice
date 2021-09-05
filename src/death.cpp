#include "death.h"
#include "cfg.h"

extern "C"
{
    #include "game/level_update.h"
    #include "game/print.h"
}

void Death::onNormal()
{
    bool dead = gMarioState->action == 0x00021312 || gMarioState->health <= 0xff;
    if (dead)
    {
        auto action = Config::deathAction();
        switch (action)
        {
            case Config::DeathAction::OFF:
            break;
            case Config::DeathAction::ACT_RESET:
            return Config::setOnDeathAction(Config::ButtonAction::ACT_SELECT);
            case Config::DeathAction::LEVEL_RESET:
            return Config::setOnDeathAction(Config::ButtonAction::LEVEL_RESET_WARP);
            case Config::DeathAction::LOAD_STATE:
            return Config::setOnDeathAction(Config::ButtonAction::LOAD_STATE);
        }
    }

    return Config::setOnDeathAction(Config::ButtonAction::OFF);
}
