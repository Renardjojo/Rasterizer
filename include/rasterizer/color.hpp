#ifndef _COLOR_RGBA_H
#define _COLOR_RGBA_H

typedef unsigned char ubyte; 

typedef struct S_ColorRGBA
{
	ubyte r, g, b, a; //0 to 255 max. 255 is max value

} ColorRGBA;

typedef struct S_ColorRGB
{
	ubyte r, g, b; //0 to 255 max. 255 is max value

} ColorRGB;

inline ColorRGBA operator+(const ColorRGBA& otherColor1, const ColorRGBA& otherColor2)
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

inline ColorRGB operator*(const ColorRGB& color, float alpha)
{
    return (ColorRGB) { static_cast<ubyte>(color.r * alpha), static_cast<ubyte>(color.g * alpha), 
                        static_cast<ubyte>(color.b * alpha)};
}


#endif // _COLOR_RGBA_H
