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

unsigned int 	Scene::addEntity(const Vec3&  originVec, const Vec3& orientationVec, const Vec3& scaleVec, const char* objPath) noexcept
{
	entities_.push_back(std::make_unique<Entity>(originVec, 
												orientationVec,
												scaleVec,
												world,
												E_primitive3D::NONE));

	entities_.back()->getpMesh() = Mesh::loadObj(objPath);

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
	//Rasterizer::renderScene(ren, *this, Mat4::createOrthoMatrix(-1.f, 1.f, -1.f, 1.f, 0.f, -100.f));
	Rasterizer::renderScene(ren, *this, Mat4::createPerspectiveMatrix(800/(float)600, 0.01f, 100.f, 150.f));
}

void			Scene::moveFront 	(float movement)
{
	for (auto& ent : entities_)
	{
		ent->getTransform().translate({0, 0, movement});
	}
}

void 			Scene::moveBack 	(float movement)
{
	for (auto& ent : entities_)
	{
		ent->getTransform().translate({0, 0, -movement});
	}
}

void 			Scene::turnLeft 	(float rotation)
{
	for (auto& ent : entities_)
	{
		ent->getTransform().rotate({0, rotation, 0});
	}
}

void 			Scene::turnRight	(float rotation)
{
	for (auto& ent : entities_)
	{
		ent->getTransform().rotate({0, -rotation, 0});
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