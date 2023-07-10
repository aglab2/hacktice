#include "tournament.h"

#include "binary.h"
#include "cfg.h"
#include "level_conv.h"
#include "text_manager.h"

#include "game/area.h"
#include "game/display.h"
#include "game/game.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/print.h"
#include "game/object_helpers.h"
#include "engine/behavior_script.h"
#include "libc/stdio.h"
#include "sm64.h"

#define SAVE_FLAG_HAVE_WING_CAP          /* 0x000002 */ (1 << 1)
#define SAVE_FLAG_HAVE_METAL_CAP         /* 0x000004 */ (1 << 2)
#define SAVE_FLAG_HAVE_VANISH_CAP        /* 0x000008 */ (1 << 3)
extern void save_file_set_flags(s32 flags);

typedef struct
{
    f32 elem[3];
} triplet;

typedef struct
{
    const triplet* triplet;
    int length;
} Path;

static const triplet sPathZAR[] = { 
    { 2878, 1944, -6880 },
    { 2532, 2044, -2028 },
    { -1511, 2044, -1674 },
    { -1383, 2711, 2979 }
};
static const triplet sPathDMG[] = {
    { 9405, 360, 6189 },
    { 7885, -1346, 5273 },
    { 4001, -1136, 4543 },
    { 2695, 184, 3295 },
    { -5582, 1864, -4123 },
    { -8179, 4804, -5612 }, 
    { -8459, 4890, 1736 } 
};
static const triplet sPathCC[] = {
    { -5232, 508, -11098 },
    { 4239, 780, -728 },
    { 4420, 4350, 944 },
    { 4982, 4410, -60 } 
};
static const triplet sPathMNE[] = {
    { -486, 0, 193 },
    { 1550, 450, 648 },
    { 4195, -300, 2291 },
    { 6808, 180, -3410 },
    { 7213, 1702, -720 } 
};
static const triplet sPathSR0[] = {
    { -920, -53, 395 },
    { 2791, 2586, 1396 },
};
static const triplet sPathMF[] = {
    { -2368, 5659, 3008 },
    { -2819, 7264, 1245 },
    { -3597, 8397, 1866 },
};
static const triplet sPathSM4[] = {
    { -4066, 296, 5357 },
    { -2471, 2524, -939 },
    { -566, 3526, 3336 },
    { -569, 7660, 7341 },
};
static const triplet sPathPM[] = {
    { -6859, 1320, 6301 },
    { -5080, 2534, 402 },
    { 244, 4253, 1637 },
    { 3585, 3900, -1102 },
};
static const triplet sPathLC[] = {
    { 0, 1829, 0 },
    { -2440, 2923, -2450 },
    { -1230, 5076, -3477 },
    { -1621, 6096, -1306 },
    { -767, 8076, -1445 },
    { 5398, 8020, -2444 },
};
static const triplet sPathSR[] = {
    { -2081, 1019, -5519 },
    { -6035, 390, 2924 },
};
static const triplet sPathCG[] = {
    { -3469, 1002, -6700 },
    { -331, 290, -2124 },
    { 237, 240, 409 },
    { 2375, -785, 1455 },
    { 6912, 841, 7187 },
    { -1391, 2583, 11006 },
};
static const triplet sPathSR5[] = {
    { -3099, -1028, -1462 },
    { -5791, -1169, -5645 },
    { -7993, -119, -3166 },
    { -8248, -689, -52 },
    { -10040, 371, 1889 },
    { -5040, 1236, -6158 },
};
static const triplet sPathKATZE[] = {
    { 1756, 349, 292 },
    { -941, 323, -1916 },
    { -1326, 1343, 394 },
    { -467, 2497, 526 },
};
static const triplet sPathTW[] = {
    { -145, -418, 3189 },
    { -951, 1137, -14059 },
    { 2714, 3727, -15046 },
};


#define PATH_VALUE(p) { p, sizeof(p) / sizeof(*p) }
static const Path sPaths[] = { 
    PATH_VALUE(sPathZAR),
    PATH_VALUE(sPathDMG),
    PATH_VALUE(sPathCC),
    PATH_VALUE(sPathMNE),
    PATH_VALUE(sPathSR0),
    PATH_VALUE(sPathMF),
    PATH_VALUE(sPathSM4),
    PATH_VALUE(sPathPM),
    PATH_VALUE(sPathLC),
    PATH_VALUE(sPathSR),
    PATH_VALUE(sPathCG),
    PATH_VALUE(sPathSR5),
    PATH_VALUE(sPathKATZE),
    PATH_VALUE(sPathTW),
};

