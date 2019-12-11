#ifndef _LIGHT_H
#define _LIGHT_H

#include "vec.hpp"
#include "color.hpp"

typedef struct S_AmbiantComponent
{
    float kr, kg, kb;

} AmbiantComponent;

typedef struct S_DiffuseComponent
{
    float kr, kg, kb;

} DiffuseComponent;

typedef struct S_SpecularComponent
{
    float kr, kg, kb;

} SpecularComponent;

class Light
{
public:

       #pragma region constructor/destructor

        Light()             =  default;
        Light(const math::Vec3&, float, float, float);

        // Copy constructor
        Light(const Light& other) = default;

        virtual ~Light()    = default;

        #pragma endregion //!constructor/destructor

        #pragma region methods

        //This function comput the intensity of pixel in function of ligth coefficient (ambient, diffuse, specular). 
        //Function based on Phong model 
        void computLightComponent(ColorRGBA& colorIntensity, const math::Vec3& normal, const math::Vec3& position, float shininessCoef) const;

        #pragma endregion //!methods

        #pragma region static methods
        #pragma endregion //!static methods

        #pragma region accessor

        const math::Vec3& 	        getPosition             () const noexcept    { return position_;}
        math::Vec3& 		        getPosition		        () noexcept          { return position_;}

        const AmbiantComponent& 	getAmbientComponent		() const noexcept    { return ambientComponent_;}
        AmbiantComponent& 			getAmbientComponent		() noexcept          { return ambientComponent_;}

        const DiffuseComponent& 	getDiffuseComponent		() const noexcept    { return diffuseComponent_;}
        DiffuseComponent& 			getDiffuseComponent		() noexcept          { return diffuseComponent_;}

        const SpecularComponent& 	getSpecularComponent	() const noexcept    { return specularComponent_;}
        SpecularComponent& 			getSpecularComponent	() noexcept          { return specularComponent_;}

        #pragma endregion //!accessor

        #pragma region mutator

        void 		            setPosition				(math::Vec3 pos)					noexcept;
        void 		            setAmbientIntensity     (float ambientCompo)				noexcept;
        void 		            setDiffuseIntensity     (float diffuseCompo)				noexcept;
        void 		            setSpecularIntensity	(float specularCompo)				noexcept;

        #pragma endregion //!mutator

        #pragma region operator
        #pragma endregion //!operator

        #pragma region convertor
        #pragma endregion //!convertor

    protected:

        #pragma region attribut

        math::Vec3              position_;
        math::Vec3              normalizePosition_;
        
        AmbiantComponent        ambientComponent_;
        DiffuseComponent        diffuseComponent_;
        SpecularComponent       specularComponent_;

        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods

        //This function compute the ambiante component of pixel in function of k ambiante
        void    computAmbiantComponent     (ColorRGBA& colorIntensity)                              const;

        //This function compute the diffuse component of pixel in function of k diffuse
        void    computDiffuseComponent     (ColorRGBA& colorIntensity, const math::Vec3& normal, float cosTeta)    const;

        //This function compute the specular component of pixel in function of k specular with the Phong model
        void    computSpecularPhong     (   ColorRGBA& colorIntensity, const math::Vec3& normal,  
                                            float shininessCoef, const math::Vec3& normalPosLightWithObj)        const;

        //This function compute the specular component of pixel in function of k specular with the Blinn-Phong model
        //cos Teta represent the dot product between nromalize vector position and normal. In paramter for more optimisation
        void    computSpecularBlinnPhong     (  ColorRGBA& colorIntensity, const math::Vec3& normal, 
                                                float shininessCoef, float cosTeta, const math::Vec3& normalPosLightWithObj)        const;                                                                
    
        //THis function compute the reflexion vector of light in function of his direction and in function of normal of surface
        //cos Teta represent the dot product between nromalize vector position and normal. In paramter for more optimisation
        math::Vec3    getRefectionVector    (const math::Vec3& normal)                              const;

        #pragma endregion //!methods

private:

};

#endif //_LIGHT_H
