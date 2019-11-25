#include "light.hpp"

Light::Light(math::Vec3& pos, float ambient, float diffuse, float specular)
{
    position_               = pos;
    ambientComponent_       = ambient;
    diffuseComponent_       = diffuse;
    specularComponent_      = specular;
}

Light::Light(const Light& other)
    :
        position_           (other.getPosition()),
        ambientComponent_   (other.getAmbientComponent()),
        diffuseComponent_   (other.getDiffuseComponent()),
        specularComponent_  (other.getSpecularComponent())

{}

void Light::setPosition(math::Vec3 pos) noexcept
{
    position_ = pos;
}

void Light::setAmbientComponent(float ambientCompo) noexcept
{
    ambientComponent_ = ambientCompo;
}

void Light::setDiffuseComponent(float diffuseCompo) noexcept
{
    diffuseComponent_ = diffuseCompo;
}

void Light::setSpecularComponent(float specularCompo) noexcept
{
    specularComponent_ = specularCompo;
}