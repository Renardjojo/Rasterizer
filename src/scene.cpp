#include "scene.hpp"
#include "referential.hpp"

using namespace math;

Scene::Scene ()
	: 	entities_	(),
		world		()
{
	entities_.reserve(50);	
}

unsigned int 	Scene::addEntity(const Vec3&  originVec, const Vec3& orientationVec, const Vec3& scaleVec, 
								int entityIDDependance, Primitive3D primitive) throw()
{
	if (entityIDDependance > (int)entities_.size() || entityIDDependance < -1)
		throw range_error("ID does not exist to create entity");

	entities_.push_back(Entity(	originVec, 
								orientationVec,
								scaleVec,
								entityIDDependance == -1 ? 
								world :	entities_[entityIDDependance - 1].getTransform(),
								primitive));

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
	for (auto& entity : entities_)
	{
		//entity.drawFill(RenBuffer);
		entity.drawLine(RenBuffer);
		entity.getTransform().displayAxis(RenBuffer);
	}	
}

const Entity& 			Scene::getEntity		(unsigned int id) const throw()
{
	if (id > entities_.size())
		throw range_error("ID does not exist to destroy entity");

	return entities_[id - 1];
}

Entity& 			Scene::getEntity		(unsigned int id) throw()
{
	if (id > entities_.size())
		throw range_error("ID does not exist to destroy entity");

	return entities_[id - 1];
}

