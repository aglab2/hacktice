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
#endif

// get_str_x_pos_from_center is different in binary
#ifdef BINARY
#define GET_STR_X_POS_FROM_CENTER(c, s, f) get_str_x_pos_from_center(c, s)
s16 get_str_x_pos_from_center(s16 centerPos, const u8 *str);
#else
#define GET_STR_X_POS_FROM_CENTER(c, s, f) get_str_x_pos_from_center(c, (u8*) s, f)
#endif

#ifdef BINARY
#define PLAY_SEQUENCE play_sequence
void play_sequence(u8 player, u8 seqId, u16 fadeTimer);
#else
// #define PLAY_SEQUENCE seq_player_play_sequence
#define PLAY_SEQUENCE play_sequence
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
