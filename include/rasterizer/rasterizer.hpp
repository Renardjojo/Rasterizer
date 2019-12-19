#ifndef _RASTERIZER_HPP
#define _RASTERIZER_HPP

#include <cmath>
#include <SDL2/SDL.h>
#include "vertex.hpp"
#include "renderer.hpp"
#include "color.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "mat.hpp"
#include "material.hpp"


enum E_rasterizerSetting
{
	R_DRAW_EDGE,
	R_DRAW_DEPTH_BUFFER,
	R_DRAW_SHAPE_FILL,
	R_DRAW_MULTI_COLOR,
	R_DRAW_NORMAL,
	R_DRAW_REFERENTIAL,
	R_ENABLE_BACK_FACE_CULLING,
	R_ENABLE_CLIPPING,
	R_ENABLE_LETTERBOX_CLIPPING,
	R_ENABLE_ANTI_ALIASING,
	R_USE_PHONG_LIGHT_ALGORYTHME,
	R_USE_BLINN_PHONG_LIGHT_ALGORYTHME,
	R_ENABLE_ALPHA_BLENDING

};

struct ArgRasterizer
{
	Renderer& ren;
	const std::vector<Light>& lights; 
	const math::Vec3& viewerPosition; 

	const Material* entityMat;

	const Vertex& v1;
	const Vertex& v2;
	const Vertex& v3;

	const math::Vec3& v1RealPos; 
	const math::Vec3& v2RealPos;
	const math::Vec3& v3RealPos; 

	float depthV1;
	float depthV2;
	float depthV3;

	float wV1;
	float wV2;
	float wV3;

	const math::Mat4& inverseCameraMatrix; 
	const Texture* pTexture = nullptr;
};

class Rasterizer
{
	public:

		#pragma region constructor/destructor

		Rasterizer () = delete;
		Rasterizer (const Rasterizer& other) = delete;
		virtual ~Rasterizer () = delete;

		#pragma endregion //!constructor/destructor

		#pragma region methods

		static void		drawLine		(Renderer&, Vertex&, Vertex&);		

		 //this function draw colorfull triangle. Use algorythme of barycenter triangle
		static void		drawTriangleWithLights		(ArgRasterizer& arg);

		// This function draw each entity in scene
		static void renderScene(Renderer& ren, const Scene& scene, const math::Mat4& inverseCameraMatrix, const math::Vec3& camPos);

		static void resetNbTriangleRender	() { nbTriangleRender = 0; }

		//this function apply algorythme of MSAA for each borderer of triangle. Do not apply to back face 
		static void applyMSAA			(Renderer& ren, const Vertex& v1, const math::Vec3& v1RealPos, float depthV1, const Vertex& v2, const math::Vec3& v2RealPos, float depthV2, const Vertex& v3, const math::Vec3& v3RealPos, float depthV3);



		#pragma endregion //!methods

		#pragma region static methods
		#pragma endregion //!static methods

		#pragma region accessor

		static ColorRGBA 	getColor4f	();
		static ColorRGBA 	getColor4ub	();
		static bool 		getSetting	(E_rasterizerSetting setting) throw();
		static unsigned int getNbTringleRender() { return nbTriangleRender; }

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
		// R_ENABLE_BACK_FACE_CULLING : Allow to don't draw face in same direction au camera. Normaly not visible
		// R_ENABLE_CLIPPING		 : clipping allow to don't try to display triangle outside of screen.
		// R_ENABLE_LETTERBOX_CLIPPING : Letter box is a process in cinema in witch user can see a black bande in top and bottom of screen
		// R_ENABLE_ANTI_ALIASING		: allow to avoid aliasing because of screen resolution 
		// R_USE_PHONG_LIGHT_ALGORYTHME : Phong algorythme is an calcul to comput light with ligth different result than blinn phong algorythm. This algorythm is also more less than blinn-phong ligth.
		// R_USE_BLINN_PHONG_LIGHT_ALGORYTHME : Blinn phong algorythme is an calcul to comput light with ligth different result than phong algorythm. This algorythm is also more fast phong ligth.
		// R_ENABLE_ALPHA_BLENDING			: Enable alpha blending of entity.
		//
		static void setSetting	(E_rasterizerSetting setting, bool data) throw();

		//This function load perspective matrix in function of a FOV in Y, aspect, zNear and zFar
		static void loadPerspectiveMatrix	(	float fovy,
												float aspect,
												float zNear,
												float zFar);

		//This function load perspective matrix in function 
		static void loadOrthoMatrix	(	float  	left,
										float  	right,
										float  	bottom,
										float  	top,
										float  	nearVal,
										float  	farVal);

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
		static bool			enableBackFaceCulling;	//	by default in true
		static bool			enableClipping;			//	by default in false
		static bool			enableLetterBoxClipping;//	by default in false
		static bool			enableAntiAliasing;		//	by default in false
		static bool			usePhongLigthAlgorythme;	//	by default in false
		static bool			useBlinnPhongLigthAlgorythme;	//	by default in true
		static bool			enableAlphaBlending;			//	by default in false

		static unsigned int nbTriangleRender;

		static math::Mat4	projectionMatrix;		//Matrix of projection. Can be in perspective or in ortho. By default is identitary
		static float 		zNear;					//by default 0
		static float		zFar;					//by default 0

		#pragma endregion //! static attribut

		#pragma region methods
		#pragma endregion //!methods
	
	private:

};

#endif // _RASTERIZER_HPP