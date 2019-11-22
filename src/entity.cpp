#include "entity.hpp"
#include "rasterizer.hpp"

using namespace math;
using namespace std;

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

vector<Vertex> Entity::transformLocalToGlobal(const Mat4 &matTRS) const
{
	vector<Vertex> vertexGlobal;
	for (auto &vertex : pMesh_->getVertices())
	{
		Vec4 vec (vertex.position_);
		vec = matTRS * vec;
		vertexGlobal.push_back({vec.x_, vec.y_, vec.z_});
	}

	return vertexGlobal;
}

Vec4 Entity::transformVertexInVec4(const Vertex & vertex) const
{
	return (Vec4) {vertex.position_.x_, vertex.position_.y_, vertex.position_.z_, 1};
}

void Entity::drawPoint(Texture &RenBuffer) const noexcept
{
	if(pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vec4> vertexToVec4;
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix());

	for (auto &vertex : globalVertex)
	{
		vertexToVec4.push_back(transformVertexInVec4(vertex));
	}


	for (auto &vertex : vertexToVec4)
	{
		vertex.homogenize();

		vertex.x_ = ((vertex.x_ / 5) + 1) * 0.5 * 800;
		vertex.y_ = 600 - ((vertex.y_ / 5) + 1) * 0.5 * 600;
		RenBuffer.setPixelColor(vertex.x_, vertex.y_, {0, 255, 0, 255});
	}
}

void Entity::drawLine(Texture &RenBuffer) const noexcept
{



}

void Entity::drawFill(Texture &RenBuffer) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	for (size_t i = 0; i < pMesh_->getIndices().size(); i+= 3)
	{
			std::cout<< i << "	" << pMesh_->getIndices().size() << std::endl;
			Rasterizer::drawTriangle(	RenBuffer, 
										pMesh_->getVertices()[pMesh_->getIndices()[i]],
										pMesh_->getVertices()[pMesh_->getIndices()[i + 1]],
										pMesh_->getVertices()[pMesh_->getIndices()[i + 2]]);
	}
}


shared_ptr<Mesh> Entity::pMeshCube(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere(nullptr);
