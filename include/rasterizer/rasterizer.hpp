#ifndef _RASTERIZER_HPP
#define _RASTERIZER_HPP

#include <cmath>
#include <SDL2/SDL.h>
#include "../math/vertex.hpp"
#include "texture.hpp"

//private function
float		min					(float, float);
float		max					(float, float);
float		dotProduct			(Vertex&, Vertex&);
Vertex		projectVertex		(Vertex&);

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
		static void		drawLine		(Texture&, Vertex&, Vertex&);
		
		/**
		 * function : drawTriangle
		 *
		 * parameter : 
		 *  : 
		 *  :
		 *
		 * return (type void):
		 *
		 * brief : this function draw colorfull triangle. Use algorythme of barycenter triangle.
		 */
		static void		drawTriangle		(Texture&, const Vertex& , const Vertex& , const Vertex&);
		
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
	
	private:
};

#endif // _RASTERIZER_HPP
