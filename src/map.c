#include<stdlib.h>
#include<stdbool.h>
#include "map.h"




map_tile_t test_map_tiles[]={
	{2,0},{2,2},{2,4},{2,6},{2,8},
	{2,10},{2,12},{2,14},{3,16},{2,19},
	{2,21},{1,23},{1,24},{2,25},{1,27},
	{2,28},{1,30},{1,31},{3,32},{1,35},
	{2,36},{1,38},{1,39},{1,40},{1,41}
};

map_sprite_t test_map_sprites[]={
	{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},
	{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{0,1,0,0},{2,4,0,0},{4,6,0,0},{0,1,0,0},{2,4,0,0},
	{0,1,0,0},{2,4,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{4,6,0,0},{0,1,0,0},
	{0,1,0,0},{2,4,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{2,4,0,0},{4,6,0,0},{0,1,0,0},
	{0,1,0,0},{2,4,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}
	};

map_t test_map={5,5,42,test_map_tiles,test_map_sprites};

//x x x x x
//x x x x x
//x   x
//x x x
//x    

map_tile_t map_get_tile(map_t* map,uint32_t x,uint32_t y)
	{
	return map->tiles[x+y*map->width];
	}



uint32_t tile_render(map_t* map,render_context_t* ctx,uint32_t x,uint32_t y,uint32_t start,int32_t z_max)
{
map_tile_t tile=map_get_tile(map,x,y);
	for(uint32_t i=start;i<tile.num_sprites;i++)
	{
	map_sprite_t sprite=map->sprites[tile.sprite_index+i];
		if((sprite.z_max<<16)>z_max)return i;
	render_sprite(ctx,sprite.sprite,(1<<15)+((int32_t)x<<16),(1<<15)+((int32_t)y<<16),(int32_t)sprite.z_min<<16);
	}
return tile.num_sprites;
}


//void map_is_intersecting(map_t* map,)

void map_render(map_t* map,render_context_t* ctx,dynamic_sprite_t* dynamic)
{
//Find tile on which dynamic belongs
int32_t x_min=(dynamic->x+dynamic->x_min)>>16;
int32_t y_min=(dynamic->y+dynamic->y_min)>>16;
//
uint32_t* tile_sprites_rendered=calloc(map->width*map->height,sizeof(uint32_t));

	for(uint32_t xy_sum=0;xy_sum<map->width+map->height;xy_sum++)
	{
	uint32_t start_x,iterations;
		if(xy_sum<map->width)
		{
		iterations=xy_sum+1;
		start_x=0;
		}
		else
		{
		iterations=2*map->width-xy_sum-1;
		start_x=1+xy_sum-map->width;
		}

		bool dynamic_object_found=false;
	
		for(uint32_t i=0;i<iterations;i++)
		{
		uint32_t x=start_x+i;
		uint32_t y=xy_sum-x;
			if(x==x_min&&y==y_min)
			{
			dynamic_object_found=true;	
			tile_sprites_rendered[x+y*map->width]=tile_render(map,ctx,x,y,tile_sprites_rendered[x+y*map->width],dynamic->z+dynamic->z_min);
			}
			else
			{
			tile_sprites_rendered[x+y*map->width]=tile_render(map,ctx,x,y,tile_sprites_rendered[x+y*map->width],INT32_MAX);
			}
		}
		if(dynamic_object_found)
		{
			if(x_min+1<map->width)tile_sprites_rendered[(x_min+1)+y_min*map->width]=tile_render(map,ctx,x_min+1,y_min,tile_sprites_rendered[(x_min+1)+y_min*map->width],dynamic->z+dynamic->z_min);
			if(y_min+1<map->height)tile_sprites_rendered[x_min+(y_min+1)*map->width]=tile_render(map,ctx,x_min,y_min+1,tile_sprites_rendered[x_min+(y_min+1)*map->width],dynamic->z+dynamic->z_min);
			if(x_min+1<map->width&&y_min+1<map->height)tile_sprites_rendered[(x_min+1)+(y_min+1)*map->width]=tile_render(map,ctx,x_min+1,y_min+1,tile_sprites_rendered[(x_min+1)+(y_min+1)*map->width],dynamic->z+dynamic->z_min);
			render_sprite(ctx,dynamic->sprite,dynamic->x,dynamic->y,dynamic->z);
			tile_sprites_rendered[x_min+y_min*map->width]=tile_render(map,ctx,x_min,y_min,tile_sprites_rendered[x_min+y_min*map->width],INT32_MAX);
		}
	}
free(tile_sprites_rendered);
}
