#include "custom_text.h"

#include "cfg.h"
#include "text_manager.h"

void CustomText_onFrame()
{
    if (Hacktice_gConfig.showCustomText)
    {
        TextManager_addLine(Hacktice_gConfig.customText, 1);
    }
}
