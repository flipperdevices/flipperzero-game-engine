#include <furi.h>
#include "fgeo/system/world.h"

typedef struct {
    float x;
    float y;
    float speed;
} Movement2D;

void* movement2d_alloc() {
    Movement2D* movement = malloc(sizeof(Movement2D));
    movement->x = 0.0f;
    movement->y = 0.0f;
    movement->speed = 0.0f;
    return movement;
}

void movement2d_free(void* movement) {
    free(movement);
}

void movement2d_system(World* world, void* context) {
    ComponentPrefab* prefab_movement2d = context;
    ComponentIterator* iterator = world_get_component_iterator(world, prefab_movement2d);
    InputState input = world_get_input_state(world);
    float delta_time = world_get_delta_time(world);

    while(component_iterator_next(iterator)) {
        Movement2D* movement = component_iterator_get_component_data(iterator);

        if(input.held & GameKeyLeft) {
            movement->x -= movement->speed * delta_time;
        }

        if(input.held & GameKeyRight) {
            movement->x += movement->speed * delta_time;
        }

        if(input.held & GameKeyUp) {
            movement->y -= movement->speed * delta_time;
        }

        if(input.held & GameKeyDown) {
            movement->y += movement->speed * delta_time;
        }
    }
}

void game_word_settings(GameWorldSettings* settings) {
    settings->fps = 60.0f;
    settings->show_fps = true;
    settings->always_backlight = true;
}

World* game_world_init(void) {
    World* world = world_alloc();

    ComponentPrefab* prefab_movement2d =
        world_create_component_prefab(world, movement2d_alloc, movement2d_free);
    world_create_system(world, movement2d_system, prefab_movement2d);

    Entity* player = world_add_entity(world);
    Movement2D* movement = entity_add_component_and_get_data(player, prefab_movement2d);
    movement->x = 64.0f;
    movement->y = 32.0f;
    movement->speed = 60.0f;

    return world;
}