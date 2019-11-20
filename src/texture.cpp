#include "texture.hpp"
#include <cassert>
#include <cstdlib>

Texture::Texture (unsigned int width, unsigned int height)
	:	width_	(width),
		height_	(height),
		pPixels_(static_cast<ColorRGBA*>(calloc(width * height, sizeof(ColorRGBA))))
{}

Texture::~Texture ()
{
	if (pPixels_ != nullptr)
		free(pPixels_);
}

void Texture::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c)
{
	assert(x < width_ && y < height_);
	pPixels_[width_ * y + x] = c;
}

ColorRGBA*		Texture::operator[]		(unsigned int indexLine) const
{
	assert(indexLine < height_);
	return &pPixels_[indexLine * width_];
}

ColorRGBA*		Texture::operator[]		(unsigned int indexLine)
{
	assert(indexLine < height_);
	return &pPixels_[indexLine * width_];
}
