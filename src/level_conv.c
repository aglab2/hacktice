#include "level_conv.h"

LevelConv_SM64Levels LevelConv_toSM64Level(LevelConv_PlainLevels pl)
{
    static char levels[] = 
    {
        LevelConv_SM64Levels_OFF,
        LevelConv_SM64Levels_C1,
        LevelConv_SM64Levels_C2,
        LevelConv_SM64Levels_C3,
        LevelConv_SM64Levels_C4,
        LevelConv_SM64Levels_C5,
        LevelConv_SM64Levels_C6,
        LevelConv_SM64Levels_C7,
        LevelConv_SM64Levels_C8,
        LevelConv_SM64Levels_C9,
        LevelConv_SM64Levels_C10,
        LevelConv_SM64Levels_C11,
        LevelConv_SM64Levels_C12,
        LevelConv_SM64Levels_C13,
        LevelConv_SM64Levels_C14,
        LevelConv_SM64Levels_C15,

        LevelConv_SM64Levels_B1,
        LevelConv_SM64Levels_B2,
        LevelConv_SM64Levels_B3,

        LevelConv_SM64Levels_Slide,

        LevelConv_SM64Levels_MC,
        LevelConv_SM64Levels_WC,
        LevelConv_SM64Levels_VC,

        LevelConv_SM64Levels_S1,
        LevelConv_SM64Levels_S2,
        LevelConv_SM64Levels_S3,
    };

    return (LevelConv_SM64Levels) levels[(int) pl];
}
