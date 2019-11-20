#include "renderer.hpp"

Renderer::Renderer (SDL_Window* win, int winW, int winH)
	:	SDLRen_ 	(SDL_CreateRenderer	(win, -1, 	SDL_RENDERER_PRESENTVSYNC | 													SDL_RENDERER_ACCELERATED | 
													SDL_RENDERER_TARGETTEXTURE)),	
		SDLBuffer_ 	(SDL_CreateTexture (	SDLRen_, 
											SDL_PIXELFORMAT_RGBA8888,
											SDL_TEXTUREACCESS_TARGET,
											winW, 												winH)),
		texBuffer_ 	(winW, winH)
{}

Renderer::~Renderer ()
{
	SDL_DestroyTexture	(SDLBuffer_);
	SDL_DestroyRenderer (SDLRen_);
}

void		Renderer::swapBuffer		() noexcept
{
	//swap pixel form texBuffer to SDLBuffer to displayu this last
	SDL_UpdateTexture (SDLBuffer_, NULL, texBuffer_[0] ,4 * texBuffer_.width());
	SDL_RenderCopy(SDLRen_, SDLBuffer_, NULL, NULL);
	SDL_RenderPresent(SDLRen_);	
}

void		Renderer::clear		() noexcept
{
	SDL_SetRenderTarget		(SDLRen_, SDLBuffer_);
    SDL_SetRenderDrawColor	(SDLRen_, 0, 0, 0, 0);
	SDL_RenderClear			(SDLRen_);
	SDL_SetRenderTarget		(SDLRen_, NULL);
}
