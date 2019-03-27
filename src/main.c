#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

void render_sprite(SDL_Surface* src,SDL_Surface* dst,uint32_t x,uint32_t y,uint32_t z)
{
SDL_Rect src_rect={0,0,src->w,src->h};
SDL_Rect dst_rect={(y-x)*16,-(x+y+z)*8,src->w,src->h};
SDL_BlitSurface(src,&src_rect,dst,&dst_rect);
}



int main(int argc,char* args[])
{
	//Initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
		printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
		exit(1);
		}
	SDL_Window* window=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(window==NULL)
		{
		printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
		exit(1);	
		}
	SDL_Surface* display=SDL_GetWindowSurface(window);
	SDL_Surface* test=SDL_LoadBMP("test.bmp");

	int running=true;
		while(running)
		{
		SDL_Event event;
			while(SDL_PollEvent(&event)!=0)
			{
				if(event.type==SDL_QUIT)running=false;
			}
		
		render_sprite(test,display,-10,1,0);	
		render_sprite(test,display,-10,1,1);	
		render_sprite(test,display,-11,1,0);	
		render_sprite(test,display,-10,0,0);	
		render_sprite(test,display,-11,0,0);	
		SDL_UpdateWindowSurface(window);
		}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
