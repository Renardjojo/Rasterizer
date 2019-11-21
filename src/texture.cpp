#include "texture.hpp"
#include <cassert>
#include <cstdlib>

Texture::Texture (unsigned int width, unsigned int height)
	:	width_	(width),
		heigth_	(height),
		pPixels_(static_cast<ColorRGBA*>(calloc(width * height, sizeof(ColorRGBA))))
{}

Texture::~Texture ()
{
	if (pPixels_ != nullptr)
		free(pPixels_);
}

void Texture::setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c)
{
	//assert(x < width_ && y < heigth_);

	if (x < width_ && y < heigth_)
		pPixels_[width_ * y + x] = c;
}

void Texture::clear		()
{
	if (pPixels_ != nullptr)
		free(pPixels_);

	pPixels_ = static_cast<ColorRGBA*>(calloc(width_ * heigth_, sizeof(ColorRGBA)));

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
