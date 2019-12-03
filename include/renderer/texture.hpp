#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "color.hpp"
#include "vertex.hpp"
#include "vec3.hpp"

class Texture
{
	public:
		Texture () = delete;

		//create black sized texture 
		Texture (unsigned int width, unsigned int height);	
		Texture (const Texture& other) = delete; //TODO
		Texture (const char* addressPNG);
		~Texture ();

		 /*----------*/
		/* methode  */
	   /*----------*/

		//color pixel of matrix. Z paramater correspond to the depth of pixel in zBuffer
		void setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c, unsigned int z = 0xffffffff);

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
		


		void bilinearFiltering(math::Vec3& vec);

		 /*----------*/
		/* accessor */
	   /*----------*/

		unsigned int 	width	() const { return width_; }
		unsigned int 	heigth	() const { return heigth_; }

		 /*----------*/
		/* mutator  */
	   /*----------*/

		 /*----------*/
		/* operator */
	   /*----------*/

		

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
		ColorRGBA*		operator[]		(unsigned int indexLine) const;

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
		ColorRGBA*		operator[]		(unsigned int indexLine);

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

		//public variable (get and set with no effect for class)

	protected:
		
		unsigned int 				width_;
		unsigned int 				heigth_;
		ColorRGBA*					pPixels_;
		unsigned int*				zBuffer_;	//Z buffer determined the depth of pixel. If 2 textures war add, Z buffer determined whitch pixel is hidden

	private:
};

#endif // _TEXTURE_H
