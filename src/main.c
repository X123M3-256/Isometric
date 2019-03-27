#include<stdio.h>
#include<stdbool.h>
#include<SDL.h>

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
	SDL_Window* window=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(window==NULL)
		{
		printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
		exit(1);	
		}
	SDL_Surface* screenSurface=SDL_GetWindowSurface(window);
	
	int running=true;
		while(running)
		{
		SDL_Event event;
			while(SDL_PollEvent(&event)!=0)
			{
				if(event.type==SDL_QUIT)running=false;
			}
		SDL_Surface* sdl_surf=SDL_GetWindowSurface(window);
		SDL_UpdateWindowSurface(window);
		}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
