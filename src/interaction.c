#include "interaction.h"

#include "game/interaction.h"
#include "game/memory.h"

#include "checkpoint.h"
#include "cfg.h"

typedef u32 (*InteractionHandlerFn)(struct MarioState *, u32, struct Object *);
typedef struct InteractionHandler {
    u32 interactType;
    InteractionHandlerFn handler;
} InteractionHandler;

static InteractionHandlerFn gOrigHandlers[32];

// TODO: drop hardcode
static InteractionHandler* sInteractionHandlers = (InteractionHandler*) 0x8032d950;

#define HOOK(name) \
static u32 hook_##name(struct MarioState* m, u32 v, struct Object* o) \
{ \
    Checkpoint_registerEvent(); \
    return gOrigHandlers[HOOK_INTERACT_##name](m, v, o); \
}

#define HOOK_INTERACT_HOOT           /* 0x00000001 */ 0
#define HOOK_INTERACT_GRABBABLE      /* 0x00000002 */ 1
#define HOOK_INTERACT_DOOR           /* 0x00000004 */ 2
#define HOOK_INTERACT_DAMAGE         /* 0x00000008 */ 3
#define HOOK_INTERACT_COIN           /* 0x00000010 */ 4
#define HOOK_INTERACT_CAP            /* 0x00000020 */ 5
#define HOOK_INTERACT_POLE           /* 0x00000040 */ 6
#define HOOK_INTERACT_KOOPA          /* 0x00000080 */ 7
#define HOOK_INTERACT_UNKNOWN_08     /* 0x00000100 */ 8
#define HOOK_INTERACT_BREAKABLE      /* 0x00000200 */ 9
#define HOOK_INTERACT_STRONG_WIND    /* 0x00000400 */ 10
#define HOOK_INTERACT_WARP_DOOR      /* 0x00000800 */ 11
#define HOOK_INTERACT_STAR_OR_KEY    /* 0x00001000 */ 12
#define HOOK_INTERACT_WARP           /* 0x00002000 */ 13
#define HOOK_INTERACT_CANNON_BASE    /* 0x00004000 */ 14
#define HOOK_INTERACT_BOUNCE_TOP     /* 0x00008000 */ 15
#define HOOK_INTERACT_WATER_RING     /* 0x00010000 */ 16
#define HOOK_INTERACT_BULLY          /* 0x00020000 */ 17
#define HOOK_INTERACT_FLAME          /* 0x00040000 */ 18
#define HOOK_INTERACT_KOOPA_SHELL    /* 0x00080000 */ 19
#define HOOK_INTERACT_BOUNCE_TOP2    /* 0x00100000 */ 20
#define HOOK_INTERACT_MR_BLIZZARD    /* 0x00200000 */ 21
#define HOOK_INTERACT_HIT_FROM_BELOW /* 0x00400000 */ 22
#define HOOK_INTERACT_TEXT           /* 0x00800000 */ 23
#define HOOK_INTERACT_TORNADO        /* 0x01000000 */ 24
#define HOOK_INTERACT_WHIRLPOOL      /* 0x02000000 */ 25
#define HOOK_INTERACT_CLAM_OR_BUBBA  /* 0x04000000 */ 26
#define HOOK_INTERACT_BBH_ENTRANCE   /* 0x08000000 */ 27
#define HOOK_INTERACT_SNUFIT_BULLET  /* 0x10000000 */ 28
#define HOOK_INTERACT_SHOCK          /* 0x20000000 */ 29
#define HOOK_INTERACT_IGLOO_BARRIER  /* 0x40000000 */ 30
#define HOOK_INTERACT_UNKNOWN_31     /* 0x80000000 */ 31

HOOK(WARP)

static u32 hook_COIN(struct MarioState* m, u32 v, struct Object* o) 
{
    bool redOnly = Config_checkpointRed() && !Config_checkpointCoin();
    bool notify = !redOnly;
    if (!notify)
    {
        // TODO: Remove hardcode
        notify = o && o->behavior == segmented_to_virtual((void*) 0x13003EAC);
    }

    if (notify)
        Checkpoint_registerEvent();
    
    return gOrigHandlers[HOOK_INTERACT_COIN](m, v, o); 
}

static void hookInteraction(int off, InteractionHandlerFn hook)
{
    int type = 1 << off;
    for (int i = 0; i < 31; i++)
    {
        InteractionHandler* interactionDesc = &sInteractionHandlers[i];
        if (interactionDesc->interactType != type)
            continue;

        if (gOrigHandlers[off] == NULL)
        {
            gOrigHandlers[off] = interactionDesc->handler;
            interactionDesc->handler = hook;
        }
        break;
    }
}

static void unhookInteraction(int off)
{
    int type = 1 << off;
    for (int i = 0; i < 31; i++)
    {
        InteractionHandler* interactionDesc = &sInteractionHandlers[i];
        if (interactionDesc->interactType != type)
            continue;

        if (gOrigHandlers[off] != NULL)
        {
            interactionDesc->handler = gOrigHandlers[off];
            gOrigHandlers[off] = NULL;
        }

        break;
    }
}

static inline bool isHooked(int off)
{
    return NULL != gOrigHandlers[off];
}

void Interaction_onNormal()
{
    if (Config_checkpointWarp() ^ isHooked(HOOK_INTERACT_WARP))
    {
        if (Config_checkpointWarp())
            hookInteraction(HOOK_INTERACT_WARP, hook_WARP);
        else
            unhookInteraction(HOOK_INTERACT_WARP);
    }
    
    bool coinOn = Config_checkpointRed() | Config_checkpointCoin();
    if (coinOn ^ isHooked(HOOK_INTERACT_COIN))
    {
        if (coinOn)
            hookInteraction(HOOK_INTERACT_COIN, hook_COIN);
        else
            unhookInteraction(HOOK_INTERACT_COIN);
    }
}
