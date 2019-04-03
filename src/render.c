#include "render.h"

void render_sprite(render_context_t* ctx,uint16_t sprite_index,int32_t x,int32_t y,int32_t z)
{
SDL_Surface* sprite=ctx->sprites[sprite_index];
SDL_Rect src_rect={0,0,sprite->w,sprite->h};
SDL_Rect dst_rect={((y-x)>>11)+256+ctx->x_offset[sprite_index],((x+y-z)>>12)+128+ctx->y_offset[sprite_index],sprite->w,sprite->h};
SDL_BlitSurface(sprite,&src_rect,ctx->display,&dst_rect);
}
