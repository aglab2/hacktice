#include "music.h"
#include "cfg.h"

#include "audio/load.h"

// TODO: Drop hardcode
struct SequencePlayer* tSequencePlayers = (struct SequencePlayer*) 0x0000000080222618;

extern void play_sequence(u8 player, u8 seqId, u16 fadeTimer);

void Music_setVolumeHook(struct SequenceChannel *seqChannel, u8 volume)
{
    if (Config_muteMusic())
        volume = 0;

    seqChannel->volume = FLOAT_CAST(volume) / US_FLOAT(127.0);
}

void Music_onFrame()
{    
    int music = Config_musicNumber();
    if (!music)
        return;

    if (tSequencePlayers[0].seqId != music)
        play_sequence(0, music, 0);
}