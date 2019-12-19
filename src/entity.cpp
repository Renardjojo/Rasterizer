#include "entity.hpp"
#include "rasterizer.hpp"

using namespace math;
using namespace std;

Entity::Entity(const math::Vec3 &translVec,
			   const math::Vec3 &rotVec,
			   const math::Vec3 &scaleVec,
			   Ref3 &dependance,
			   E_primitive3D primitive)
	: pMesh_		(nullptr),
	  transform_	("Test", translVec, rotVec, scaleVec, dependance),
	  pMaterial_	(nullptr)
{
	switch (primitive)
	{
	case E_primitive3D::NONE:
		break;

	case E_primitive3D::CUBE:
		if (pMeshCube == nullptr)
			pMeshCube = Mesh::createCube();

		pMesh_ = pMeshCube;
	break;

	case E_primitive3D::SPHERE:
		if (pMeshSphere == nullptr)
			pMeshSphere = Mesh::createSphere(10, 10);

		pMesh_ = pMeshSphere;
	break;

	case E_primitive3D::CYLINDRE:
		if (pMeshCylindre == nullptr)
			pMeshCylindre = Mesh::createCylindre(15);

		pMesh_ = pMeshCylindre;
	break;

	case E_primitive3D::TRIANGLE:
		if (pMeshTriangle == nullptr)
			pMeshTriangle = Mesh::createTriangle();

		pMesh_ = pMeshTriangle;
	break;

	default:
		break;
	}
}

shared_ptr<Mesh> Entity::pMeshCube(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere(nullptr);
shared_ptr<Mesh> Entity::pMeshCylindre(nullptr);
shared_ptr<Mesh> Entity::pMeshTriangle(nullptr);