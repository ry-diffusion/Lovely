#include <Lovely.h>
#include <minwindef.h>

HHOOK g_Hook = NULL;
State g_State = {FALSE, 1, {}};

ULONGLONG GetTime(void) {
  FILETIME ft;

  ULONGLONG milliseconds;

  GetSystemTimePreciseAsFileTime(&ft);

  milliseconds = ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
  milliseconds /= 10000; // Convert 100-nanosecond intervals to milliseconds

  return milliseconds;
}