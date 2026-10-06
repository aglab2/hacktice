#pragma once

#include "types.h"

extern uintptr_t Hacktice_start[];

#define HACKTICE_START_STATUS_OFFSET 6
#define HACKTICE_START_SAVESTATE_OFFSET 8

static inline uintptr_t HackticeGetStatus()
{ return Hacktice_start[HACKTICE_START_STATUS_OFFSET]; }
static inline void HackticeSetStatus(uintptr_t status)
{ Hacktice_start[HACKTICE_START_STATUS_OFFSET] = status; }

static inline void HackticeSetSaveState(uintptr_t status)
{ Hacktice_start[HACKTICE_START_SAVESTATE_OFFSET] = status; }
