#include "entity.hpp"
#include "rasterizer.hpp"

using namespace math;
using namespace std;

Entity::Entity(const math::Vec3 &translVec,
			   const math::Vec3 &rotVec,
			   const math::Vec3 &scaleVec,
			   Ref3 &dependance,
			   Primitive3D primitive)
	: pMesh_		(nullptr),
	  transform_	("Test", translVec, rotVec, scaleVec, dependance),
	  materials_	(nullptr)
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

	default:
		break;
	}
}

void 	Entity::setTexture		(const char* path)
{
	assert (path != nullptr);

	pTexture_ = make_unique<Texture>(path);
}

vector<Vertex> Entity::transformLocalToGlobal(const Mat4 &matTRS, unsigned int winW, unsigned int winH) const
{
	vector<Vertex> vertexGlobal = pMesh_->getVertices();
	for (auto &vertex : vertexGlobal)
	{
		vertex.position_ = (matTRS * vertex.position_).xyz;
		vertex.position_.x = static_cast<float>(((vertex.position_.x / 5) + 1) * 0.5f * winW);
		vertex.position_.y = static_cast<float>(winH - ((vertex.position_.y / 5) + 1) * 0.5 * winH);

		vertex.normal_ = (matTRS * vertex.normal_).xyz;
		vertex.normal_.normalize();
	}
	return vertexGlobal;
}

Vec4 Entity::transformVertexInVec4(const Vec3& vertex) const
{
	return (Vec4){vertex.x, vertex.y, vertex.z, 1};
}

void Entity::drawPoint(Renderer &ren) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), ren.width(), ren.heigth());

	for (auto &vertex : globalVertex)
	{
		ren.setPixelColor(vertex.position_.x, vertex.position_.y, {0, 255, 0, 255});
	}
}

void Entity::drawLine(Renderer &ren) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), ren.width(), ren.heigth());
/*
	for (size_t i = 0; i < pMesh_->getIndices().size(); i += 3)
	{
		Rasterizer::drawLine(	ren, 
								globalVertex[pMesh_->getIndices()[i]],
								globalVertex[pMesh_->getIndices()[i + 1]]);

		Rasterizer::drawLine(	ren, 
								globalVertex[pMesh_->getIndices()[i + 1]],
								globalVertex[pMesh_->getIndices()[i + 2]]);

		Rasterizer::drawLine(	ren, 
								globalVertex[pMesh_->getIndices()[i + 2]],
								globalVertex[pMesh_->getIndices()[i]]);
	}*/
}

void Entity::drawFill(Renderer &ren) const noexcept
{
	if (pMesh_ == nullptr)
		return;

	// Transform all the Mesh's Vertices to Vec4
	vector<Vertex> globalVertex = transformLocalToGlobal(transform_.getTRSMatrix(), ren.width(), ren.heigth());

	for (size_t i = 0; i < pMesh_->getNbTriangle() ; i += 3)
	{
		Rasterizer::drawTriangle(ren,
								 globalVertex[i],
								 globalVertex[i + 1],
								 globalVertex[i + 2]);
	}
}

/*
void Entity::updateTRS (const math::Mat4& TRSMatDep)
{
	transform_.updateTRSMat(TRSMatDep);
}*/


shared_ptr<Mesh> Entity::pMeshCube(nullptr);
shared_ptr<Mesh> Entity::pMeshSphere(nullptr);
shared_ptr<Mesh> Entity::pMeshCylindre(nullptr);