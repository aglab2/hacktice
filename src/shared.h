#pragma once

#define HACKTICE_CANARY 'HKTC'

#define HACKTICE_CONFIG_CANARY 'HCFG'

// Initial state when payload is written in RAM/ROM
#define HACKTICE_STATUS_INIT 'INIT'

// When payload is running, state is written to active
#define HACKTICE_STATUS_ACTIVE 'ACTV'

// Data Writeback was triggered, hacktice is disabled, written from ASM
#define HACKTICE_STATUS_DISABLED 'DSBL'

// Invalidate was called so tool can write upgraded code, written from ASM
#define HACKTICE_STATUS_CAN_UPGRADE 'UPGR'

// hacktice should never set it, used by tool to check if other state is written
#define HACKTICE_STATUS_RUNTIME_CHECK 'RTCK'
