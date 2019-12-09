#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>
#include <string>
#include <math.h>
#include <cassert>

#include "vec2.hpp"
#include "vec3.hpp"
#include "color.hpp"

class Vertex
{
	public:

	   	#pragma region constructor/destructor

		Vertex () 			 			= default;
		Vertex (	float x, float y, float z,
					float nx = 0.f, float ny = 0.f, float nz = 0.f,	
					float tcx = 0.f, float tcy = 0.f,
					ubyte r = 255, ubyte g = 255, ubyte b = 255, ubyte a = 255)
			: 	position_	{x, y, z},
				normal_		{nx, ny, nz},
				texCoords_	{tcx, tcy},
				color_		{r, g, b, a}
		{}

		Vertex (const math::Vec3& position, const math::Vec3& normal, const math::Vec2& textCoord, ColorRGBA color = {255, 255, 255, 255})
			: 	position_	(position),
				normal_		(normal),
				texCoords_	(textCoord),
				color_		{color.r, color.g, color.b, color.a}
		{}

		Vertex (const math::Vec3&& position, const math::Vec3&& normal, const math::Vec2&& textCoord, ColorRGBA&& color = {255, 255, 255, 255})
			: 	position_	(std::move(position)),
				normal_		(std::move(normal)),
				texCoords_	(std::move(textCoord)),
				color_		{std::move(color.r), std::move(color.g), std::move(color.b), std::move(color.a)}
		{}

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

		// Public variable (get and set with no effect for class)
		math::Vec3	position_;
		math::Vec3	normal_;
		math::Vec2	texCoords_; // Texture's coordinates

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