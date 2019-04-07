#include "render.h"

void render_sprite(render_context_t* ctx,uint16_t sprite_index,int32_t x,int32_t y,int32_t z,int32_t x_clip_min,int32_t x_clip_max)
{
int32_t screen_x=((y-x)>>11)+256+ctx->x_offset[sprite_index];
int32_t screen_y=((x+y-z)>>12)+128+ctx->y_offset[sprite_index];

int32_t source_x_clip_min=x_clip_min-screen_x;
int32_t source_x_clip_max=x_clip_max-screen_x;

SDL_Surface* sprite=ctx->sprites[sprite_index];
SDL_Rect src_rect={source_x_clip_min<0?0:source_x_clip_min,0,source_x_clip_max>sprite->w?sprite->w:source_x_clip_max-source_x_clip_min,sprite->h};
SDL_Rect dst_rect={screen_x+source_x_clip_min,screen_y,0,0};
SDL_BlitSurface(sprite,&src_rect,ctx->display,&dst_rect);
}
