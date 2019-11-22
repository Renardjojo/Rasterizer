#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <vector>
#include "mesh.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "texture.hpp"
#include "referential.hpp"

typedef enum E_primitive3D
{
	NONE 	=	-1,
	CUBE	= 	 0,
	SPHERE	=	 1 //level of quality of sphere. 1 for higth quality, 4 for low.

} Primitive3D;


class Entity
{
	public:
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

		 /*----------*/
		/* methode  */
	   /*----------*/

		//display vextex in function of his matrix TRS
		void			drawPoint				(Texture& RenBuffer) const noexcept;
		void 			drawLine				(Texture &RenBuffer) const noexcept;
		void 			drawFill				(Texture &RenBuffer) const noexcept;

		//retrun an array of modified vectices
		vector<Vertex>	transformLocalToGlobal	(const math::Mat4&) const;

		//return the transformation of a vertex in a vec4
		math::Vec4			transformVertexInVec4	(const Vertex&) const;

		 /*----------*/
		/* accessor */
	   /*----------*/

	   const Ref3& 		getTransform()				const noexcept { return transform_;}
	   Ref3& 			getTransform()					  noexcept { return transform_;}

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

	shared_ptr<Mesh>		pMesh_;				//pointor toward mesh (allow to not duplicate vertex)
	Ref3					transform_;			//local referential of entity. Entity is clip into another referntial and dependant of it.


	static shared_ptr<Mesh> pMeshCube;
	static shared_ptr<Mesh> pMeshSphere;

	private:
};



#endif // _ENTITY_H