#include "light.hpp"

Light::Light(const math::Vec3& pos, float ambient, float diffuse, float specular)
{
    position_               = pos;
    setAmbientIntensity     (ambient);
    setDiffuseIntensity     (diffuse);
    setSpecularIntensity    (specular);
}


void Light::computLightComponent(ColorRGBA& colorIntensity, const math::Vec3& normal, float shininessCoef) const
{
    computAmbiantComponent      (colorIntensity);
    computDiffuseComponent      (colorIntensity, normal);
    computSpecularComponent     (colorIntensity, shininessCoef);
}

void Light::setPosition(math::Vec3 pos) noexcept
{
    position_ = pos;
}

void Light::setAmbientIntensity(float ambientCompo) noexcept
{
    assert(ambientCompo <= 1.f && ambientCompo >= 0.f);
    ambientComponent_.kr =  ambientComponent_.kg = ambientComponent_.kb = ambientCompo;
}

void Light::setDiffuseIntensity(float diffuseCompo) noexcept
{
    assert(diffuseCompo <= 1.f && diffuseCompo >= 0.f);
    diffuseComponent_.kr =  diffuseComponent_.kg = diffuseComponent_.kb = diffuseCompo;
}

void Light::setSpecularIntensity(float specularCompo) noexcept
{
    std::cout << specularCompo << std::endl;
    assert(specularCompo <= 1.f && specularCompo >= 0.f);
    specularComponent_.kr =  specularComponent_.kg = specularComponent_.kb = specularCompo;
}

void Light::computAmbiantComponent     (ColorRGBA& colorIntensity) const
{
    colorIntensity.r *= ambientComponent_.kr;
    colorIntensity.g *= ambientComponent_.kg;
    colorIntensity.b *= ambientComponent_.kb;
}

void Light::computDiffuseComponent     (ColorRGBA& colorIntensity, const math::Vec3& normal) const
{
    float cosTeta = position_.dot_product(normal);

    colorIntensity.r = colorIntensity.r * diffuseComponent_.kr * cosTeta;
    colorIntensity.g = colorIntensity.g * diffuseComponent_.kg * cosTeta;
    colorIntensity.b = colorIntensity.b * diffuseComponent_.kb * cosTeta;
}

void Light::computSpecularComponent     (ColorRGBA& colorIntensity, float shininessCoef)  const
{



}