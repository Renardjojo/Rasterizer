//renderer.hpp
//Editing by Six Jonathan
//Date 2019-11-20

#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL2/SDL.h>
#include "texture.hpp"

class Renderer
{
	public:

		//create 2 buffer of pixel from window size.
		Renderer (SDL_Window* win,  int winW, int winH);
		Renderer (const Renderer& other) = delete;
		~Renderer ();

		 /*----------*/
		/* methode  */
	   /*----------*/
	
		/**
		 * function : renderPresent
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : update SDLBuffer with pixel of texBuffer and display SDLBuffer. Clear the texBuffer
		 */
		void		swapBuffer	() noexcept;
		

		/**
		 * function : renderClear
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : clear the SDLBuffer
		 */
		void		clear		()  noexcept;
		
		//ColorRGBA alphaBlending(const ColorRGBA& Ca, ColorRGBA& Cb);
	//	ColorRGB alphaBlending(const ColorRGBA& Ca, ColorRGB& Cb);

		

		 /*----------*/
		/* accessor */
	   /*----------*/

		Texture& getDrawBuffer() { return texBuffer_;}
		unsigned int* getDepthBuffer() { return zBuffer_;}

		//this function return the color of pixel in current renderer
		const ColorRGBA& 	getPixelColor(unsigned int x, unsigned int y) const noexcept	
		{ 
			ColorRGBA* pC = static_cast<ColorRGBA*>(texBuffer_[0]);
			pC += width() * y + x;
			return *pC;	
		}

		ColorRGBA& 			getPixelColor(unsigned int x, unsigned int y) noexcept
		{ 
			ColorRGBA* pC = static_cast<ColorRGBA*>(texBuffer_[0]);
			pC += width() * y + x;
			return *pC;	
		}

		unsigned int 	width	() const { return texBuffer_.width(); }
		unsigned int 	heigth	() const { return texBuffer_.heigth(); }


		 /*----------*/
		/* mutator  */
	   /*----------*/

		//color pixel of matrix. Z paramater correspond to the depth of pixel in zBuffer
		void setPixelColor(unsigned int x, unsigned int y, const ColorRGBA& c, unsigned int z = 0xffffffff);

		 /*----------*/
		/* operator */
	   /*----------*/

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

		//public variable (get and set with no effect for class)

	protected:

		SDL_Renderer*			SDLRen_;
		SDL_Texture*			SDLBuffer_;
		Texture			 		texBuffer_;
		unsigned int*			zBuffer_;	//Z buffer determined the depth of pixel. If 2 textures war add, Z buffer determined whitch pixel is hidden

	private:


};

#include "renderer.inl"

#endif // _RENDERER_H	
