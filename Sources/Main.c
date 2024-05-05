#include <Lovely.h>
#include <handleapi.h>
#include <minwindef.h>
#include <processthreadsapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <winuser.h>
ULONG FROM_CLICKER = 0xb00b;

typedef enum MouseKind { MK_LEFT = 0xf, MK_RIGHT = 0xd } MOUSEKIND;

DWORD MouseClickTask(LPVOID lpParam) {
  if (NULL == lpParam) {
    printf("MouseClickTask: NULL Pointer!\n");
    return 0;
  }

  MOUSEKIND mouseKind = *(MOUSEKIND *)lpParam;

  INPUT input;
  DWORD keyDown =
      MK_LEFT == mouseKind ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
  DWORD keyUp = MK_LEFT == mouseKind ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
  input.type = INPUT_MOUSE;
  input.mi.dwExtraInfo = FROM_CLICKER;

  Sleep(50);
  input.mi.dwFlags = keyDown;
  SendInput(1, &input, sizeof(INPUT));

  Sleep(2);
  input.mi.dwFlags = keyUp;

  SendInput(1, &input, sizeof(INPUT));

  free(lpParam);
  return 0;
}

void Click(MOUSEKIND mouseKind) {
  HANDLE hThread;
  DWORD dwThreadId;

  MOUSEKIND *pMouseKind = (MOUSEKIND *)malloc(sizeof(MOUSEKIND));
  *pMouseKind = mouseKind;

  hThread = CreateThread(NULL, 0, MouseClickTask, pMouseKind, 0, &dwThreadId);

  if (hThread == NULL) {
    fprintf(stderr, "Failed to create thread!\n");
    return;
  }

  CloseHandle(hThread);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
  MSLLHOOKSTRUCT *pMouseStruct;

  if (!(nCode >= 0 && (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN))) {
    goto bye;
  }

  pMouseStruct = (MSLLHOOKSTRUCT *)lParam;

  if (pMouseStruct->dwExtraInfo == FROM_CLICKER)
    goto bye;

  g_State.dynamicShouldIgnore =
      (GetTime() - g_State.lastClickTime) > g_State.dynamicTimeoutMs;

  g_State.lastClickTime = GetTime();

  fprintf(stderr, "should ignore? %d\n", g_State.dynamicShouldIgnore);

  if (!g_State.dynamicShouldIgnore) {
    for (int i = 0; i < 2; ++i)
      Click(WM_LBUTTONDOWN == wParam ? MK_LEFT : MK_RIGHT);
    goto bye;
  }

bye:
  return CallNextHookEx(g_Hook, nCode, wParam, lParam);
}

int main() {
  // 1 Second
  g_State.dynamicTimeoutMs = 100;

  g_Hook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

  if (g_Hook == NULL) {
    fprintf(stderr, "Failed to install hook!\n");
    return 1;
  }

  // Message loop
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // Unhook
  UnhookWindowsHookEx(g_Hook);

  return 0;
}
