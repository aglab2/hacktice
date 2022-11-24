#include "text_manager.h"

#include "game/print.h"

typedef struct Line
{
    const char* str;
    int timeout;
} Line;

#define LineCount 9
static Line sLines[LineCount] = { 0 };

void TextManager_onFrame()
{
    for (int i = 0; i < LineCount; i++)
    {
        Line* line = &sLines[i];
        if (line->timeout == 0)
            continue;

        print_text(10, 20 + 20 * i, line->str);
        line->timeout--;
    }
}

void TextManager_onVi()
{

}

void TextManager_addLine(const char* str, int timeout)
{
    for (int i = 0; i < LineCount; i++)
    {
        Line* line = &sLines[i];
        if (line->timeout != 0 && line->str == str)
        {
            line->timeout = timeout;
            return;
        }
    }

    for (int i = 0; i < LineCount; i++)
    {
        Line* line = &sLines[i];
        if (line->timeout == 0)
        {
            line->str = str;
            line->timeout = timeout;
            return;
        }
    }
}
