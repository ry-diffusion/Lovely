#pragma once
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct State {
  BOOL dynamicShouldIgnore;
  WORD dynamicTimeoutMs;
  ULONGLONG lastClickTime;
} State;

extern State g_State;
extern HHOOK g_Hook;

ULONGLONG GetTime(void);