TournamentConfig gTournamentConfig = {
    .locked = true,
    .path = true,
};

enum TournamentMode
{
    TM_OFF,
    TM_TO_START,
    TM_RUNNING,
};

static bool sTournamentMode = TM_OFF;
static bool sCourse = 0;
static int sTimeLeft = 0;
static int sPersonalBest = 0;

static char sTimeLeftDefaultsMinute[] = { 5, 7, 10, };

extern void render_hud_tex_lut(s32 x, s32 y, u8 *texture);
void render_timer_at(int xoff, int yoff, u16 timerValFrames)
{
    u16 timerMins;
    u16 timerSecs;
    u16 timerFracSecs;

    timerMins = timerValFrames / (30 * 60);
    timerSecs = (timerValFrames - (timerMins * 1800)) / 30;
    timerFracSecs = ((timerValFrames - (timerMins * 1800) - (timerSecs * 30)) & 0xFFFF) * 3.33333333333f;

    print_text_fmt_int(xoff - 91, yoff, "%0d", timerMins);
    print_text_fmt_int(xoff - 71, yoff, "%02d", timerSecs);
    print_text_fmt_int(xoff - 37, yoff, "%02d", timerFracSecs);
}

void Tournament_onFrame()
{
    static int lastTime = 0;
    if (lastTime != gGlobalTimer)
    {
        lastTime = gGlobalTimer;
        if (sTournamentMode == TM_RUNNING)
        {
            if (sTimeLeft)
            {
                sTimeLeft--;
                render_timer_at(110, 210, sTimeLeft);
            }
            else
            {
                print_text(20, 210, "TIME IS UP");
            }
        }
    }

    // hack
    if (gGlobalTimer < 30)
        return;

    if (gTournamentConfig.locked)
    {
        bzero(&Hacktice_gConfig.speed, sizeof(Hacktice_gConfig) - 2 * sizeof(s32));
        Hacktice_gConfig.timerShow = true;
        if (sTournamentMode == TM_RUNNING && sTimeLeft)
        {
            Hacktice_gConfig.lAction = Config_ButtonAction_LEVEL_RESET_WARP;
            Hacktice_gConfig.deathAction = Config_DeathAction_LEVEL_RESET;
        }
        // else bzero
        
        if (gCurrLevelNum == 16)
        {
            static const char sTournamentModeText[] = "TOURNAMENT MODE ON";
            TextManager_addLine(sTournamentModeText, 1);
            
            static char sTournamentModeLength[20];
            sprintf(sTournamentModeLength, "%d MINUTES ROUND", sTimeLeftDefaultsMinute[gTournamentConfig.length]);
            TextManager_addLine(sTournamentModeLength, 1);

            TextManager_addLine("PATCH 1", 1);
        }
    }
}

void play_clear()
{
    if (14 == gCurrCourseNum)
        return;
    if (8 == gCurrCourseNum)
        return;
    if (2 == gCurrCourseNum)
        return;

    play_sequence(1, 1, 0);
}

void update_pb()
{
    static int LastUpdateTime = 0;
    bool skip = (LastUpdateTime == gGlobalTimer) || (LastUpdateTime == (gGlobalTimer - 1));
    LastUpdateTime = gGlobalTimer;

    if (skip)
        return;

    static char PbStatus[32];

    if (!sPersonalBest)
    {
        sPersonalBest = gHudDisplay.timer;
        sprintf(PbStatus, "FIRST PB");
        play_clear();
    }
    else
    {
        if (sPersonalBest > gHudDisplay.timer)
        {
            play_clear();
            int diff = sPersonalBest - gHudDisplay.timer;
            sPersonalBest = gHudDisplay.timer;
            if (diff > 100)
            {
                sprintf(PbStatus, "%d SECONDS BEST", diff / 30);
            }
            else
            {
                if (diff > 1)
                    sprintf(PbStatus, "%d FRAMES BEST", diff);
                else
                    sprintf(PbStatus, "1 FRAME BEST");
            }
        }
        else if (sPersonalBest == gHudDisplay.timer)
        {
            sprintf(PbStatus, "TIED WITH PB");
        }
        else
        {
            int diff = gHudDisplay.timer - sPersonalBest;
            if (diff < 100)
            {
                if (diff > 1)
                    sprintf(PbStatus, "%d FRAMES WORSE", diff);
                else
                    sprintf(PbStatus, "1 FRAME WORSE");
            }
            else if (diff < 500)
            {
                sprintf(PbStatus, "%d SECONDS WORSE", diff / 30);
            }
        }
    }

    TextManager_addLine(PbStatus, 200);
}

