#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "entity.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

class Scene
{
	public:
		Scene ()					= default;
		Scene (const Scene& other) 	= default;
		~Scene () 					= default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		//this function add entity in scene and return it id
		unsigned int 	addEntity			(	const math::Vec3& scaleVec, 
												const math::Vec3& rotVec, 
												const math::Vec3& translVec, 
												Primitive3D primitive = E_primitive3D::NONE) noexcept;

		//delete entity of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteEntity		(unsigned int id) throw();

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
			std::vector<Entity>	entities_;

	private:
};


#endif // _SCENE_H
