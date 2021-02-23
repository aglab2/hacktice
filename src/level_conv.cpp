#include "level_conv.h"

LevelConv::SM64Levels LevelConv::toSM64Level(PlainLevels pl)
{
    static SM64Levels levels[] = 
    {
        SM64Levels::OFF,
        SM64Levels::C1,
        SM64Levels::C2,
        SM64Levels::C3,
        SM64Levels::C4,
        SM64Levels::C5,
        SM64Levels::C6,
        SM64Levels::C7,
        SM64Levels::C8,
        SM64Levels::C9,
        SM64Levels::C10,
        SM64Levels::C11,
        SM64Levels::C12,
        SM64Levels::C13,
        SM64Levels::C14,
        SM64Levels::C15,

        SM64Levels::B1,
        SM64Levels::B2,
        SM64Levels::B3,

        SM64Levels::Slide,

        SM64Levels::MC,
        SM64Levels::WC,
        SM64Levels::VC,

        SM64Levels::S1,
        SM64Levels::S2,
        SM64Levels::S3,
    };

    return levels[(int) pl];
}
