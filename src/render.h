#ifndef RENDER_INCLUDED
#define RENDER_INCLUDED
#include<SDL.h>

typedef struct
	{
	SDL_Surface* display;
	uint32_t* x_offset;
	uint32_t* y_offset;
	SDL_Surface** sprites;
	}render_context_t;


void render_sprite(render_context_t* ctx,uint16_t sprite,int32_t x,int32_t y,int32_t z);

#endif
