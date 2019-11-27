#include <cassert>
#include <cstdlib>
#include <iostream>
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

void Light::setAmbientComponent(float kA, float intensityA) noexcept
{
    // kA must be between 0 and 1
    assert(kA < 1 && kA > 0);

    ambientComponent_ = kA * intensityA;
}

void Light::setDiffuseComponent(float kD, float intensityD) noexcept
{
    // kD must be between 0 and 1
    assert(kD < 1 && kD > 0);

    diffuseComponent_ = kD * intensityD;
}

void Light::setSpecularComponent(float kS, float intensityS) noexcept
{
    // kS must be between 0 and 1
    assert(kS < 1 && kS > 0);

    specularComponent_ = kS * intensityS;
}