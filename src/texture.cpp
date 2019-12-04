#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <GL/glu.h>

#include "texture.hpp"

Texture::Texture (unsigned int width, unsigned int height)
	:	width_	(width),
		heigth_	(height),
		pPixels_(static_cast<ColorRGBA*>(calloc(width * height, sizeof(ColorRGBA)))),
		zBuffer_(static_cast<unsigned int*>(malloc(width * height * sizeof(unsigned int))))
{
	//init zBuffer wither min value
	for (size_t i = 0; i < width * height; i++)
	{
		zBuffer_[i] = 0; //uint limit
	}
}

Texture::Texture (const char* addressPNG) 
{
	SDL_Surface* image = IMG_Load(addressPNG);

	if (image == nullptr)
	{
		std::cerr << "Image not initilized with path : " << addressPNG << std::endl;
		exit(EXIT_FAILURE);
	}

	if (image->format->format != SDL_PIXELFORMAT_RGBA8888) 
	{
		std::cerr << "Texture only support RGBA format, other texture is not implemented. Path : " << addressPNG << std::endl;
		exit(EXIT_FAILURE);
	}

	pPixels_ = static_cast<ColorRGBA*>(image->pixels);
}

Texture::~Texture ()
{
	if (pPixels_ != nullptr)
		free(pPixels_);

	if (zBuffer_ != nullptr)
		free(zBuffer_);
}

void Texture::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c, unsigned int z)
{
	//assert(x < width_ && y < heigth_);

	//TODO: Add opacity function in function of depth
	if (x < width_ && y < heigth_ && z > zBuffer_[width_ * y + x])
	{
		pPixels_[width_ * y + x] = c;
		zBuffer_[width_ * y + x] = z;
	}
}

void Texture::clear		()
{
	if (pPixels_ != nullptr)
		free(pPixels_);
	
	if (zBuffer_ != nullptr)
		free(zBuffer_);

	pPixels_ = static_cast<ColorRGBA*>(calloc(width_ * heigth_, sizeof(ColorRGBA)));
	zBuffer_ = static_cast<unsigned int*>(malloc(width_ * heigth_ * sizeof(unsigned int)));

	for (size_t i = 0; i < width_ * heigth_; i++)
	{
		zBuffer_[i] = 0; //uint limit
	}
}

void image(int, int)
{}

void Texture::nearestNeighborTexturing(Vertex& ver)
{
	float Uint = ver.u + 0.5; 
	float Vint = ver.v + 0.5;
}

void Texture::bilinearFiltering(Vertex& ver)
{
	int Uint = ver.u;
	int Vint = ver.v;

	float Ufrac = ver.u - Uint;
	float Vfrac = ver.v - Vint;

	// float ??
	float Cfinal =	C00 * (1 - Ufrac) * (1 - Vfrac) + C10 * Ufrac * (1 - Vfrac) + C01 * (1 - Ufrac) * Vfrac 
					+ C11 * Ufrac * Vfrac;

	// return Cfinal

}

ColorRGBA*		Texture::operator[]		(unsigned int indexLine) const
{
	assert(indexLine < heigth_);
	return &pPixels_[indexLine * width_];
}

ColorRGBA*		Texture::operator[]		(unsigned int indexLine)
{
	assert(indexLine < heigth_);
	return &pPixels_[indexLine * width_];
}