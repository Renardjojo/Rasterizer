#include "scene.hpp"
#include "referential.hpp"
#include "rasterizer.hpp"

using namespace math;

Scene::Scene ()
	: 	camPos_		{},
		camOrientation_		{0, 0, 0},
		camScale_	{1.f, 1.f, 1.f},
		playerDir_	{0.f, 0.f, -1.f},
		entities_	(),
		light_		(),
		world		()
{
	entities_.reserve(50);
	light_.reserve(10);
}

unsigned int 	Scene::addLigth			(const math::Vec3& originVec, float ambient, float diffuse, float specular) noexcept
{
	light_.emplace_back(originVec, ambient, diffuse, specular);
	return light_.size();

}

unsigned int 	Scene::addEntity(const Vec3&  originVec, const Vec3& orientationVec, const Vec3& scaleVec, Primitive3D primitive) noexcept
{
	entities_.push_back(std::make_unique<Entity>(originVec, 
												orientationVec,
												scaleVec,
												world,
												primitive));

	entities_.back()->setMaterial(Material::getMaterial("Default"));

	return entities_.size();
}

unsigned int 	Scene::addEntity(const Vec3&  originVec, const Vec3& orientationVec, const Vec3& scaleVec, const char* objPath) noexcept
{
	entities_.push_back(std::make_unique<Entity>(originVec, 
												orientationVec,
												scaleVec,
												world,
												E_primitive3D::NONE));


	pair<Material*, shared_ptr<Mesh>> objInfo = Mesh::loadObj(objPath);
	entities_.back()->setMaterial(objInfo.first);
	entities_.back()->getpMesh() 	 = objInfo.second;

	return entities_.size();
}

unsigned int 	Scene::moveEntityInto (std::unique_ptr<Entity>& pEntityMove) noexcept
{
	//pEntityMove->getTransform().updateTRSMat(world.getTRSMatrix());
	entities_.push_back(std::move(pEntityMove));
	return entities_.size();
}

void 			Scene::deleteEntity	(unsigned int id) throw()
{
	if (id > entities_.size())
		throw range_error("ID does not exist to destroy entity");

	entities_.erase(entities_.begin() + id);
}

void 			Scene::deleteLight	(unsigned int id) throw()
{
	if (id > light_.size())
		throw range_error("ID does not exist to destroy light");

	light_.erase(light_.begin() + id);
}

void 			Scene::draw				(Renderer& ren) const noexcept
{
	Mat4 matCam = Mat4::createTRSMatrix(camScale_, camOrientation_, camPos_);
	
	matCam.reverse(matCam);

	//Rasterizer::renderScene(ren, *this, Mat4::createOrthoMatrix(-1.f, 1.f, -1.f, 1.f, 0.f, -100.f));
	Rasterizer::renderScene(ren, *this, Mat4::createPerspectiveMatrix(800/(float)600, 0.01f, 100.f, 150.f), matCam);
}

void 			Scene::zoom				(float zoom)
{
	for (auto& ent : entities_)
	{
		ent->getTransform().scale({zoom, zoom, zoom});
	}
}

const Entity& 			Scene::getEntity		(unsigned int id) const throw()
{
	if (id > entities_.size())
		throw range_error("ID does not exist to destroy entity");

	return (*entities_[id - 1]);
}

Entity& 			Scene::getEntity		(unsigned int id) throw()
{
	if (id > entities_.size())
		throw range_error("ID does not exist to destroy entity");

	return (*entities_[id - 1]);
}

const Light& 			Scene::getLight		(unsigned int id) const throw()
{
	if (id > light_.size())
		throw range_error("ID does not exist to destroy light");

	return light_[id - 1];
}

Light& 			Scene::getLight		(unsigned int id) throw()
{
	if (id > light_.size())
		throw range_error("ID does not exist to destroy light");

	return light_[id - 1];
}