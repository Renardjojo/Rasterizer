#include "texture.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

Texture::Texture (unsigned int width, unsigned int height)
	:	width_	(width),
		heigth_	(height),
		pPixels_(static_cast<ColorRGBA*>(calloc(width * height, sizeof(ColorRGBA)))),
		zBuffer_(static_cast<unsigned int*>(malloc(width * height * sizeof(unsigned int))))
{
	//init zBuffer wither min value
	for (size_t i = 0; i < width * height; i++)
	{
		zBuffer_[i] = __INT_MAX__ * 2U + 1; //uint limit
	}
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

	//TODO: Add opacity function oin function of depth
	if (x < width_ && y < heigth_ /*&& z < zBuffer_[width_ * y + x]*/)
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
		zBuffer_[i] = __INT_MAX__ * 2U + 1; //uint limit
	}
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
