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
		zBuffer_[i] = 0; //TODO: memset to optimize
	}
}

ColorRGBA alphaBlendingADD(const ColorRGBA& Ca, const ColorRGBA& Cd) //Ca Over Cb
{
	float Car(Ca.r / 255.f) , Cag(Ca.g / 255.f), Cab(Ca.b / 255.f), Caa(Ca.a / 255.f);
	float Cdr(Cd.r / 255.f) , Cdg(Cd.g / 255.f), Cdb(Cd.b / 255.f), Cda(Cd.a / 255.f);

	float finalAlpha = Caa + Cda * (1.f - Caa);

	float r =  (Car * Caa) + Cdr;
	float g =  (Cag * Caa) + Cdg;
	float b =  (Cab * Caa) + Cdb;

	return (ColorRGBA) {static_cast<ubyte>(r * 255.f),
						static_cast<ubyte>(g * 255.f),
						static_cast<ubyte>(b * 255.f),
						static_cast<ubyte>(finalAlpha * 255.f)};
}


ColorRGBA alphaBlending(const ColorRGBA& Ca, const ColorRGBA& Cb) //Ca Over Cb
{
	float Car(Ca.r / 255.f) , Cag(Ca.g / 255.f), Cab(Ca.b / 255.f), Caa(Ca.a / 255.f);
	float Cbr(Cb.r / 255.f) , Cbg(Cb.g / 255.f), Cbb(Cb.b / 255.f), Cba(Cb.a / 255.f);

	float finalAlpha = Caa + Cba * (1.f - Caa);

	float r =  (Car * Caa + Cbr * Cba * (1.f - Caa)) / finalAlpha;
	float g =  (Cag * Caa + Cbg * Cba * (1.f - Caa)) / finalAlpha;
	float b =  (Cab * Caa + Cbb * Cba * (1.f - Caa)) / finalAlpha;

	return (ColorRGBA) {static_cast<ubyte>(r * 255.f),
						static_cast<ubyte>(g * 255.f),
						static_cast<ubyte>(b * 255.f),
						static_cast<ubyte>(finalAlpha * 255.f)};
}

/*
ColorRGBA alphaBlending(const ColorRGBA& Ca, const ColorRGBA& Cb) //Ca Over Cb
{
	float Car(Ca.r / 255.f) , Cag(Ca.g / 255.f), Cab(Ca.b / 255.f), Caa(Ca.a / 255.f);
	float Cbr(Cb.r / 255.f) , Cbg(Cb.g / 255.f), Cbb(Cb.b / 255.f), Cba(Cb.a / 255.f);

	float r = (Car * Caa + Cbr * Cba * (1.f - Caa));
	float g = (Cag * Caa + Cbg * Cba * (1.f - Caa));
	float b = (Cab * Caa + Cbb * Cba * (1.f - Caa));
	float a = (Caa * Caa + Cba * Cba * (1.f - Caa));

	return (ColorRGBA) {static_cast<ubyte>(r * 255.f),
						static_cast<ubyte>(g * 255.f),
						static_cast<ubyte>(b * 255.f),
						static_cast<ubyte>(a * 255.f)};
}*/
/*

ColorRGBA alphaBlending(const ColorRGBA& Ca, const ColorRGBA& Cb) //Ca Over Cb
{
	float Car(Ca.r / 255.f) , Cag(Ca.g / 255.f), Cab(Ca.b / 255.f), Caa(Ca.a / 255.f);
	float Cbr(Cb.r / 255.f) , Cbg(Cb.g / 255.f), Cbb(Cb.b / 255.f), Cba(Cb.a / 255.f);

	float finalAlpha = Caa + Cba * (1.f - Caa);

	float r =  (Car * Caa + Cbr * Cba * (1.f - Caa)) / finalAlpha;
	float g =  (Cag * Caa + Cbg * Cba * (1.f - Caa)) / finalAlpha;
	float b =  (Cab * Caa + Cbb * Cba * (1.f - Caa)) / finalAlpha;

	return (ColorRGBA) {static_cast<ubyte>(r * 255.f),
						static_cast<ubyte>(g * 255.f),
						static_cast<ubyte>(b * 255.f),
						static_cast<ubyte>(finalAlpha * 255.f)};
}
*/
ColorRGBA alphaBlendingWithoutBlendAlpha(const ColorRGBA& Ca, const ColorRGBA& Cb) //Ca Over Cb
{
	float Car(Ca.r / 255.f) , Cag(Ca.g / 255.f), Cab(Ca.b / 255.f), Caa(Ca.a / 255.f);

	float finalAlpha = Caa;

	float r =  (Car * Caa) / finalAlpha;
	float g =  (Cag * Caa) / finalAlpha;
	float b =  (Cab * Caa) / finalAlpha;

	return (ColorRGBA) {static_cast<ubyte>(r * 255.f),
						static_cast<ubyte>(g * 255.f),
						static_cast<ubyte>(b * 255.f),
						static_cast<ubyte>(finalAlpha * 255.f)};
}

void Renderer::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c, unsigned int z)
{
	assert(x < texBuffer_.width() && y < texBuffer_.heigth());

	ColorRGBA ca = texBuffer_.getRGBAPixelColor(x, y);

	if (z > zBuffer_[texBuffer_.width() * y + x])
	{
		if (c.a == 255)
		{
			texBuffer_.	setPixelColor(x, y, c);
		}
		else
		{
			if (zBuffer_[texBuffer_.width() * y + x] == 0)
			{
				texBuffer_.setPixelColor(x, y, alphaBlendingWithoutBlendAlpha(c, ca)); //C over Ca
			}
			else
			{
				texBuffer_.setPixelColor(x, y, alphaBlending(c, ca)); //C over Ca
			}
		}

		zBuffer_	[texBuffer_.width() * y + x] = z;
	}
	else if (ca.a != 255)
	{
		texBuffer_.setPixelColor(x, y, alphaBlending(ca, c)); //Ca over C		
	}
}