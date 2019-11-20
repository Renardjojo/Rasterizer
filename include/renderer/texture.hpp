#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <vector>
#include <SDL2/SDL.h>
#include "color.hpp"

class Texture
{
	public:
		Texture () = delete;

		//create black sized texture 
		Texture (unsigned int width, unsigned int height);		
		Texture (const Texture& other) = delete; //TODO
		~Texture ();

		 /*----------*/
		/* methode  */
	   /*----------*/

		//color pixel of matrix
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

	private:
};

#endif // _TEXTURE_H