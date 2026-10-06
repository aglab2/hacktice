#include "string_conv.h"

void String_convert(int num, HC* dst)
{
#if BINARY
    int digitCount = 0;
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
        int val = num;
        while (val)
        {
            digitCount++;
            val /= 10;
        }
    }

    dst[digitCount] = 0xff;
    digitCount--;
    {
        int val = num;
        while (val)
        {
            dst[digitCount] = val % 10;
            val /= 10;
            digitCount--;
        }
    }
#else
    sprintf(dst, "%d", num);
#endif
}
