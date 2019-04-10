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
}sprite_t;



typedef struct
{
uint32_t num_sprites;
sprite_t* sprites;
}sprite_collection_t;


extern sprite_collection_t test_sprites;

void render_sprites(sprite_collection_t* sprites,render_context_t* ctx,uint32_t x_clip_min,uint32_t x_clip_max);




#endif
