#include "types.h"

extern "C"
{
    #include "audio/internal.h"
}

namespace Music
{
    void setVolumeHook(struct SequenceChannel *seqChannel, u8 volume);
    void onFrame();
}
