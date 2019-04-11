#ifndef DYNAMIC_INCLUDED
#define DYNAMIC_INCLUDED
#include "render.h"

#define MAX_SPRITES_PER_SORT 256

typedef struct
{
int32_t x_min,x_max,y_min,y_max,z_min,z_max;
}bounding_box_t;

typedef struct
{
bounding_box_t bounds;
int32_t x,y,z;
uint16_t sprite;
uint16_t visited;
}sprite_t;



typedef struct
{
uint32_t num_sprites;
sprite_t* sprites;
}sprite_collection_t;


void sort_sprites(sprite_t* src,sprite_t* dst,uint32_t num_sprites);




#endif
