#include "materials.hpp"

Materials::Materials()
	:
		pTexture_ (nullptr)
{}

void Materials::setColor(ColorRGB& color)
{
	color_.r = color.r;
    color_.g = color.g;
    color_.b = color.b;
}

void Materials::setAlpha (float alpha)
{
    alpha_ = alpha;
}

ColorRGBA Materials::alphaBlending(ColorRGB& Ca, ColorRGBA& Cb)
{   
    // Ca.a = 1, not transparency regarding already drawn pixels

    ColorRGB Co = (Ca * 1 /*Ca.a*/ + (Cb * Cb.a) * (1 - 1 /*Ca.a*/)) / 1 /*Ca.a*/ + (Cb.a * (1 - 1 /*Ca.a*/));
    
    ColorRGBA Cofinale = Co;

    return Cofinale;
}