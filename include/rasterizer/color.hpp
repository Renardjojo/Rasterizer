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

ColorRGBA operator+(const ColorRGBA& otherColor1, const ColorRGBA& otherColor2);
//ColorRGBA operator=(const ColorRGBA& otherColor1, const ColorRGB& otherColor2);
ColorRGB operator*(const ColorRGB& color, float alpha);
ColorRGBA operator*(const ColorRGBA& color, float alpha); 




#endif // _COLOR_RGBA_H
