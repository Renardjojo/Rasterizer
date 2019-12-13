#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <vector>
#include "mesh.hpp"
#include "vec.hpp"
#include "mat.hpp"
#include "renderer.hpp"
#include "referential.hpp"
#include "color.hpp"
#include "light.hpp"
#include "material.hpp"

typedef enum E_primitive3D
{
	NONE 	=	-1,
	CUBE	= 	 0,
	SPHERE	=	 1,
	CYLINDRE=	 2 

} Primitive3D;

class Entity
{
	public:

		#pragma region constructor/destructor

		Entity () = default;
		
		//constructor to init entity this position, scale and rotation. Entity can be choose in function of enum E_primitive3D
		//Entity is dependant of another referntial. For free entity, use world referential.
		Entity (const math::Vec3& 	translVec,
				const math::Vec3& 	rotVec, 
				const math::Vec3& 	scaleVec,
				Ref3& 				dependance,	 
				Primitive3D 		primitive = E_primitive3D::NONE); //TODO : add subdivision

		Entity (const Entity& other) = default;
		~Entity () = default;

		#pragma endregion //!constructor/destructor

		#pragma region methods

		//display vextex in function of his matrix TRS
		void					drawPoint				(Renderer& ren) const noexcept;
		void 					drawLine				(Renderer& ren) const noexcept;
		void 					drawFill				(Renderer& ren) const noexcept;
		void 					drawFillWithLigths		(Renderer& ren, const std::vector<Light>& light) const noexcept;
		void 					drawNormal				(Renderer& ren) const noexcept;

		//this function update TRS matrix of entity in function of dependante matrix. If entity depende of world, put in paramter the world TRS matrix.
		//This function must be update each time that his parent TRS matrix change (rotation, scale, translatoin...)
		//void 			updateTRS				(const math::Mat4& TRSMatDep);


		//return the transformation of a vertex in a vec4
		math::Vec4				transformVertexInVec4	(const math::Vec3&) const;

		#pragma endregion //!methods

		#pragma region accessor

	   const 	Ref3& 				getTransform()				const noexcept	{ return transform_;}
	   			Ref3& 				getTransform()					  noexcept	{ return transform_;}

	   const 	std::shared_ptr<Mesh>&	getpMesh	()				const noexcept	{ return pMesh_;}
	  			std::shared_ptr<Mesh>&	getpMesh	()					  noexcept	{ return pMesh_;}

		const 	Material*		getpMaterial	() const noexcept	{ return pMaterial_;}
		 		Material*		getpMaterial	() noexcept			{ return pMaterial_;}

		#pragma endregion //!accessor

		#pragma region mutator

		//Enable to create entity material.
		void 	setMaterial	(Material* pMat) { pMaterial_ = pMat; }; //TODO: with more paramter


		#pragma endregion //!mutator

		#pragma region operator

		#pragma endregion //!operator

		#pragma region convertor

		#pragma endregion //!convertor

	protected:

		#pragma region attribut

		std::shared_ptr<Mesh>		pMesh_;				//pointor toward mesh (allow to not duplicate vertex)
		Ref3						transform_;			//local referential of entity. Entity is clip into another referntial and dependant of it.
		Material*					pMaterial_; 		//Material of the entity
		
		#pragma endregion //!attribut

		#pragma region static attribut

		static std::shared_ptr<Mesh> pMeshCube;
		static std::shared_ptr<Mesh> pMeshSphere;
		static std::shared_ptr<Mesh> pMeshCylindre;

		#pragma endregion //! static attribut

		#pragma region methods

		//retrun an array of modified vectices form local to global. Project Shape in ortho
		std::vector<Vertex>	transformLocalToGlobal	(const math::Mat4& matTRS, unsigned int winW, unsigned int winH) const;

		#pragma endregion //!methods

	private:
};

#endif // _ENTITY_H