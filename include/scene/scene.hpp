#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <memory>
#include "entity.hpp"
#include "vec3.hpp"
#include "mat4.hpp"
#include "renderer.hpp"
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


		//this function add ligth to the scene and return it id
		unsigned int 	addLigth			(const math::Vec3& originVec, float ambient, float diffuse, float specular) noexcept;

		/**
		* function : addEntity
		*
		* parameter :
		*	const math::Vec3&  	originVec			: local origin of entity
		*	const math::Vec3&  	orientationVec		: local orientation of entity in function of axes X, Y, Z 
		*	const math::Vec3&  	scaleVec 			: local scale of entity
		*	Primitive3D 		primitive 			: Predefined mesh of the entity. By default, entity do not have mesh
		*
		* return (type unsigned int): ID of entity
		*
		* brief : this function create entity in function of tranform indicate in parameter. Return error if id is incorrect
		*/
		unsigned int 	addEntity			(	const math::Vec3&  	originVec,
												const math::Vec3&  	orientationVec, 										
												const math::Vec3&  	scaleVec,
												Primitive3D 		primitive 			= E_primitive3D::NONE) noexcept;

		//Same function but to load .obj file
		unsigned int 	addEntity			(	const math::Vec3&  	originVec,
												const math::Vec3&  	orientationVec, 										
												const math::Vec3&  	scaleVec,
												const char* objPath) noexcept;

		//this function deplace entity into scene. Use std::move, so the previous pointor must be destroy and nerver use.
		unsigned int 	moveEntityInto		(	std::unique_ptr<Entity>& pEntityMove) noexcept;

		//delete entity of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteEntity		(unsigned int id) throw();

		//delete light of scene in function of id in parameter. Error if Id doesn't exist
		void 			deleteLight		(unsigned int id) throw();

		//this function draw all entities of the scene in function of there referential. It take in parameter th buffer of renderer
		void 			draw				(Renderer& ren) const noexcept;
		
		//few funciton to control camera
		void			moveFront 	(float movement);
		void 			moveBack 	(float movement);
		void 			turnLeft 	(float rotation); //in rad
		void 			turnRight	(float rotation); //in rad

		#pragma endregion //!methods

		#pragma region accessor

		const Entity& 									getEntity		(unsigned int id) 	const throw();
		Entity& 										getEntity		(unsigned int id) 	throw();
		const std::vector<std::unique_ptr<Entity>>& 	getEntities		()  				const noexcept		{return entities_;}

		const Light& 				getLight		(unsigned int id) const throw();
		Light& 						getLight		(unsigned int id) throw();
		const std::vector<Light>& 	getLights		() 				  const noexcept	{return light_;}

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