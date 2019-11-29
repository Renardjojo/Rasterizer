#ifndef _RASTERIZER_HPP
#define _RASTERIZER_HPP

#include <cmath>
#include <SDL2/SDL.h>
#include "vertex.hpp"
#include "texture.hpp"
#include "color.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "mat4.hpp"


enum E_rasterizerSetting
{
	R_DRAW_EDGE,
	R_DRAW_DEPTH_BUFFER,
	R_DRAW_SHAPE_FILL,
	R_DRAW_MULTI_COLOR,
	R_DRAW_NORMAL,
	R_DRAW_REFERENTIAL

};

class Rasterizer
{
	public:

		#pragma region constructor/destructor

		Rasterizer () = default;
		Rasterizer (const Rasterizer& other) = default;
		virtual ~Rasterizer () = default;

		#pragma endregion //!constructor/destructor

		#pragma region methods

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
		static void		drawTriangle				(Texture&, const Vertex& , const Vertex& , const Vertex&);
		static void		drawTriangleWithLights		(Texture&, const std::vector<Light>& lights, const Vertex& v1, const Vertex& v2, const Vertex& v3);
		static void		drawTriangleWithTexture		(Texture*, const Vertex& , const Vertex& , const Vertex&);

		// This function draw each entity in scene
		static void renderScene(Texture& renBuffer, const Scene& scene, const math::Mat4& projectionMatrix);

		#pragma endregion //!methods

		#pragma region static methods
		#pragma endregion //!static methods

		#pragma region accessor

		static ColorRGBA 	getColor4f	();
		static ColorRGBA 	getColor4ub	();
		static bool 		getSetting	(E_rasterizerSetting setting) throw();

		#pragma endregion //!accessor

		#pragma region mutator

		// To set color of rasterizer between 0.f and 1.0f (less perform  than function setColor4ub())
		static void setColor4f	( float r, float g, float b, float a);

		// To set color of rasterizer between 0 and 255 (more perform than function setColor4f())
		static void setColor4ub	( ubyte r, ubyte g, ubyte b, ubyte a);

		// This function allow to set setting for rasterizing. Indicate in first paramter witch setting chang and in parameter the booleean
		//
		// R_DRAW_EDGE				: Allow to draw the edge of shape in mode drawTriangle(). By default in false
		// R_DRAW_DEPTH_BUFFER		: Allow to draw depth buffer. This buffer is relative to the distance between user and objet and allow to draw correctely the shape. by default to false 
		// R_DRAW_SHAPE_FILL		: Allow to draw the shape fill in mode drawTriangle(). By default to true.
		// R_DRAW_MULTI_COLOR		: Allow to drawn shape in multi color in mode drawTriangle(). By default to false.
		// R_DRAW_NORMAL			: Allow to draw the normal of each vertexe.
		// R_DRAW_REFERENTIAL		: Allow to draw the referential of entity
		//
		static void setSetting	(E_rasterizerSetting setting, bool data) throw();
		
		// This function creates a perspective projection matrix
		static math::Mat4 CreatePerspectiveProjectionMatrix(int width, int height, float near, float far, float fov);

		#pragma endregion //!mutator

		#pragma region operator
		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

	protected:

		#pragma region attribut
		#pragma endregion //!attribut

		#pragma region static attribut

		//Few setting
		static ColorRGBA 	color; 					//	Color of shape, by default in white
		static bool			drawEdge;				//	by default in false 
		static bool			drawZBuffer;			//	by default in false
		static bool			drawShapeFill;			//	by default in true
		static bool			drawMutliColor;			//	by default in false
		static bool			drawNormal;				//	by default in false
		static bool			drawReferential;		//	by default in false

		#pragma endregion //! static attribut

		#pragma region methods
		#pragma endregion //!methods
	
	private:

};

#endif // _RASTERIZER_HPP