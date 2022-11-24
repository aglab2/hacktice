#include "strings.h"

const u8 u4_CBUTTONS_ACTION[] = { 0x04, 0x0C, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uACT_SELECT[] = { 0x0A, 0x0C, 0x1D, 0x9E, 0x1C, 0x0E, 0x15, 0x0E, 0x0C, 0x1D, 0xFF };
const u8 uBURNING[] = { 0x0B, 0x1E, 0x1B, 0x17, 0x12, 0x17, 0x10, 0xFF };
const u8 uBUTTON[] = { 0x0B, 0x1E, 0x1D, 0x1D, 0x18, 0x17, 0xFF };
const u8 uBUTTONS[] = { 0x0B, 0x1E, 0x1D, 0x1D, 0x18, 0x17, 0x1C, 0xFF };
const u8 uCANNON[] = { 0X0C, 0X0A, 0x17, 0x17, 0x18, 0x17, 0xFF };
const u8 uCOIN[] = { 0X0C, 0x18, 0x12, 0x17, 0xFF };
const u8 uCHECKPOINTS[] = { 0x16, 0x12, 0x1C, 0x0C, 0x0E, 0x15, 0x15, 0x0A, 0x17, 0x0E, 0x18, 0x1E, 0x1C, 0x9E, 0x1D, 0x12, 0x16, 0x0E, 0x1B, 0x1C, 0xFF };
const u8 uC_DOWN[] = { 0x0C, 0x9E, 0x0D, 0x18, 0x20, 0x17, 0xFF };
const u8 uC_UP[] = { 0x0C, 0x9E, 0x1E, 0x19, 0xFF };
const u8 uDEATH_ACTION[] = { 0x0D, 0x0E, 0x0A, 0x1D, 0x11, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uDISTANCE_TO_RED[] = { 0X0D, 0x9E, 0x1D, 0x18, 0x9E, 0x1B, 0x0E, 0x0D, 0xFF };
const u8 uDISTANCE_TO_SECRET[] = { 0X0D, 0x9E, 0x1D, 0x18, 0x9E, 0x1C, 0x0E, 0x0C, 0x1B, 0x0E, 0x1D, 0xFF };
const u8 uDOOR[] = { 0x0D, 0x18, 0x18, 0x1B, 0xFF };
const u8 uDOWN[] = { 0x51, 0xff };
const u8 uDPAD_DOWN_ACTION[] = { 0X0D, 0x9E, 0x0D, 0x18, 0x20, 0x17, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uGENERAL[] = { 0x10, 0x0E, 0x17, 0x0E, 0x1B, 0x0A, 0x15, 0x9E, 0x0C, 0x18, 0x17, 0x0F, 0x12, 0x10, 0x1C, 0xFF };
const u8 uGRAB[] = { 0x10, 0x1B, 0x0A, 0x0B, 0xFF };
const u8 uGRAPHICS[] = { 0x10, 0x1B, 0x0A, 0x19, 0x11, 0x12, 0x0C, 0x1C, 0xFF };
const u8 uGROUNDPOUND[] = { 0X10, 0x1B, 0x18, 0x1E, 0x17, 0x0D, 0x19, 0x18, 0x1E, 0x17, 0x0D, 0xFF };
const u8 uNORMAL[] = { 0x17, 0x18, 0x1B, 0x16, 0x0A, 0x15, 0xFF };
const u8 uOBJECT[] = { 0x18, 0x0B, 0x13, 0x0E, 0X0C, 0x1D, 0xFF };
const u8 uOFF[] = { 0x18, 0x0F, 0x0F, 0xFF };
const u8 uON[] = { 0x18, 0x17, 0xFF };
const u8 uLACTION[] = { 0x15, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uLAVA[] = { 0x15, 0x0A, 0x1F, 0x0A, 0xFF };
const u8 uLRACTION[] = { 0x15, 0xE4, 0x1B, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uLEFT_Z[] = { 0x52, 0x23, 0xff };
const u8 uLEFT_DPAD[] = { 0x0D, 0x19, 0x0A, 0x0D, 0x9E, 0x15, 0x0E, 0x0F, 0x1D, 0x52, 0xff };
const u8 uLEVEL_RESET[] = { 0X15, 0x0E, 0x1F, 0x0E, 0x15, 0x9E, 0x1B, 0x0E, 0x1C, 0x0E, 0x1D, 0xFF };
const u8 uLEVEL_RESET_WARP[] = { 0x1C, 0x1D, 0x0A, 0x1B, 0x1D, 0x9E, 0x1B, 0x0E, 0x1C, 0x0E, 0x1D, 0xFF };
const u8 uLEVITATE[] = { 0x15, 0x0E, 0x1F, 0x12, 0x1D, 0x0A, 0x1D, 0x0E, 0xFF };
const u8 uLOAD_STATE[] = { 0X15, 0x18, 0x0A, 0x0D, 0x9E, 0x1C, 0x1D, 0x0A, 0x1D, 0x0E, 0xFF };
const u8 uMUTE_MUSIC[] = { 0x16, 0x1E, 0x1D, 0x0E, 0x9E, 0x16, 0x1E, 0x1C, 0x12, 0x0C, 0xFF };
const u8 uMUSIC_NUMBER[] = { 0X16, 0x1E, 0x1C, 0x12, 0x0C, 0x9E, 0x17, 0x1E, 0x16, 0x0B, 0x0E, 0x1B, 0xFF };
const u8 uPAUSE[] = { 0x19, 0x0A, 0x1E, 0x1C, 0x0E, 0xFF };
const u8 uPLATFORM[] = { 0x19, 0X15, 0x0A, 0x1D, 0x0F, 0x18, 0x1B, 0X16, 0xFF };
const u8 uPOLE[] = { 0x19, 0x18, 0x15, 0x0E, 0xFF };
const u8 uRED[] = { 0x1B, 0x0E, 0x0D, 0xFF };
const u8 uRIGHT_R[] = { 0x1B, 0x53, 0xFF };
const u8 uRIGHT_DPAD[] = { 0x53, 0x0D, 0x19, 0x0A, 0x0D, 0x9E, 0x1B, 0x12, 0x10, 0x11, 0x1D, 0xFF };
const u8 uSSAVESTYLE[] = { 0x1C, 0x1C, 0x0A, 0x1F, 0x0E, 0x9E, 0x1C, 0x1D, 0x22, 0x15, 0x0E, 0xFF };
const u8 uSELECT_WARP_TARGET[] = { 0X1C, 0x0E, 0x15, 0x0E, 0x0C, 0x1D, 0x9E, 0x20, 0x0A, 0x1B, 0x19, 0x9E, 0x1D, 0x0A, 0x1B, 0x10, 0x0E, 0x1D, 0x9E, 0x0A, 0x17, 0x0D, 0x9E, 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x9E, 0x0A, 0xFF };
const u8 uSTATE[] = { 0x1C, 0x1D, 0x0A, 0x1D, 0x0E, 0xFF };
const u8 uSTICK[] = { 0x1C, 0x1D, 0x12, 0x0C, 0x14, 0xFF };
const u8 uSPEED[] = { 0x1C, 0x19, 0x0E, 0x0E, 0x0D, 0xFF };
const u8 uTEXT[] = { 0x1D, 0x0E, 0x21, 0x1D, 0xFF };
const u8 uUP[] = { 0x50, 0xff };
const u8 uWARP[] = { 0x20, 0x0A, 0x1B, 0x19, 0xFF };
const u8 uTIMER[] = { 0x1D, 0x12, 0x16, 0x0E, 0x1B, 0xFF };
const u8 uTIMERSTYLE[] = { 0x1D, 0x12, 0x16, 0x0E, 0x1B, 0x9E, 0x1C, 0x1D, 0x22, 0x15, 0x0E, 0xFF };
const u8 uTIMER100[] = { 0x1D, 0x12, 0x16, 0x0E, 0x1B, 0x9E, 0x01, 0x00, 0x00, 0xFF };
const u8 uXACTION[] = { 0x21, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uXRACTION[] = { 0x21, 0xE4, 0x1B, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uYACTION[] = { 0x22, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uYRACTION[] = { 0x22, 0xE4, 0x1B, 0x9E, 0x0A, 0x0C, 0x1D, 0x12, 0x18, 0x17, 0xFF };
const u8 uWALLKICKFRAME[] = { 0x20, 0x0A, 0x15, 0x15, 0x14, 0x12, 0x0C, 0x14, 0x9E, 0x0F, 0x1B, 0x0A, 0x16, 0x0E, 0xFF };
const u8 uWALLKICK[] = { 0x20, 0x0A, 0x15, 0x15, 0x14, 0x12, 0x0C, 0x14, 0xFF };
const u8 uXCAM[] = { 0x21, 0x0C, 0x0A, 0x16, 0xFF };

//  u8 uTEXT[] = { 0x };