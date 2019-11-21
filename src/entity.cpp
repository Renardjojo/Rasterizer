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

	default:
		break;
	}
}

vector<Vertex> Entity::transformLocalToGlobal(Mat4 &matTRS) const
{
	vector<Vertex> vertexGlobal;
	for (auto &vertex : pMesh_->getVertices())
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
			}
		}
	}

	return vertexGlobal;
}

Vec4 Entity::transformVertexInVec4(const Vertex & vertex) const
{
	return (Vec4) {vertex.position_.x_, vertex.position_.y_, vertex.position_.z_, 1};
}

void Entity::draw(Texture &RenBuffer) const noexcept
{
	assert(pMesh_ != nullptr);

	// Transform all the Mesh's Vertices to Vec4
	vector<Vec4> vertexToVec4;
	for (auto &vertex : pMesh_->getVertices())
	{
		vertexToVec4.push_back(Mat4::createProjectionMatrix(0.5f) * transformVertexInVec4(vertex));
	}

	for (auto &vertex : vertexToVec4)
	{
		vertex.homogenize();

		RenBuffer.setPixelColor(vertex.x_, vertex.y_, {0, 255, 0, 255});
	}
}

shared_ptr<Mesh> Entity::pMeshCube(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere(nullptr);
