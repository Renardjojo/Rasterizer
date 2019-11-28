#include "entity.hpp"
#include "rasterizer.hpp"

using namespace math;
using namespace std;

Entity::Entity(const math::Vec3 &translVec,
			   const math::Vec3 &rotVec,
			   const math::Vec3 &scaleVec,
			   Ref3 &dependance,
			   Primitive3D primitive)
	: pMesh_(nullptr),
	  transform_("Test", translVec, rotVec, scaleVec, dependance)
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

vector<Vertex> Entity::transformLocalToGlobal(const Mat4 &matTRS, unsigned int winW, unsigned int winH) const
{
	vector<Vertex> vertexGlobal = pMesh_->getVertices();
	for (auto &vertex : vertexGlobal)
	{
		Vec4 vec(vertex.position_);
		vec = matTRS * vec;
		vertex.position_ = {static_cast<float>(((vec.x_ / 5) + 1) * 0.5f * winW),
							static_cast<float>(winH - ((vec.y_ / 5) + 1) * 0.5 * winH),
							vec.z_};

		Vec4 vecN(vertex.normal_);
		vecN = matTRS * vecN;
		vertex.normal_  = {vecN.x_, vecN.y_, vecN.z_};

		vertex.normal_.normalize();
	}
	return vertexGlobal;
}

Vec4 Entity::transformVertexInVec4(const Vertex &vertex) const
{
	return (Vec4){vertex.position_.x_, vertex.position_.y_, vertex.position_.z_, 1};
}

void Entity::drawPoint(Texture &RenBuffer) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), RenBuffer.width(), RenBuffer.heigth());

	for (auto &vertex : globalVertex)
	{
		RenBuffer.setPixelColor(vertex.position_.x_, vertex.position_.y_, {0, 255, 0, 255});
	}
}

void Entity::drawLine(Texture &RenBuffer) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), RenBuffer.width(), RenBuffer.heigth());

	for (size_t i = 0; i < pMesh_->getIndices().size(); i += 3)
	{
		Rasterizer::drawLine(	RenBuffer, 
								globalVertex[pMesh_->getIndices()[i]],
								globalVertex[pMesh_->getIndices()[i + 1]]);

		Rasterizer::drawLine(	RenBuffer, 
								globalVertex[pMesh_->getIndices()[i + 1]],
								globalVertex[pMesh_->getIndices()[i + 2]]);

		Rasterizer::drawLine(	RenBuffer, 
								globalVertex[pMesh_->getIndices()[i + 2]],
								globalVertex[pMesh_->getIndices()[i]]);
	}
}

void Entity::drawFill(Texture &RenBuffer) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), RenBuffer.width(), RenBuffer.heigth());

	for (size_t i = 0; i < pMesh_->getIndices().size() ; i += 3)
	{
		Rasterizer::drawTriangle(RenBuffer,
								 globalVertex[pMesh_->getIndices()[i]],
								 globalVertex[pMesh_->getIndices()[i + 1]],
								 globalVertex[pMesh_->getIndices()[i + 2]]);
	}
}

void Entity::drawFillWithLigths		(Texture &RenBuffer, const std::vector<Light>& light) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), RenBuffer.width(), RenBuffer.heigth());

	for (size_t i = 0; i < pMesh_->getIndices().size() ; i += 3)
	{
		Rasterizer::drawTriangleWithLights(RenBuffer, light,
								 globalVertex[pMesh_->getIndices()[i]],
								 globalVertex[pMesh_->getIndices()[i + 1]],
								 globalVertex[pMesh_->getIndices()[i + 2]]);
	}
}

/*
void Entity::updateTRS (const math::Mat4& TRSMatDep)
{
	transform_.updateTRSMat(TRSMatDep);
}*/


shared_ptr<Mesh> Entity::pMeshCube(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere(nullptr);