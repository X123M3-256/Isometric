#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<SDL.h>

#include "render.h"
#include "map.h"

//Screen dimension constants
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;




int main(int argc,char* args[])
{
	//Initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
		printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
		exit(1);
		}
	SDL_Window* window=SDL_CreateWindow("Isometric test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(window==NULL)
		{
		printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
		exit(1);	
		}

	render_context_t ctx;
	ctx.display=SDL_GetWindowSurface(window);
	ctx.sprites=malloc(2*sizeof(SDL_Surface*));
	ctx.sprites[0]=SDL_LoadBMP("test.bmp");
	ctx.sprites[1]=SDL_LoadBMP("test2.bmp");
	ctx.x_offset=malloc(2*sizeof(uint32_t));
	ctx.y_offset=malloc(2*sizeof(uint32_t));
	ctx.x_offset[0]=-32;
	ctx.y_offset[0]=-47;
	ctx.x_offset[1]=-16;
	ctx.y_offset[1]=-23;
	int running=true;

	dynamic_sprite_t box;
	box.x_min=-(1<<14);
	box.x_max=1<<14;
	box.y_min=-(1<<14);
	box.y_max=1<<14;
	box.z_min=0;
	box.z_max=1<<15;
	box.x=(4<<16)+(1<<15);
	box.y=(4<<16)+(1<<15);
	box.z=2<<16;
	box.sprite=1;

		while(running)
		{
		SDL_Event event;
			while(SDL_PollEvent(&event)!=0)
			{
				switch(event.type)
				{
					case SDL_QUIT:
					running=false;
					break;
				}
			}
		const Uint8* keys=SDL_GetKeyboardState(NULL);
			if(keys[SDL_SCANCODE_LEFT])box.x+=128;
			if(keys[SDL_SCANCODE_RIGHT])box.x-=128;
			if(keys[SDL_SCANCODE_UP])box.y-=128;
			if(keys[SDL_SCANCODE_DOWN])box.y+=128;
			if(keys[SDL_SCANCODE_W])box.z+=128;
			if(keys[SDL_SCANCODE_S])box.z-=128;
		map_render(&test_map,&ctx,&box);
		SDL_UpdateWindowSurface(window);
		}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
