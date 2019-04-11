#include <stdbool.h>
#include "sprite.h"




bounding_box_t sprite_get_bounding_box(sprite_t* sprite)
{
bounding_box_t box={sprite->bounds.x_min+sprite->x,sprite->bounds.x_max+sprite->x,sprite->bounds.y_min+sprite->y,sprite->bounds.y_max+sprite->y,sprite->bounds.z_min+sprite->z,sprite->bounds.z_max+sprite->z};
return box;
}


bool interval_overlap(int32_t A_min,int32_t A_max,int32_t B_min,int32_t B_max)
{
	return A_min<B_max&&A_max>B_min;
}

bool is_behind(sprite_t* sprite1,sprite_t* sprite2)
{
bounding_box_t A=sprite_get_bounding_box(sprite1);
bounding_box_t B=sprite_get_bounding_box(sprite2);

	if(interval_overlap(A.x_min-A.y_max,A.x_max-A.y_min,B.x_min-B.y_max,B.x_max-B.y_min)&&
	   interval_overlap(A.x_min-A.z_max,A.x_max-A.z_min,B.x_min-B.z_max,B.x_max-B.z_min)&&
	   interval_overlap(A.z_min-A.y_max,A.z_max-A.y_min,B.z_min-B.y_max,B.z_max-B.y_min))
	{
		if(A.x_max<=B.x_min)return true;
		if(A.y_max<=B.y_min)return true;
		if(A.z_max<=B.z_min)return true;
	}
return false;
}


uint32_t add_sprite_with_dependencies(sprite_t* src,sprite_t* dst,uint32_t num_sprites,uint32_t sprites_added,uint32_t i)
{
src[i].visited=1;
//Add all sprites that should be drawn before this one
	for(uint32_t j=0;j<num_sprites;j++)
	{
		if(is_behind(src+j,src+i)&&src[j].visited==0)
		{
		sprites_added=add_sprite_with_dependencies(src,dst,num_sprites,sprites_added,j);
		}
	}
//Add sprite to output
dst[sprites_added]=src[i];
return sprites_added+1;
}

void sort_sprites(sprite_t* src,sprite_t* dst,uint32_t num_sprites)
{
//Mark all sprites unvisited
	for(uint32_t i=0;i<num_sprites;i++)src[i].visited=0;
//Sort sprites
uint32_t sprites_added=0;
	for(uint32_t i=0;i<num_sprites;i++)
	{
		if(src[i].visited==0)
		{
		sprites_added=add_sprite_with_dependencies(src,dst,num_sprites,sprites_added,i);
		}
	}
}
