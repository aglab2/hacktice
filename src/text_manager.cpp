#include "text_manager.h"
extern "C"
{
    #include "game/print.h"
}

struct Line
{
    const char* str;
    int timeout;
};

constexpr int LineCount = 9;
static Line sLines[LineCount] = {};

void TextManager::onFrame()
{
    for (int i = 0; i < LineCount; i++)
    {
        auto& line = sLines[i];
        if (line.timeout == 0)
            continue;

        print_text(10, 20 + 20 * i, line.str);
        line.timeout--;
    }
}

void TextManager::onVi()
{

}

void TextManager::addLine(const char* str, int timeout)
{
    for (int i = 0; i < LineCount; i++)
    {
        auto& line = sLines[i];
        if (line.timeout != 0 && line.str == str)
        {
            line.timeout = timeout;
            return;
        }
    }

    for (int i = 0; i < LineCount; i++)
    {
        auto& line = sLines[i];
        if (line.timeout == 0)
        {
            line = { str, timeout };
            return;
        }
    }
}
