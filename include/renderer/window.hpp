//window.hpp
//Editing by Six Jonathan
//Date : 2019-11-20

#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>

class Window
{
	public:
		Window () = delete;
		Window (unsigned int width, unsigned int heigth);
		Window (const Window& other) = delete;
		~Window ();

		 /*----------*/
		/* methode  */
	   /*----------*/

		//this function update input. It be update once by frame
		//void catchInput		();

		 /*----------*/
		/* accessor */
	   /*----------*/

		const SDL_Window*		get () const 	{ return win; }
		SDL_Window*				get () 			{ return win; }

		unsigned int 			width () const	{ return width_;}
		unsigned int			heigth() const 	{ return heigth_;}
		

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

	SDL_Window* win;
	unsigned int width_;
	unsigned int heigth_;

	private:
};


#endif // _WINDOW_H
