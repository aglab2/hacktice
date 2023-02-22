#pragma once

#include "bool.h"

void Checkpoint_onNormal();

extern char Checkpoint_gShow;

static inline void Checkpoint_registerEvent()
{ Checkpoint_gShow = true; }
