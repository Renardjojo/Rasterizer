#include "materials.hpp"

Materials::Materials()
	:
		pTexture_ (nullptr)
{}

void Materials::setColor(ColorRGBA& color)
{
	color_.r = color.r;
    color_.g = color.g;
    color_.b = color.b;
    color_.a = color.a;
}

void Materials::setAlpha (float alpha)
{
    alpha_ = alpha;
}