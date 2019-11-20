#include "entity.hpp"

using namespace math;

Entity::Entity (const Vec3& scaleVec, const Vec3& rotVec, const Vec3& translVec, Primitive3D primitive)
	:	pMesh_			(nullptr),
		transformation_	(Mat4::createTRSMatrix(scaleVec, rotVec, translVec))
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


void 	Entity::display		()
{
	assert(pMesh_ != nullptr);
	
	//TODO
}

shared_ptr<Mesh> Entity::pMeshCube 		(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere	(nullptr);

