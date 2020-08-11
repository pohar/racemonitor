#ifndef __UTIL_H__
#define __UTIL_H__

#include <Windows.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define RPS_TO_RPM (60 / (2 * M_PI))
#define MPS_TO_KPH 3.6f

#ifdef __cplusplus
extern "C" {
#endif
BOOL is_process_running(const TCHAR* name);
BOOL is_r3e_running();
#ifdef __cplusplus
}
#endif
#endif // __UTIL_H__
