#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <map>
#include <math.h>
#include <memory>
#include <utility>
#include <cassert>
#include <vector>

#include "vec.hpp"
#include "vertex.hpp"
#include "materials.hpp"

typedef struct S_Indices
{
	unsigned int iV, iVt, iVn;

} Indices;

typedef struct S_FaceIndices
{
	Indices iV1, iV2, iV3;

} FaceIndices;

typedef struct S_VertexInfo
{
	const math::Vec3&	pos; 
	const math::Vec2&	textCord; 
	const math::Vec3&	normal;

} VertexInfo;

typedef struct S_Face
{
	VertexInfo v1, v2, v3;

} Face;

class Mesh
{
	public:

		#pragma region constructor/destructor

		Mesh ()						= default;
	

		Mesh (const Mesh& other) 	= default;
		~Mesh () 					= default;

		#pragma endregion //!constructor/destructor

		#pragma region methods

		#pragma endregion //!methods

		#pragma region static methods

		//create cube of size 1 with triangle and return mesh. Cube is centered on the origin
		static std::shared_ptr<Mesh> createCube	();

		//load .obj file and return pointer to the new mesh
		static std::shared_ptr<Mesh> loadObj	(const char* path);
		
		//create sphere of radius 1 and return it mesh.	Sphere is centered on the origin	
		static std::shared_ptr<Mesh> createSphere(int latitudeCount, int longitudeCount);

		//this function return pointor to mesh of Cylindre with x precision
		static std::shared_ptr<Mesh> createCylindre(unsigned int prescision);

		#pragma endregion //!static methods

		#pragma region accessor

		//return the number of triangle in the mesh
		unsigned int 					getNbTriangle	()				{ return facesIndices_.size();}

		//return the number of triangle in the mesh
		std::vector<Vertex> 					getVertices	()			
		{
			std::vector<Vertex> vertice;
			vertice.reserve(facesIndices_.size() * 3);

			for (size_t i = 0; i < facesIndices_.size(); i++)
			{
				vertice.push_back({vertex_[facesIndices_[i].iV1.iV], normal_[facesIndices_[i].iV1.iVn], {0,0}});
				vertice.push_back({vertex_[facesIndices_[i].iV2.iV], normal_[facesIndices_[i].iV2.iVn], {0,0}});
				vertice.push_back({vertex_[facesIndices_[i].iV3.iV], normal_[facesIndices_[i].iV3.iVn], {0,0}});
			}

			return vertice;
		}

		//this function stock allow information about face and return it. Face is composed of 3 vertex
		const Face 	getFace	(unsigned int iFace) const noexcept
		{
			assert (iFace < facesIndices_.size());
			return Face{{vertex_[facesIndices_[iFace].iV1.iV], textCoord_[facesIndices_[iFace].iV1.iVt], normal_[facesIndices_[iFace].iV1.iVn]},
						{vertex_[facesIndices_[iFace].iV2.iV], textCoord_[facesIndices_[iFace].iV2.iVt], normal_[facesIndices_[iFace].iV2.iVn]},
						{vertex_[facesIndices_[iFace].iV3.iV], textCoord_[facesIndices_[iFace].iV3.iVt], normal_[facesIndices_[iFace].iV3.iVn]}};
		}

		#pragma endregion //!accessor

		#pragma region mutator
		
		#pragma endregion //!mutator

		#pragma region operator
		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

		#pragma region attribut

		std::vector<math::Vec3> 					vertex_; 		// Vertex buffer. Local vertices, doesn't change
		std::vector<math::Vec2> 					textCoord_; 	// Buffer of texture coordonnate
		std::vector<math::Vec3> 					normal_;		// Buffer of normal. Nomral is unit vector indicate the direction of face

		std::vector<FaceIndices>					facesIndices_;  // Indices buffer. Define triangle of mesh. It's a suit of triplet index
		static Materials*							pMaterial_;		// Pointer of mesh's material

		#pragma endregion //!attribut

	protected:

		#pragma region static attribut
		#pragma endregion //!static attribut

		#pragma region methods
		#pragma endregion //!methods

	private:
};

#endif // _MESH_H