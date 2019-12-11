#include "material.hpp"
#include <cassert>

using namespace std;

Material::Material(LightComponent&& lc)
    :   lightComp_      {lc},
        pTexture_       {nullptr},
        alpha_          {1.f}
{}

void Material::addMaterial(LightComponent&& LightComponent)
{
    pMaterial_.insert(pair<string, unique_ptr<Material>>("test", make_unique<Material>(LightComponent)));
}

const Material* Material::getMaterial(string id_material)
{
    assert(!id_material.empty());

    return pMaterial_.find(id_material)->second.get();
}