#include "scene.hpp"
#include "referential.hpp"

using namespace math;

Scene::Scene ()
	: 	entities_	(),
		world		()
{
	entities_.reserve(50);	
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

void 			Scene::draw				(Texture& RenBuffer) const noexcept
{
	for (unsigned int i = 0; i < entities_.size(); i++)
	{
		entities_[i]->drawFill(RenBuffer);
		//entities_[i].drawLine(RenBuffer, (i == 0) ? (ColorRGBA){255,0,0,255} : (ColorRGBA){0,255,0,255});
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

