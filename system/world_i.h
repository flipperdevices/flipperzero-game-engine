#pragma once
#include "world.h"

#ifdef __cplusplus
extern "C" {
#endif

void world_step(
    World* world,
    RunningGameEngine* engine,
    const InputState* input_state,
    Canvas* canvas);

#ifdef __cplusplus
}
#endif