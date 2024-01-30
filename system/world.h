#pragma once
#include "../game_engine.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct World World;

typedef struct Entity Entity;

typedef struct ComponentPrefab ComponentPrefab;

typedef struct Component Component;

typedef struct System System;

World* world_alloc(void);

void world_free(World* world);

Entity* world_add_entity(World* world);

typedef void* (*ComponentAlloc)(void);
typedef void (*ComponentFree)(void* data);
ComponentPrefab* world_create_component_prefab(World* world, ComponentAlloc, ComponentFree);

typedef void (*SystemUpdate)(World* world, void* context);

System* world_create_system(World* world, SystemUpdate update, void* context);

InputState world_get_input_state(World* world);

Canvas* world_get_canvas(World* world);

float world_get_delta_time(World* world);

typedef struct ComponentIterator ComponentIterator;

ComponentIterator* world_get_component_iterator(World* world, ComponentPrefab* prefab);

bool component_iterator_next(ComponentIterator* iterator);

void* component_iterator_get_component_data(ComponentIterator* iterator);

void* entity_add_component_and_get_data(Entity* entity, ComponentPrefab* component);

void* component_get_data(Component* component);

typedef struct {
    float fps;
    bool show_fps;
    bool always_backlight;
} GameWorldSettings;

#ifdef __cplusplus
}
#endif