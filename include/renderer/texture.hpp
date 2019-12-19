#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <cassert>
#include "color.hpp"
#include "vertex.hpp"
#include "vec.hpp"

typedef enum E_PixelFormat
{
	RGB		= 3,
	RGBA	= 4

} PixelFormat;

class Texture
{
	public:

		#pragma region constructor/destructor

		Texture () = delete;

		//create black sized texture 
		Texture (unsigned int width, unsigned int height, E_PixelFormat pixelFormat = E_PixelFormat::RGBA);
		Texture (const Texture& other) = delete; //TODO
		Texture (const char* path);
		~Texture ();

		#pragma endregion //!constructor/destructor

		#pragma region methods

		//color pixel of matrix. Z paramater correspond to the depth of pixel in zBuffer
		void setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c);

		/**
		 * function : clear
		 *
		 * parameter : 
		 *
		 * return (type void):
		 *
		 * brief : This function destroy the current Texture and alloc new texture buffer with the same size. Clear in black
		 */
		void		clear		();

		#pragma endregion //!methods

		#pragma region static methods

		#pragma endregion //!static methods

		#pragma region accessor

		unsigned int 	width	() const { return width_; }
		unsigned int 	heigth	() const { return heigth_; }

		ColorRGBA		getRGBAPixelColor (unsigned int x, unsigned int y) const noexcept;

		const PixelFormat& 	getPixelFormat () const noexcept 	{ return pixelFormat_;}		
		PixelFormat& 		getPixelFormat () noexcept 			{ return pixelFormat_;}

		#pragma endregion //!accessor

		#pragma region mutator
		#pragma endregion //!mutator

		#pragma region operator

		void operator=(const Texture& other) = delete; //TODO

		/**
		 * function : operator[]
		 *
		 * parameter : 
		 * unsigned int indexLine : index of line in texture
		 *
		 * return (type float*):return tab of float corresponding to line of texture.
		 *
		 * brief : this function return tab of float corresponding to line of texture.
		 * This form allow this call texture[n][m]. Thirst element start to 0 : [0][0]. Max = [line-1][colomn-1]
		 */
		void*		operator[]		(unsigned int indexLine) const;

		/**
		 * function : operator[]
		 *
		 * parameter : 
		 * unsigned int indexLine : index of line in texture
		 *
		 * return (type float*):return tab of float corresponding to line of texture.
		 *
		 * brief : this function return tab of float corresponding to line of texture.
		 * This form allow this call texture[n][m]. Thirst element start to 0 : [0][0]. Max = [line-1][colomn-1]
		 */
		void*		operator[]		(unsigned int indexLine); 

		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

	protected:

		#pragma region attribut

		unsigned int 		width_;
		unsigned int 		heigth_;
		void*				pPixels_;
		PixelFormat			pixelFormat_;

		#pragma endregion //!attribut

		#pragma region static attribut
		#pragma endregion //! static attribut

		#pragma region methods

		//this function load texture only in PNG for moment
		void loadTexture (const char* path);

		#pragma endregion //!methods
};

#include "texture.inl"

#endif //_TEXTURE_H