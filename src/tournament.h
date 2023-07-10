#pragma once

typedef struct
{
    char locked;
    char length;
    char path;
} TournamentConfig;

extern TournamentConfig gTournamentConfig;

void Tournament_onFrame();
void Tournament_onNormal();

int Tournament_canPauseExit();
