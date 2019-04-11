#include "render.h"

void render_sprite(render_context_t* ctx,uint16_t sprite_index,int32_t x,int32_t y,int32_t x_clip_min,int32_t x_clip_max,int32_t y_clip_min,int32_t y_clip_max)
{
int32_t screen_x=x+ctx->x_offset[sprite_index];
int32_t screen_y=y+ctx->y_offset[sprite_index];



int32_t source_x_clip_min=x_clip_min-screen_x;
int32_t source_x_clip_max=x_clip_max-screen_x;
int32_t source_y_clip_min=y_clip_min-screen_y;
int32_t source_y_clip_max=y_clip_max-screen_y;
	if(source_x_clip_min<0)source_x_clip_min=0;
	if(source_x_clip_max>ctx->display->w)source_x_clip_max=ctx->display->w;
	if(source_y_clip_min<0)source_y_clip_min=0;
	if(source_y_clip_max>ctx->display->h)source_y_clip_max=ctx->display->h;

SDL_Surface* sprite=ctx->sprites[sprite_index];
SDL_Rect src_rect={source_x_clip_min,source_y_clip_min,source_x_clip_max-source_x_clip_min,source_y_clip_max-source_y_clip_min};
SDL_Rect dst_rect={screen_x+source_x_clip_min,screen_y+source_y_clip_min,0,0};
SDL_BlitSurface(sprite,&src_rect,ctx->display,&dst_rect);
}
