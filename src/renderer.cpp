#include "renderer.hpp"

Renderer::Renderer (SDL_Window* win, int winW, int winH)
	:	SDLRen_ 	(SDL_CreateRenderer	(win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | 
												  SDL_RENDERER_TARGETTEXTURE)),	
		SDLBuffer_ 	(SDL_CreateTexture (	SDLRen_, 
											SDL_PIXELFORMAT_RGBA32,
											SDL_TEXTUREACCESS_TARGET,
											winW, winH)),
		texBuffer_ 	(winW, winH, E_PixelFormat::RGBA),
		zBuffer_	(static_cast<unsigned int*>(malloc(winW * winH * sizeof(unsigned int))))
{
	//init zBuffer wither min value
	for (int i = 0; i < winW * winH; i++)
	{
		zBuffer_[i] = 0; //uint limit
	}	
}

Renderer::~Renderer ()
{
	if (zBuffer_ != nullptr)
		free(zBuffer_);

	SDL_DestroyTexture	(SDLBuffer_);
	SDL_DestroyRenderer (SDLRen_);
}

void		Renderer::swapBuffer		() noexcept
{
	//swap pixel form texBuffer to SDLBuffer to displayu this last
	SDL_UpdateTexture (SDLBuffer_, NULL, texBuffer_[0] , sizeof(ColorRGBA) * (texBuffer_.width()));
	SDL_RenderCopy(SDLRen_, SDLBuffer_, NULL, NULL);
	SDL_RenderPresent(SDLRen_);	
}

void		Renderer::clear		() noexcept
{
	//clear current buffer
	texBuffer_.clear();	

	//clear Z buffer
	size_t zBufferSize = texBuffer_.width() * texBuffer_.heigth();

	for (size_t i = 0; i < zBufferSize; i++)
	{
		zBuffer_[i] = 0; //uint limit
	}
}

void Renderer::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c, unsigned int z)
{
	//TODO: Add opacity function in function of depth
	if (x < texBuffer_.width() && y < texBuffer_.heigth())
	{
		if (c.a != 255)
		{
			ColorRGBA cb = texBuffer_.getRGBAPixelColor(x, y);
			texBuffer_.setPixelColor(x, y, alphaBlending(c, cb));
		}
		else if (z > zBuffer_[texBuffer_.width() * y + x])
		{
			texBuffer_.	setPixelColor(x, y, c);
			zBuffer_	[texBuffer_.width() * y + x] = z;
		}
	}
}

ColorRGBA Renderer::alphaBlending(const ColorRGBA& Ca, ColorRGBA& Cb)
{
	Cb.a = 1;
	float finalAlpha = Ca.a + Cb.a * (255 - Ca.a);

	return (ColorRGBA) {static_cast<ubyte>((Ca.r * Ca.a + Cb.r * Cb.a * (255 - Ca.a)) / finalAlpha),
						static_cast<ubyte>((Ca.g * Ca.a + Cb.g * Cb.a * (255 - Ca.a)) / finalAlpha),
						static_cast<ubyte>((Ca.b * Ca.a + Cb.b * Cb.a * (255 - Ca.a)) / finalAlpha),
						static_cast<ubyte>(finalAlpha)};
}

ColorRGB Renderer::alphaBlending(const ColorRGBA& Ca, ColorRGB& Cb)
{
	float finalAlpha = Ca.a + (255 - Ca.a);

	return (ColorRGB) {	static_cast<ubyte>(((Ca.r * Ca.a) + Cb.r * (255 - Ca.a)) / finalAlpha),
						static_cast<ubyte>(((Ca.g * Ca.a) + Cb.g * (255 - Ca.a)) / finalAlpha),
						static_cast<ubyte>(((Ca.b * Ca.a) + Cb.b * (255 - Ca.a)) / finalAlpha)};	
}