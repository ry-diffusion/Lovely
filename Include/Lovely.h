#pragma once
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct State {
  WORD dynamicTimeoutMs;
  ULONGLONG lastClickTime;
} State;

extern LONG FROM_CLICKER;
typedef enum MouseKind { MK_LEFT = 0xf, MK_RIGHT = 0xd } MOUSEKIND;

extern State g_State;
extern HHOOK g_Hook;

ULONGLONG GetTime(void);