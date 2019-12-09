#include "color.hpp"


ColorRGBA operator+(const ColorRGBA& otherColor1, const ColorRGBA& otherColor2)
{
	int r = otherColor1.r + otherColor2.r;
	int g = otherColor1.g + otherColor2.g;
	int b = otherColor1.b + otherColor2.b;
	int a = otherColor1.a + otherColor2.a;

    if (r > 255)
    {        
        r = 255;
    }

    if (g >  255)
    {
        g = 255;
    }

    if (b >  255)
    {
        b = 255;
    }

    if (a >  255)
    {
        a = 255;
    }
    
	return (ColorRGBA){	static_cast<ubyte>(r), static_cast<ubyte>(g),static_cast<ubyte>(b) ,static_cast<ubyte>(a)};
}

ColorRGBA operator=(ColorRGBA& otherColor1, const ColorRGB& otherColor2)
{
    otherColor1.r = otherColor2.r;
    otherColor1.g = otherColor2.g;
    otherColor1.b =  otherColor2.b;
    otherColor1.a = 1;

    return otherColor1;
}

ColorRGB operator*(const ColorRGB& color, float alpha)
{
    return (ColorRGB) { static_cast<ubyte>(color.r * alpha), static_cast<ubyte>(color.g * alpha), 
                        static_cast<ubyte>(color.b * alpha)};
}