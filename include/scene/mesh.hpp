#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <math.h>
#include <memory>
#include "texture.hpp"
#include "mat4.hpp"
#include "vertex.hpp"

class Mesh
{
	public:

		#pragma region constructor/destructor

		Mesh ()						= default;
		Mesh (const Mesh& other) 	= default;
		~Mesh () 					= default;

		#pragma endregion //!constructor/destructor

		#pragma region methods

		//this function draw normal vector of vertex. This function use buffer of pixel and use TRSMatrix of object to display normal in good emplace.
		void 	drawNormal(Texture& RenBuffer, const math::Mat4& TRSMatrix) 	const;

		#pragma endregion //!methods

		#pragma region static methods

		//create cube of size 1 with triangle and return mesh. Cube is centered on the origin
		static std::shared_ptr<Mesh> createCube	();
		
		//create sphere of radius 1 and return it mesh.	Sphere is centered on the origin	
		static std::shared_ptr<Mesh> createSphere(int latitudeCount, int longitudeCount);

		//this function return pointor to mesh of Cylindre with x precision
		static std::shared_ptr<Mesh> createCylindre(unsigned int prescision);

		#pragma endregion //!static methods

		#pragma region accessor

		 const 	std::vector<Vertex>&	getVertices	() const 	{ return vertices_;}
		 		std::vector<Vertex>&	getVertices	() 			{ return vertices_;}

		 const 	std::vector<int>&		getIndices	() const	{ return indices_;}
		 		std::vector<int>&		getIndices	() 			{ return indices_;}

		#pragma endregion //!accessor

		#pragma region mutator
		#pragma endregion //!mutator

		#pragma region operator
		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

	protected:

		#pragma region attribut

		std::vector<Vertex> vertices_; //vertex buffer. Local vertices, doesn't change
		std::vector<int>	indices_;  //indices buffer. Define triangle of mesh. It's a suit of triplet index
		Texture*			pTexture = nullptr;

		#pragma endregion //!attribut

		#pragma region static attribut
		#pragma endregion //! static attribut

		#pragma region methods
		#pragma endregion //!methods

	private:
};

#endif // _MESH_H