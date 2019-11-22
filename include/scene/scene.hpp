#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "entity.hpp"
#include "vec3.hpp"
#include "mat4.hpp"
#include "texture.hpp"

class Scene
{
	public:
		Scene ()					;
		Scene (const Scene& other) 	= default;
		~Scene () 					= default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		/**
		* function : addEntity
		*
		* parameter :
		*	const math::Vec3&  	originVec			: local origin of entity
		*	const math::Vec3&  	orientationVec		: local orientation of entity in function of axes X, Y, Z 
		*	const math::Vec3&  	scaleVec 			: local scale of entity
		*	int 			   	entityIDDependance  : Entity can by depand of another entity for exemple, car motor depdand of car... . 
		*											  By default with id -1, entity depend about WORLD referential. Else give the id of entity dependance
		*	Primitive3D 		primitive 			: The mesh of the entity. By default, entity do not have mesh
		*
		* return (type unsigned int): ID of entity
		*
		* brief : this function create entity in function of tranform indicate in parameter. Return error if id is incorrect
		*/
		unsigned int 	addEntity			(	const math::Vec3&  	originVec,
												const math::Vec3&  	orientationVec, 										
												const math::Vec3&  	scaleVec,												
												int 			   	entityIDDependance	= -1,
												Primitive3D 		primitive 			= E_primitive3D::NONE) throw();

		//delete entity of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteEntity		(unsigned int id) throw();

		//this function draw all entities of the scene in function of there referential. It take in parameter th buffer of renderer
		void 			draw				(Texture& RenBuffer) const noexcept;

		 /*----------*/
		/* accessor */
	   /*----------*/

		const Entity& 		getEntity		(unsigned int id) const throw();
		Entity& 			getEntity		(unsigned int id) throw();

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
			std::vector<Entity>	entities_;	//TODO: Must be replace by map or set conteneur
			Ref3				world; 		//world referential of scene. Do not move.

	private:
};


#endif // _SCENE_H
