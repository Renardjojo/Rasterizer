#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

#include "vec3.hpp"


class Vertex
{
	public:
		Vertex () 			 	= default;
		Vertex (float x, float y, float z);

		Vertex (const Vertex& other) 	= default;
		Vertex (const math::Vec3& other);

		~Vertex () 						= default;

		 /*----------*/
		/* methode  */
	   /*----------*/

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
		math::Vec3 position_;

	protected:
		
	private:
};

#endif // _VERTEX_H
