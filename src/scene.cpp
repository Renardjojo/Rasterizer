#include "scene.hpp"

using namespace math;

unsigned int 	Scene::addEntity(const Vec3& scaleVec, const Vec3& rotVec, const Vec3& translVec, Primitive3D primitive) noexcept
{
	entities_.push_back(Entity(scaleVec, rotVec, translVec, primitive));
	return entities_.size();
}

void 			Scene::deleteEntity	(unsigned int id) throw()
{
	if (id > entities_.size() - 1)
		throw range_error("ID does not exist to destroy entity");

	entities_.erase(entities_.begin() + id);
}

void 			Scene::draw				(Texture& RenBuffer) const noexcept
{
	for (auto& entity : entities_)
		entity.draw(RenBuffer);
}
