#ifndef _COLOR_RGBA_H
#define _COLOR_RGBA_H

typedef unsigned char ubyte; 

typedef struct S_ColorRGBA
{
	ubyte r,  g, b, a; //0 to 255 max. 255 is max value

} ColorRGBA;

typedef struct S_ColorRGB
{
	ubyte r, g, b; //0 to 255 max. 255 is max value

} ColorRGB;

#endif // _COLOR_RGBA_H
