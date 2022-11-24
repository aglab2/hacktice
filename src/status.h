#pragma once

#include "types.h"

extern uintptr_t _start[];

#define HACKTICE_START_STATUS_OFFSET 6

static inline uintptr_t HackticeGetStatus()
{ return _start[HACKTICE_START_STATUS_OFFSET]; }
static inline void HackticeSetStatus(uintptr_t status)
{ _start[HACKTICE_START_STATUS_OFFSET] = status; }
