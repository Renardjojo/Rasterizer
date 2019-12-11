#include <cassert>
#include "materials.hpp"

Materials::Materials()
	:
		pTexture_ (nullptr)
{}

/*Materials::Materials(tinyobj::real_t a, tinyobj::real_t d, tinyobj::real_t s)
{
    //pTexture_               = texture;
    ambientComponent_[3]    = a;
    diffuseComponent_[3]    = d;
    specularComponent_[3]   = s;

}*/

void Materials::setColor(ColorRGB& color)
{
	color_.r = color.r;
    color_.g = color.g;
    color_.b = color.b;
}

void Materials::setAlpha (float alpha)
{
    alpha_ = alpha;
}

/*void Materials::addMaterial(const char* pathMtl)
{
    assert(pathMtl != nullptr);

    pMaterial_.emplace(pathMtl, pMaterial_.end());
}

Materials* Materials::getMaterial(std::string id_material)
{
    assert(id_material != "");

    return pMaterial_.find(id_material)->second.get();
}*/