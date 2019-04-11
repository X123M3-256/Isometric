#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include<stdint.h>
#include "sprite.h"

typedef struct
{
uint16_t z_min,z_max;
uint16_t sprite;//ID of the sprite
uint16_t object;//ID of the object that this sprite forms part of
}map_element_t;

typedef struct
{
uint32_t num_elements;
uint32_t element_index;
}map_tile_t;

typedef struct
{
uint16_t width,height;
uint32_t num_sprites;
map_tile_t* tiles;
map_element_t* elements;
sprite_t* sprites;
}map_t;

extern map_t test_map;

map_tile_t map_get_tile(map_t* map,uint32_t x,uint32_t y);

#endif
