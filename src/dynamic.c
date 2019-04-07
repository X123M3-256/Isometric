#include <stdbool.h>
#include "dynamic.h"




bounding_box_t dynamic_sprite_get_bounding_box(dynamic_sprite_t* sprite)
{
bounding_box_t box={sprite->bounds.x_min+sprite->x,sprite->bounds.x_max+sprite->x,sprite->bounds.y_min+sprite->y,sprite->bounds.y_max+sprite->y,sprite->bounds.z_min+sprite->z,sprite->bounds.z_max+sprite->z};
return box;
}


bool interval_overlap(int32_t A_min,int32_t A_max,int32_t B_min,int32_t B_max)
{
	return A_min<B_max&&A_max>=B_min;
}

bool is_behind(dynamic_sprite_t* sprite1,dynamic_sprite_t* sprite2)
{
bounding_box_t A=dynamic_sprite_get_bounding_box(sprite1);
bounding_box_t B=dynamic_sprite_get_bounding_box(sprite2);

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

dynamic_sprite_t sprites[5]=
	{
	{-(1<<14),1<<14,-(1<<14),1<<14,0,1<<15,(3<<16),(4<<16)+(1<<15),2<<16,1},
	{-(1<<14),1<<14,-(1<<14),1<<14,0,1<<15,(3<<16)+(1<<15),(4<<16)+(1<<15),2<<16,1},
	{-(1<<14),1<<14,-(1<<14),1<<14,0,1<<15,(4<<16)+(1<<15),(3<<16)+(1<<15),2<<16,1},
	{-(1<<14),1<<14,-(1<<14),1<<14,0,1<<15,(4<<16)+(1<<14),(3<<16)+(1<<14),(3<<16),1},
	{-(1<<14),1<<14,-(1<<14),1<<14,0,1<<15,(4<<16)+(3<<14),(3<<16),(4<<15),1}
	};
dynamic_sprite_collection_t test_sprites={5,sprites};

void render_dynamic_sprite(dynamic_sprite_collection_t* sprites,render_context_t* ctx,uint32_t i)
{
sprites->sprites[i].invalid=0;
//Render all sprites that are behind this one and have not been rendered
	for(uint32_t j=0;j<sprites->num_sprites;j++)
	{
		if(is_behind(sprites->sprites+j,sprites->sprites+i)&&sprites->sprites[j].invalid==1)
		{
		render_dynamic_sprite(sprites,ctx,j);
		}
	}
//Render the sprite
render_sprite(ctx,sprites->sprites[i].sprite,sprites->sprites[i].x,sprites->sprites[i].y,sprites->sprites[i].z,INT32_MIN,INT32_MAX);
}

void dynamic_render(dynamic_sprite_collection_t* sprites,render_context_t* ctx)
{
//Invalidate all sprites
	for(uint32_t i=0;i<sprites->num_sprites;i++)sprites->sprites[i].invalid=1;
//Render all sprites
	for(uint32_t i=0;i<sprites->num_sprites;i++)
	{
		if(sprites->sprites[i].invalid==1)
		{
		render_dynamic_sprite(sprites,ctx,i);
		}
	}
}
