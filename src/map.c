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
	{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},
	{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{0,1,0,0},{1,2,0,0},{2,3,0,0},{0,1,0,0},{1,2,0,0},
	{0,1,0,0},{1,2,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{2,3,0,0},{0,1,0,0},
	{0,1,0,0},{1,2,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{1,2,0,0},{2,3,0,0},{0,1,0,0},
	{0,1,0,0},{1,2,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}
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

//         x
//       x   x
//     x   x   x
//   x   x   x   x
// x   x   x   x   x
//   x   x   x   x
//     x   x   x
//       x   x
//         x

void map_get_tile_sprites(map_t* map, sprite_collection_t* sprites,uint32_t x,uint32_t y,uint32_t col)
{
map_tile_t tile=map_get_tile(map,x,y);
	for(uint32_t i=0;i<tile.num_sprites;i++)
	{
	map_sprite_t map_sprite=map->sprites[tile.sprite_index+i];
	sprite_t sprite={{-1<<15,1<<15,-1<<15,1<<15,0,2<<16},(1<<15)+((int32_t)x<<16),(1<<15)+((int32_t)y<<16),(int32_t)map_sprite.z_min<<16,map_sprite.sprite,0};
	sprites->sprites[sprites->num_sprites]=sprite;
	sprites->num_sprites++;
	}
}

void map_get_column_sprites(map_t* map,sprite_collection_t* sprites,int32_t col)
{
uint32_t x,y;
	if(col-8>=0)
	{
	x=0;
	y=col-8;
		while(x<map->width&&y<map->height)
		{
		map_get_tile_sprites(map,sprites,x,y,col);
			if(y+1<map->height)map_get_tile_sprites(map,sprites,x,y+1,col);
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
		map_get_tile_sprites(map,sprites,x,y,col);
			if(x+1<map->width)map_get_tile_sprites(map,sprites,x+1,y,col);
		x++;
		y++;
		}
	}
}

void map_render(map_t* map,render_context_t* ctx,sprite_collection_t* sprites)
{
sprite_t sprite_data[256];
	for(uint32_t col=0;col<20;col++)
	{
	sprite_collection_t column_sprites={0,sprite_data};	
	map_get_column_sprites(map,&column_sprites,col);
	//Add dynamic sprites
	memcpy(column_sprites.sprites+column_sprites.num_sprites,sprites->sprites,sprites->num_sprites*sizeof(sprite_t));
	column_sprites.num_sprites+=sprites->num_sprites;
	//Render column
	render_sprites(&column_sprites,ctx,col*32,(col+1)*32);
	}
}
