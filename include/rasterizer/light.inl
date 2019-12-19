#include "light.hpp"

using namespace math;

inline Light::Light(const math::Vec3& pos, float ambient, float diffuse, float specular)
{
    position_               = pos;
    normalizePosition_      = pos.getNormalize();
    setAmbientIntensity     (ambient);
    setDiffuseIntensity     (diffuse);
    setSpecularIntensity    (specular);
    setAmbientColor         (1.f, 1.f, 1.f);
    setDiffuseColor         (1.f, 1.f, 1.f);
    setSpecularColor        (1.f, 1.f, 1.f);
}


inline void Light::computLightComponent(ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition, const Vec3& position, const Material* mat, E_LightAlgorythm lightA) const
{
    ColorRGBA colorIntensityDiffuse = colorIntensity;
    computAmbiantComponent          (colorIntensity, mat);

    Vec3 normalPosLightWithObj = (position_ - position).getNormalize();

    float cosTeta = normalPosLightWithObj.dot_product(normal);
	if (cosTeta < 0.f)
		return;


    ColorRGBA colorIntensitySpec {};

    Vec3 Viewer = (viewerPosition - position).getNormalize();
    computDiffuseComponent      (colorIntensityDiffuse, normal, cosTeta, mat);
 

    if (lightA == E_LightAlgorythm::PHONG)
    {
	    computSpecularPhong    (colorIntensitySpec, normal, Viewer, mat->lightComp_.shininess, normalPosLightWithObj, mat);	
    }
    else if (lightA == E_LightAlgorythm::BLINN_PHONG)
    {
	    computSpecularBlinnPhong    (colorIntensitySpec, normal, Viewer, mat->lightComp_.shininess, cosTeta, normalPosLightWithObj, mat);
    }
	
    float alpha = colorIntensity.a;
    colorIntensity = colorIntensity + colorIntensityDiffuse + colorIntensitySpec;
    colorIntensity.a = alpha;
}

inline void Light::setPosition(math::Vec3 pos) noexcept
{
    position_ = pos;
    normalizePosition_ = pos.getNormalize();
}

inline void Light::setAmbientIntensity(float ambientCompo) noexcept
{
    assert(ambientCompo <= 1.f && ambientCompo >= 0.f);
    ambientComponent_.ki = ambientCompo;
}

inline void Light::setAmbientColor (float r, float g, float b)		noexcept
{
    assert(r <= 1.f && r >= 0.f);
    assert(g <= 1.f && g >= 0.f);
    assert(b <= 1.f && b >= 0.f);

    ambientComponent_.kr = r;
    ambientComponent_.kg = g;
    ambientComponent_.kb = b;  
}

inline void Light::setDiffuseIntensity(float diffuseCompo) noexcept
{
    assert(diffuseCompo <= 1.f && diffuseCompo >= 0.f);
    diffuseComponent_.ki = diffuseCompo;
}

inline void Light::setDiffuseColor (float r, float g, float b)		noexcept
{
    assert(r <= 1.f && r >= 0.f);
    assert(g <= 1.f && g >= 0.f);
    assert(b <= 1.f && b >= 0.f);

    diffuseComponent_.kr = r;
    diffuseComponent_.kg = g;
    diffuseComponent_.kb = b;  
}

inline void Light::setSpecularIntensity(float specularCompo) noexcept
{
    assert(specularCompo <= 1.f && specularCompo >= 0.f);
    specularComponent_.ki = specularCompo;
}

inline void Light::setSpecularColor (float r, float g, float b) noexcept
{
    assert(r <= 1.f && r >= 0.f);
    assert(g <= 1.f && g >= 0.f);
    assert(b <= 1.f && b >= 0.f);

    specularComponent_.kr = r;
    specularComponent_.kg = g;
    specularComponent_.kb = b;  
}

inline void Light::computAmbiantComponent     (ColorRGBA& colorIntensity, const Material* mat) const
{
    colorIntensity.r *= ambientComponent_.kr * ambientComponent_.ki * mat->lightComp_.Ka.r;
    colorIntensity.g *= ambientComponent_.kg * ambientComponent_.ki * mat->lightComp_.Ka.g;
    colorIntensity.b *= ambientComponent_.kb * ambientComponent_.ki * mat->lightComp_.Ka.b;
}

inline void Light::computDiffuseComponent     (ColorRGBA& colorIntensity, const math::Vec3& normal, float cosTeta, const Material* mat) const
{
    colorIntensity.r *= (diffuseComponent_.kr * diffuseComponent_.ki * mat->lightComp_.Kd.r * cosTeta);
    colorIntensity.g *= (diffuseComponent_.kg * diffuseComponent_.ki * mat->lightComp_.Kd.g * cosTeta);
    colorIntensity.b *= (diffuseComponent_.kb * diffuseComponent_.ki * mat->lightComp_.Kd.b * cosTeta);
}

inline void Light::computSpecularBlinnPhong     (ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition,
                                                                    float shininessCoef, float cosTeta, const Vec3& normalPosLightWithObj, const Material* mat)  const
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


    float powCosGamCoefShini255WithIntensity = powf(rst, shininessCoef) * 255 * specularComponent_.ki;

    colorIntensity.r = specularComponent_.kr * mat->lightComp_.Ks.r * powCosGamCoefShini255WithIntensity;
    colorIntensity.g = specularComponent_.kg * mat->lightComp_.Ks.g * powCosGamCoefShini255WithIntensity;
    colorIntensity.b = specularComponent_.kb * mat->lightComp_.Ks.b * powCosGamCoefShini255WithIntensity;
}

inline void Light::computSpecularPhong     (ColorRGBA& colorIntensity, const math::Vec3& normal, const Vec3& viewerPosition, 
                                                                    float shininessCoef, const Vec3& normalPosLightWithObj, const Material* mat)  const
{
    math::Vec3 reflexionR   = 2 * normal.dot_product(normalPosLightWithObj) * normal - normalPosLightWithObj;

    // Dot product of reflexionR and the position of the camera
    float cosGamma = reflexionR.dot_product(viewerPosition.getNormalize());

    if (cosGamma < 0.f)
        cosGamma = 0.f;

    float powCosGamCoefShini255WithIntensity = powf(cosGamma, shininessCoef) * 255 * specularComponent_.ki;

    colorIntensity.r = specularComponent_.kr * mat->lightComp_.Ks.r * powCosGamCoefShini255WithIntensity;
    colorIntensity.g = specularComponent_.kg * mat->lightComp_.Ks.g * powCosGamCoefShini255WithIntensity;
    colorIntensity.b = specularComponent_.kb * mat->lightComp_.Ks.b * powCosGamCoefShini255WithIntensity;
}