#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <vector>
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

		 /*----------*/
		/* accessor */
	   /*----------*/

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
		unsigned int 				height_;
		ColorRGBA*					pPixels_;

	private:
};

#endif // _TEXTURE_H
