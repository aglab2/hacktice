#include "string_conv.h"

namespace String
{
    void convert(int num, u8* dst)
    {
        auto digitCount = 0;
        if (num < 0)
        {
            digitCount++;
            num = -num;
            dst[0] = 0x9f;
        }

        if (0 == num)
        {
            dst[0] = 0;
            dst[1] = 0xff;
            return;
        }

        {
            auto val = num;
            while (val)
            {
                digitCount++;
                val /= 10;
            }
        }

        dst[digitCount] = 0xff;
        digitCount--;
        {
            auto val = num;
            while (val)
            {
                dst[digitCount] = val % 10;
                val /= 10;
                digitCount--;
            }
        }
    }
}