static f32 distance_between(const triplet* a, const triplet* b)
{
    f32 length = 0;
    for (int i = 0; i < 3; i++)
    {
        f32 d = a->elem[i] - b->elem[i];
        length += sqrtf(d*d);
    }

    return length;
}

static f32 lerpf(f32 a, f32 b, f32 amt)
{
    return a + amt * (b - a);
}

static void lerp(const triplet* a, const triplet* b, f32 amt, triplet* res)
{
    for (int i = 0; i < 3; i++)
    {
        res->elem[i] = lerpf(a->elem[i], b->elem[i], amt);
    }
}

static void render_path(const triplet* line, int cnt)
{
    if (!gMarioObject)
        return;

    static const triplet* LastLine = NULL;
    static f32 LineLength;
    if (LastLine != line)
    {
        LineLength = 0;
        for (int i = 1; i < cnt; i++)
        {
            const triplet* curr = &line[i - 1];
            const triplet* next = &line[i];
            LineLength += distance_between(curr, next);
        }
    }
    LastLine = line;

    for (int j = 0; j < LineLength / 7000.f; j++)
    {
        f32 where = 0.99f * LineLength * RandomFloat();
        triplet pos;
        for (int i = 1; i < cnt; i++)
        {
            const triplet* curr = &line[i - 1];
            const triplet* next = &line[i];
            f32 d = distance_between(curr, next);
            if (d >= where)
            {
                lerp(curr, next, where / d, &pos);
                break;
            }
            else
            {
                where -= d;
            }
        }

        struct Object* sparkle = spawn_object(gMarioObject, 0x8F, (const BehaviorScript*) 0x13002ad0);
        sparkle->oPosX = pos.elem[0];
        sparkle->oPosY = pos.elem[1];
        sparkle->oPosZ = pos.elem[2];
    }
}

extern unsigned char sPage;
void Tournament_onNormal()
{
    if (gTournamentConfig.path)
    {
        if (1 <= gCurrCourseNum && gCurrCourseNum <= 15)
        {
            const Path* path = &sPaths[gCurrCourseNum - 1];
            render_path(path->triplet, path->length);
        }
    }

    if (gCurrLevelNum == 16)
    {
        sTournamentMode = gTournamentConfig.locked ? TM_TO_START : TM_OFF;
        sTimeLeft = 0;
    }
    else
    {
        if ((sTournamentMode == TM_TO_START) 
         || (sTournamentMode == TM_RUNNING && sCourse != gCurrLevelNum))
        {
            save_file_set_flags(SAVE_FLAG_HAVE_WING_CAP | SAVE_FLAG_HAVE_METAL_CAP | SAVE_FLAG_HAVE_VANISH_CAP);
            sPage = 0;
            sTournamentMode = TM_RUNNING;
            sPersonalBest = 0;
            sCourse = gCurrLevelNum;
            sTimeLeft = sTimeLeftDefaultsMinute[gTournamentConfig.length] * 30 * 60;
        }

        if (sCourse != gCurrLevelNum)
        {
            sPersonalBest = 0;
            sCourse = gCurrLevelNum;
        }

        if (gMarioStates->action == ACT_FALL_AFTER_STAR_GRAB || gMarioStates->action == ACT_STAR_DANCE_WATER || gMarioStates->action == ACT_STAR_DANCE_EXIT)
        {
            update_pb();
            if (sTimeLeft)
                Config_setOnDeathAction(Config_ButtonAction_LEVEL_RESET_WARP);
        }
    }

    if (sPersonalBest)
    {
        render_timer_at(320, 210, sPersonalBest);
    }
}

int Tournament_canPauseExit()
{
    if (!gTournamentConfig.locked)
        return true;

    if (sTournamentMode != TM_RUNNING)
        return true;

    return 0 == sTimeLeft;
}
