#include "texture.hpp"

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <GL/glu.h>
#include <string.h>

inline Texture::Texture (unsigned int width, unsigned int height, E_PixelFormat pixelFormat)
	:	width_			(width),
		heigth_			(height),
		pPixels_		(static_cast<ColorRGBA*>(calloc(width * height, sizeof(ColorRGBA)))),
		pixelFormat_	(pixelFormat)
{}


inline Texture::Texture (const char* path)
	:	width_			(0),
		heigth_			(0),
		pPixels_		(nullptr),
		pixelFormat_	(E_PixelFormat::RGB)
{
	loadTexture (path);
}

inline Texture::~Texture ()
{
	if (pPixels_ != nullptr)
		free(pPixels_);
}

inline void Texture::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c)
{
	assert(x < width_ && y < heigth_);

	if (pixelFormat_ == E_PixelFormat::RGB)
	{
		ColorRGB* pC = static_cast<ColorRGB*>(pPixels_);
		pC += width_ * y + x;
		*pC = {c.r, c.g, c.b};
	}
	else
	{
		ColorRGBA* pC = static_cast<ColorRGBA*>(pPixels_);
		pC += width_ * y + x;
		*pC = {c.r, c.g, c.b, c.a};
	}
}

inline void Texture::clear		()
{
	if (pixelFormat_ == E_PixelFormat::RGB)
	{
		memset(pPixels_, 0, width_ * heigth_ * sizeof(ColorRGB));
	}
	else
	{
		memset(pPixels_, 0, width_ * heigth_ * sizeof(ColorRGBA));
	}
}

inline void*		Texture::operator[]		(unsigned int indexLine) const
{
	assert(indexLine < heigth_);

	if (pixelFormat_ == E_PixelFormat::RGB)
	{
		ColorRGB* pC = static_cast<ColorRGB*>(pPixels_);
		pC += indexLine * width_ * pixelFormat_;
		return pC;
	}
	else
	{
		ColorRGBA* pC = static_cast<ColorRGBA*>(pPixels_);
		pC += indexLine * width_ * pixelFormat_;
		return pC;
	}
}


inline void*		Texture::operator[]		(unsigned int indexLine)
{
	assert(indexLine < heigth_);

	if (pixelFormat_ == E_PixelFormat::RGB)
	{
		ColorRGB* pC = static_cast<ColorRGB*>(pPixels_);
		pC += indexLine * width_ * pixelFormat_;
		return pC;
	}
	else
	{
		ColorRGBA* pC = static_cast<ColorRGBA*>(pPixels_);
		pC += indexLine * width_ * pixelFormat_;
		return pC;
	}
}

inline ColorRGBA		Texture::getRGBAPixelColor (unsigned int x, unsigned int y) const noexcept
{ 
    assert(x < width_ && y < heigth_);
    unsigned int i = width_ * y + x;

    if (pixelFormat_ == RGBA)
    {
        auto cRGBA = static_cast<ColorRGBA*>(pPixels_);
        return ColorRGBA{cRGBA[i].r, cRGBA[i].g, cRGBA[i].b, cRGBA[i].a};
    }
    else
    {
        auto cRGB = static_cast<ColorRGB*>(pPixels_);
        return (ColorRGBA){cRGB[i].r, cRGB[i].g, cRGB[i].b, 255};
    }
}

inline void Texture::loadTexture (const char* path)
{
	SDL_Surface* image = IMG_Load(path);

	if (image == nullptr)
	{
		std::cerr << "Image not initilized with path : " << path << std::endl;
		exit(EXIT_FAILURE);
	}

	if (pPixels_ != nullptr)
		free(pPixels_);

	if (image->format->BytesPerPixel == 4)
	{
		pixelFormat_ = E_PixelFormat::RGBA;
	}
	else
	{
		pixelFormat_ = E_PixelFormat::RGB;
	}

	pPixels_ 	= image->pixels;
	width_		= image->w;
	heigth_		= image->h;
}