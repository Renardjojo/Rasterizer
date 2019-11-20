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
		
		
		

		 /*----------*/
		/* accessor */
	   /*----------*/

		Texture& getDrawBuffer() { return texBuffer_;}

		 /*----------*/
		/* mutator  */
	   /*----------*/

		 /*----------*/
		/* operator */
	   /*----------*/

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

		//public variable (get and set with no effect for class)

	protected:

		SDL_Renderer*	SDLRen_;
		SDL_Texture*	SDLBuffer_;
		Texture 		texBuffer_;
			

	private:
};

#endif // _RENDERER_H	
