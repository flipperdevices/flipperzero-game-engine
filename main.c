#include <furi.h>
#include "fgeo/game_engine.h"
#include "system/world.h"
#include "system/world_i.h"

void game_word_settings(GameWorldSettings* settings);
World* game_world_init(void);

static void frame_cb(RunningGameEngine* engine, Canvas* canvas, InputState input, void* context) {
    World* world = context;
    world_step(world, engine, &input, canvas);
}

int32_t game_engine_app(void* p) {
    UNUSED(p);

    GameWorldSettings user_settings;
    memset(&user_settings, 0, sizeof(user_settings));
    game_word_settings(&user_settings);

    World* world = game_world_init();

    GameEngineSettings settings = game_engine_settings_init();
    settings.fps = user_settings.fps;
    settings.show_fps = user_settings.show_fps;
    settings.always_backlight = user_settings.always_backlight;
    settings.frame_callback = frame_cb;
    settings.context = world;

    GameEngine* engine = game_engine_alloc(settings);

    game_engine_run(engine);

    game_engine_free(engine);

    return 0;
}