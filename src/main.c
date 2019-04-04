#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<SDL.h>

#include "render.h"
#include "dynamic.h"

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
			if(keys[SDL_SCANCODE_LEFT])test_sprites.sprites[0].x+=128;
			if(keys[SDL_SCANCODE_RIGHT])test_sprites.sprites[0].x-=128;
			if(keys[SDL_SCANCODE_UP])test_sprites.sprites[0].y-=128;
			if(keys[SDL_SCANCODE_DOWN])test_sprites.sprites[0].y+=128;
			if(keys[SDL_SCANCODE_W])test_sprites.sprites[0].z+=128;
			if(keys[SDL_SCANCODE_S])test_sprites.sprites[0].z-=128;
		SDL_Rect screen={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
		SDL_FillRect(ctx.display,&screen,0);
		dynamic_render(&test_sprites,&ctx);
		SDL_UpdateWindowSurface(window);
		}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
