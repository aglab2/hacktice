#include "types.h"

extern "C" void* memset(void* s, int c, size_t len) 
{
    unsigned char *dst = reinterpret_cast<unsigned char*>(s);
    while (len > 0)
    {
        *dst = (unsigned char) c;
        dst++;
        len--;
    }
    return s;
}