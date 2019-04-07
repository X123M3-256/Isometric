#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include<stdint.h>
#include "render.h"
#include "dynamic.h"

typedef struct
{
uint16_t z_min,z_max;
uint16_t sprite;//ID of the sprite
uint16_t object;//ID of the object that this sprite forms part of
}map_sprite_t;

typedef struct
{
uint32_t num_sprites;
uint32_t sprite_index;
}map_tile_t;

typedef struct
{
uint16_t width,height;
uint32_t num_objects;
map_tile_t* tiles;
map_sprite_t* sprites;
}map_t;

extern map_t test_map;

void map_render(map_t* map,render_context_t* ctx,dynamic_sprite_collection_t* dynamic);
#endif
