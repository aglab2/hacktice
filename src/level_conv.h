namespace LevelConv
{
    enum class PlainLevels
    {
        OFF,
        C1,
        C2,
        C3,
        C4,
        C5,
        C6,
        C7,
        C8,
        C9,
        C10,
        C11,
        C12,
        C13,
        C14,
        C15,

        B1,
        B2,
        B3,

        Slide,

        MC,
        WC,
        VC,

        S1,
        S2,
        S3,
    };

    enum class SM64Levels
    {
        OFF = 0,
        C1 = 0x9,
        C2 = 0x18,
        C3 = 0x0c,
        C4 = 0x05,
        C5 = 0x04,
        C6 = 0x07,
        C7 = 0x16,
        C8 = 0x08,
        C9 = 0x17,
        C10 = 0x0a,
        C11 = 0x0b,
        C12 = 0x24,
        C13 = 0x0d,
        C14 = 0x0e,
        C15 = 0x0f,

        B1 = 0x11,
        B2 = 0x13,
        B3 = 0x15,

        Slide = 0x1b,

        MC = 0x1c,
        WC = 0x1d,
        VC = 0x12,

        S1 = 0x1f,
        S2 = 0x14,
        S3 = 0x19,
    };

    SM64Levels toSM64Level(PlainLevels);
    PlainLevels toPlainLevel(SM64Levels);
} // namespace LevelConv
