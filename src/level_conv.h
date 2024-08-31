typedef enum LevelConv_PlainLevels
{
    LevelConv_PlainLevels_OFF,
    LevelConv_PlainLevels_C1,
    LevelConv_PlainLevels_C2,
    LevelConv_PlainLevels_C3,
    LevelConv_PlainLevels_C4,
    LevelConv_PlainLevels_C5,
    LevelConv_PlainLevels_C6,
    LevelConv_PlainLevels_C7,
    LevelConv_PlainLevels_C8,
    LevelConv_PlainLevels_C9,
    LevelConv_PlainLevels_C10,
    LevelConv_PlainLevels_C11,
    LevelConv_PlainLevels_C12,
    LevelConv_PlainLevels_C13,
    LevelConv_PlainLevels_C14,
    LevelConv_PlainLevels_C15,

    LevelConv_PlainLevels_B1,
    LevelConv_PlainLevels_B2,
    LevelConv_PlainLevels_B3,

    LevelConv_PlainLevels_Slide,

    LevelConv_PlainLevels_MC,
    LevelConv_PlainLevels_WC,
    LevelConv_PlainLevels_VC,

    LevelConv_PlainLevels_S1,
    LevelConv_PlainLevels_S2,
    LevelConv_PlainLevels_S3,

    LevelConv_PlainLevels_F1,
    LevelConv_PlainLevels_F2,
    LevelConv_PlainLevels_F3,
} LevelConv_PlainLevels;

typedef enum LevelConv_SM64Levels
{
    LevelConv_SM64Levels_OFF = 0,
    LevelConv_SM64Levels_C1 = 0x9,
    LevelConv_SM64Levels_C2 = 0x18,
    LevelConv_SM64Levels_C3 = 0x0c,
    LevelConv_SM64Levels_C4 = 0x05,
    LevelConv_SM64Levels_C5 = 0x04,
    LevelConv_SM64Levels_C6 = 0x07,
    LevelConv_SM64Levels_C7 = 0x16,
    LevelConv_SM64Levels_C8 = 0x08,
    LevelConv_SM64Levels_C9 = 0x17,
    LevelConv_SM64Levels_C10 = 0x0a,
    LevelConv_SM64Levels_C11 = 0x0b,
    LevelConv_SM64Levels_C12 = 0x24,
    LevelConv_SM64Levels_C13 = 0x0d,
    LevelConv_SM64Levels_C14 = 0x0e,
    LevelConv_SM64Levels_C15 = 0x0f,

    LevelConv_SM64Levels_B1 = 0x11,
    LevelConv_SM64Levels_B2 = 0x13,
    LevelConv_SM64Levels_B3 = 0x15,

    LevelConv_SM64Levels_Slide = 0x1b,

    LevelConv_SM64Levels_MC = 0x1c,
    LevelConv_SM64Levels_WC = 0x1d,
    LevelConv_SM64Levels_VC = 0x12,

    LevelConv_SM64Levels_S1 = 0x1f,
    LevelConv_SM64Levels_S2 = 0x14,
    LevelConv_SM64Levels_S3 = 0x19,

    LevelConv_SM64Levels_F1 = 0x1e,
    LevelConv_SM64Levels_F2 = 0x21,
    LevelConv_SM64Levels_F3 = 0x22,
} LevelConv_SM64Levels;

LevelConv_SM64Levels LevelConv_toSM64Level(LevelConv_PlainLevels);
