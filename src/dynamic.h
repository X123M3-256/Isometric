#ifndef DYNAMIC_INCLUDED
#define DYNAMIC_INCLUDED
#include "render.h"

typedef struct
{
int32_t x_min,x_max,y_min,y_max,z_min,z_max;
}bounding_box_t;

typedef struct
{
bounding_box_t bounds;
int32_t x,y,z;
uint16_t sprite;
uint16_t invalid;
}dynamic_sprite_t;



typedef struct
{
uint32_t num_sprites;
dynamic_sprite_t* sprites;
}dynamic_sprite_collection_t;


extern dynamic_sprite_collection_t test_sprites;

void dynamic_render(dynamic_sprite_collection_t* sprites,render_context_t* ctx);




#endif
