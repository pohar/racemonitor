#include "r3e-api/sample-c/src/r3e.h"

#define PACKET_VERSION 100

typedef struct
{
    r3e_float32 lap_time_current_self;
    r3e_float32 lap_time_previous_self;
    r3e_float32 time_delta_best_self;
    int myelapsed;
    int myLastLapTime;
    bool isLapValid;
} packet_t;

