#include "entity.hpp"

using namespace math;

Entity::Entity (const math::Vec3& 	translVec,
				const math::Vec3& 	rotVec, 
				const math::Vec3& 	scaleVec,
				Ref3& 				dependance,
				Primitive3D 		primitive)
	:	pMesh_		(nullptr),
		transform_	("Test", translVec, rotVec, scaleVec, dependance)
{
	switch (primitive)
	{
		case E_primitive3D::NONE :
		break;

		case E_primitive3D::CUBE :
			if (pMeshCube == nullptr)
				pMeshCube =  Mesh::createCube();

			pMesh_ = pMeshCube;
		break;

		case E_primitive3D::SPHERE :
			if (pMeshSphere == nullptr)
				pMeshSphere =  Mesh::createSphere(10, 10);

			pMesh_ = pMeshSphere;
		break;
	
		default :
		break;
	}
}


void 	Entity::draw		(Texture& RenBuffer) const noexcept
{
	assert(pMesh_ != nullptr);

	//TODO
}

shared_ptr<Mesh> Entity::pMeshCube 		(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere	(nullptr);

