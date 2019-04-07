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


//void map_is_intersecting(map_t* map,)


uint32_t min(uint32_t a,uint32_t b)
	{
	return a<b?a:b;
	}

int32_t floor_fix(int32_t x)
	{
	return x>>16;
	} 

int32_t ceil_fix(int32_t x)
	{
	return (x>>16)+((x&0xFFFF)?1:0);
	}

//         x
//       x   x
//     x   x   x
//   x   x   x   x
// x   x   x   x   x
//   x   x   x   x
//     x   x   x
//       x   x
//         x

void map_render_tile(map_t* map, render_context_t* ctx,uint32_t x,uint32_t y,uint32_t col)
{
map_tile_t tile=map_get_tile(map,x,y);
	for(uint32_t i=0;i<tile.num_sprites;i++)
	{
	map_sprite_t sprite=map->sprites[tile.sprite_index+i];
	render_sprite(ctx,sprite.sprite,(1<<15)+((int32_t)x<<16),(1<<15)+((int32_t)y<<16),(int32_t)sprite.z_min<<16,col*32,(col+1)*32);
	}
}

void map_render_column(map_t* map,render_context_t* ctx,int32_t col)
{
uint32_t x,y;
	if(col-8>=0)
	{
	x=0;
	y=col-8;
		while(x<map->width&&y<map->height)
		{
		map_render_tile(map,ctx,x,y,col);
			if(y+1<map->height)map_render_tile(map,ctx,x,y+1,col);
		x++;
		y++;
		}
	}
	else
	{
	x=-(col-8)-1;
	y=0;
		while(x<map->width&&y<map->height)
		{
		map_render_tile(map,ctx,x,y,col);
			if(x+1<map->width)map_render_tile(map,ctx,x+1,y,col);
		x++;
		y++;
		}
	}
}

void map_render(map_t* map,render_context_t* ctx,dynamic_sprite_collection_t* dynamic)
{
	for(uint32_t col=0;col<20;col++)
	{
	map_render_column(map,ctx,col);
	}
}
