#include "music.h"
#include "cfg.h"
extern "C"
{
    #include "audio/load.h"
}

auto tSequencePlayers = (struct SequencePlayer*) 0x0000000080222618;

extern "C" void play_sequence(u8 player, u8 seqId, u16 fadeTimer);

void Music::setVolumeHook(struct SequenceChannel *seqChannel, u8 volume)
{
    if (Config::muteMusic())
        volume = 0;

    seqChannel->volume = FLOAT_CAST(volume) / US_FLOAT(127.0);
}

void Music::onFrame()
{    
    auto music = Config::musicNumber();
    if (!music)
        return;

    if (tSequencePlayers[0].seqId != music)
        play_sequence(0, music, 0);
}