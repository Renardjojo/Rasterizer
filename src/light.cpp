#include <cmath>
#include "light.hpp"

using namespace math;

Light::Light(const math::Vec3& pos, float ambient, float diffuse, float specular)
{
    position_               = pos;
    normalizePosition_      = pos.getNormalize();
    setAmbientIntensity     (ambient);
    setDiffuseIntensity     (diffuse);
    setSpecularIntensity    (specular);
}


void Light::computLightComponent(ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition, const Vec3& position, float shininessCoef) const
{
    ColorRGBA colorIntensityDiffuse = colorIntensity;
    ColorRGBA colorIntensitySpec    = colorIntensity;
    computAmbiantComponent          (colorIntensity);

    Vec3 normalPosLightWithObj = (position_ - position).getNormalize();
    Vec3 Viewer = (viewerPosition - position).getNormalize();

    float cosTeta = normalPosLightWithObj.dot_product(normal);

	if (cosTeta < 0.f)
		return;

	computDiffuseComponent      (colorIntensityDiffuse, normal, cosTeta);
	computSpecularBlinnPhong    (colorIntensitySpec, normal, Viewer, shininessCoef, cosTeta, normalPosLightWithObj);		
	
    colorIntensity = colorIntensity + colorIntensityDiffuse + colorIntensitySpec;
}

void Light::setPosition(math::Vec3 pos) noexcept
{
    position_ = pos;
    normalizePosition_ = pos.getNormalize();
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
    assert(specularCompo <= 1.f && specularCompo >= 0.f);
    specularComponent_.kr = specularComponent_.kb = specularComponent_.kg = specularCompo;
}

void Light::computAmbiantComponent     (ColorRGBA& colorIntensity) const
{
    colorIntensity.r *= ambientComponent_.kr;
    colorIntensity.g *= ambientComponent_.kg;
    colorIntensity.b *= ambientComponent_.kb;
}

void Light::computDiffuseComponent     (ColorRGBA& colorIntensity, const math::Vec3& normal, float cosTeta) const
{
    colorIntensity.r *= (diffuseComponent_.kr * cosTeta);
    colorIntensity.g *= (diffuseComponent_.kg * cosTeta);
    colorIntensity.b *= (diffuseComponent_.kb * cosTeta);
}

void Light::computSpecularBlinnPhong     (ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition,
                                                                    float shininessCoef, float cosTeta, const Vec3& normalPosLightWithObj)  const
{    
    // If the angle between the normal and the light direction is greater than 90 degrees, 
    // then we force the specular term to zero.
 
    if (cosTeta / (normalPosLightWithObj.length() * normal.length()) > 90)
    {
        colorIntensity.r = colorIntensity.g = colorIntensity.b = 0;
        return;
    }

    math::Vec3 add   = normalPosLightWithObj + viewerPosition;

    //H: The halfway vector between the viewer and light-source vectors
    // Dot product of the normal and H of the camera
   	math::Vec3 H = add / add.length();
    float rst = normal.dot_product(H);
    //math::Vec3 H = normalizePosition_;


    float powCosGamCoefShiniMult255 = 255 * powf(rst, shininessCoef);

    colorIntensity.r = specularComponent_.kr * powCosGamCoefShiniMult255;
    colorIntensity.g = specularComponent_.kg * powCosGamCoefShiniMult255;
    colorIntensity.b = specularComponent_.kb * powCosGamCoefShiniMult255;
}

void Light::computSpecularPhong     (ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition, 
                                                                    float shininessCoef, const Vec3& normalPosLightWithObj)  const
{
    math::Vec3 reflexionR   = 2 * normal.dot_product(normalPosLightWithObj) * normal - normalPosLightWithObj;

    // Dot product of reflexionR and the position of the camera
    float cosGamma = reflexionR.dot_product(viewerPosition.getNormalize());

    if (cosGamma < 0.f)
        cosGamma = 0.f;
    
    colorIntensity.r = 255 * specularComponent_.kr * powf(cosGamma, shininessCoef);
    colorIntensity.g = 255 * specularComponent_.kg * powf(cosGamma, shininessCoef);
    colorIntensity.b = 255 * specularComponent_.kb * powf(cosGamma, shininessCoef);
}
