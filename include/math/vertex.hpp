#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

#include "vec3.hpp"
#include "color.hpp"

class Vertex
{
	public:

	   	#pragma region constructor/destructo

		Vertex () 			 			= default;
		Vertex (float x, float y, float z, float nx = 0.f, float ny = 0.f, float nz = 0.f,	ubyte r = 255, ubyte g = 255, 
																							ubyte b = 255, ubyte a = 255);
		Vertex (const math::Vec3& position, const math::Vec3& normal, ColorRGBA& color);

		Vertex (const Vertex& other) 	= default;
		~Vertex () 						= default;

		#pragma endregion //!constructor/destructor

		#pragma region methods
		#pragma endregion //!methods

		#pragma region static methods
		#pragma endregion //!static methods

		#pragma region accessor
		#pragma endregion //!accessor

		#pragma region mutator
		#pragma endregion //!mutator

		#pragma region operator
		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

		//public variable (get and set with no effect for class)
		math::Vec3	position_;
		math::Vec3	normal_;
		ColorRGBA	color_;

	protected:
		
		#pragma region attribut
		#pragma endregion //!attribut

		#pragma region static attribut
		#pragma endregion //! static attribut

		#pragma region methods
		#pragma endregion //!methods

	private:
};

#endif // _VERTEX_H