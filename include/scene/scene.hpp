#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <memory>
#include "entity.hpp"
#include "vec3.hpp"
#include "mat4.hpp"
#include "texture.hpp"
#include "light.hpp"

class Scene
{
	public:

		#pragma region constructor/destructor
		
		Scene ();
		Scene (const Scene& other) 	= default;
		~Scene () 					= default;

		#pragma endregion //!constructor/destructor

		#pragma region methods

		/**
		* function : addEntity
		*
		* parameter :
		*	const math::Vec3&  	originVec			: local origin of entity
		*	const math::Vec3&  	orientationVec		: local orientation of entity in function of axes X, Y, Z 
		*	const math::Vec3&  	scaleVec 			: local scale of entity
		*	Primitive3D 		primitive 			: The mesh of the entity. By default, entity do not have mesh
		*
		* return (type unsigned int): ID of entity
		*
		* brief : this function create entity in function of tranform indicate in parameter. Return error if id is incorrect
		*/
		unsigned int 	addEntity			(	const math::Vec3&  	originVec,
												const math::Vec3&  	orientationVec, 										
												const math::Vec3&  	scaleVec,
												Primitive3D 		primitive 			= E_primitive3D::NONE) noexcept;
		//this function deplace entity into scene. Use std::move, so the previous pointor must be destroy and nerver use.
		unsigned int 	moveEntityInto		(	std::unique_ptr<Entity>& pEntityMove) noexcept;

		//delete entity of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteEntity		(unsigned int id) throw();

		//delete light of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteLight		(unsigned int id) throw();

		//this function draw all entities of the scene in function of there referential. It take in parameter th buffer of renderer
		void 			draw				(Texture& RenBuffer) const noexcept;

		#pragma endregion //!methods

		#pragma region accessor

		const Entity& 		getEntity		(unsigned int id) const throw();
		Entity& 			getEntity		(unsigned int id) throw();

		const Light& 		getLight		(unsigned int id) const throw();
		Light& 				getLight		(unsigned int id) throw();

		#pragma endregion //!accessor

		#pragma region mutator

		#pragma endregion //!mutator

		#pragma region operator

		#pragma endregion //!operator

		#pragma region convertor

		#pragma endregion //!convertor

	protected:

		#pragma region attribut

		std::vector<std::unique_ptr<Entity>>	entities_;	//TODO: Must be replace by map or set conteneur
		std::vector<Light>						light_;
		Ref3									world; 		//world referential of scene. Do not move.

		#pragma endregion //!attribut


	private:
};

#endif // _SCENE_H