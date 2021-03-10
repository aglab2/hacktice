#include "music.h"
#include "cfg.h"

void Music::setVolumeHook(struct SequenceChannel *seqChannel, u8 volume)
{
    if (Config::muteMusic())
        volume = 0;

    seqChannel->volume = FLOAT_CAST(volume) / US_FLOAT(127.0);
}
