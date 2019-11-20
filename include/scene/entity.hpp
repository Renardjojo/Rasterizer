#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include "mesh.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

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
		Entity (const math::Vec3& scaleVec, 
				const math::Vec3& rotVec, 
				const math::Vec3& translVec, 
				Primitive3D primitive = E_primitive3D::NONE); //TODO : add subdivision

		Entity (const Entity& other) = default;
		~Entity () = default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		//display vextex in function of his matrix TRS
		void 	display		();

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

	shared_ptr<Mesh>		pMesh_;				//pointor toward mesh (allow to not duplicate vertex)
	math::Mat4				transformation_;	//matrix TRS. Allow to pass vertex form local to global


	static shared_ptr<Mesh> pMeshCube;
	static shared_ptr<Mesh> pMeshSphere;

	private:
};



#endif // _ENTITY_H
