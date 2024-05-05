#include <Lovely.h>

HHOOK g_Hook = NULL;
State g_State = {FALSE, {}};
LONG FROM_CLICKER = 0xb00b;

ULONGLONG GetTime(void) {
  FILETIME ft;

  ULONGLONG milliseconds;

  GetSystemTimePreciseAsFileTime(&ft);

  milliseconds = ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
  milliseconds /= 10000; // Convert 100-nanosecond intervals to milliseconds

  return milliseconds;
}