#include "scene.hpp"
#include "referential.hpp"
#include "rasterizer.hpp"

using namespace math;

Scene::Scene ()
	: 	entities_	(),
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

void 			Scene::draw				(Texture& RenBuffer) const noexcept
{
	//Rasterizer::renderScene(RenBuffer, *this, Mat4::createOrthoMatrix(-1.f, 1.f, -1.f, 1.f, 0.f, -100.f));
	Rasterizer::renderScene(RenBuffer, *this, Rasterizer::CreatePerspectiveProjectionMatrix(800, 600, 0.01f, 100.f, 150.f));
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