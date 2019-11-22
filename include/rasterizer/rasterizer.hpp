#ifndef _RASTERIZER_HPP
#define _RASTERIZER_HPP

#include <cmath>
#include <SDL2/SDL.h>
#include "../math/vertex.hpp"
#include "texture.hpp"

class Rasterizer
{
	public:
		Rasterizer () = default;
		Rasterizer (const Rasterizer& other) = default;
		virtual ~Rasterizer () = default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		/**
		 * function : drawLine
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : 
		 */
		void		drawLine		(Texture&, Vertex&, Vertex&);
		
		/**
		 * function : drawTriangle
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : 
		 */
		void		drawTriangle		(Texture&, Vertex& , Vertex& , Vertex&);
		
		

		 /*----------*/
		/* accessor */
	   /*----------*/

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
	


		//private function
		float		min					(float, float);
		float		max					(float, float);
		float		dotProduct			(Vertex&, Vertex&);
		//float		crossProduct		(Vertex&, Vertex&);
		void		projectVertex		(Vertex&);


	private:
};

#endif // _RASTERIZER_HPP
