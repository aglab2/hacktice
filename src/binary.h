// Bunch of culprits to support both binary and decomp
// It is more oriented towards binary though

#pragma once

// game <-> game_init
#ifdef BINARY
#include "types.h"
#include "game/game.h"
#else
#include <ultra64.h>
#include "sm64.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/print.h"
#endif

#ifdef BINARY
#define PLAY_SEQUENCE play_sequence
void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
#else
#define PLAY_SEQUENCE seq_player_play_sequence
// #define PLAY_SEQUENCE play_sequence
void seq_player_play_sequence(u8 player, u8 seqId, u16 arg2);
#endif

#ifdef BINARY
static struct SequencePlayer* tSequencePlayers = (struct SequencePlayer*) 0x80222618;
#else
#include "audio/load.h"
UNUSED static struct SequencePlayer* tSequencePlayers = gSequencePlayers;
#endif

// I have to put those here because C is dumb
typedef u32 (*InteractionHandlerFn)(struct MarioState *, u32, struct Object *);
typedef struct InteractionHandler {
    u32 interactType;
    InteractionHandlerFn handler;
} InteractionHandler;

#ifdef BINARY
static struct InteractionHandler* sInteractionHandlers = (struct InteractionHandler*) 0x8032d950;
#else
extern struct InteractionHandler sInteractionHandlers[];
#endif

#ifdef BINARY
static void* sCourseNames = (void*) 0x02010f68;
#else
extern u8 seg2_course_name_table[];
UNUSED static const void* sCourseNames = (void*) seg2_course_name_table;
#endif

#ifdef BINARY
#define MARIO_FALL_SOUND_PLAYED MARIO_UNKNOWN_18
#endif

#ifdef BINARY
#define HC u8
#else
#define HC char
#endif

#ifndef BINARY
static inline void print_text_centered(int x, int y, const char* str)
{ print_text_aligned(x, y, str, TEXT_ALIGN_CENTER); }
#endif

#ifdef BINARY
#define Hacktice_gState ((State*) 0x80026000)
#else
#define Hacktice_gState ((State*) 0x80600000)
#endif

#ifdef BINARY
#define gMarioAnimsMemAlloc D_80339CF0
#define gMarioAnimsBuf D_80339D10
#define MARIO_ANIMS_POOL_SIZE 0x4000
#else
extern struct DmaHandlerList gMarioAnimsBuf;
#endif
