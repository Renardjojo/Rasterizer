#ifndef _LIGHT_H
#define _LIGHT_H

#include "vec3.hpp"

class Light
{
public:

       #pragma region constructor/destructor

        Light()             =  default;
        Light(math::Vec3&, float, float, float);

        // Copy constructor
        Light(const Light& other);

        virtual ~Light()    = default;

        #pragma endregion //!constructor/destructor

        #pragma region methods
        #pragma endregion //!methods

        #pragma region static methods
        #pragma endregion //!static methods

        #pragma region accessor

        const math::Vec3& 		getPosition             () const throw()    { return position_;}
        math::Vec3& 			getPosition		        () throw()          { return position_;}

        const float& 		    getAmbientComponent		() const throw()    { return ambientComponent_;}
        float& 				    getAmbientComponent		() throw()          { return ambientComponent_;}

        const float& 		    getDiffuseComponent		() const throw()    { return diffuseComponent_;}
        float& 				    getDiffuseComponent		() throw()          { return diffuseComponent_;}

        const float& 		    getSpecularComponent	() const throw()    { return specularComponent_;}
        float& 				    getSpecularComponent	() throw()          { return specularComponent_;}

        #pragma endregion //!accessor

        #pragma region mutator

        void 		            setPosition				(math::Vec3 pos)					noexcept;
        void 		            setAmbientComponent     (float ambientCompo)				noexcept;
        void 		            setDiffuseComponent     (float diffuseCompo)				noexcept;
        void 		            setSpecularComponent	(float specularCompo)				noexcept;

        #pragma endregion //!mutator

        #pragma region operator
        #pragma endregion //!operator

        #pragma region convertor
        #pragma endregion //!convertor

    protected:

        #pragma region attribut

        math::Vec3  position_;
        float       ambientComponent_;
        float       diffuseComponent_;
        float       specularComponent_;

        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods
        #pragma endregion //!methods

private:

};

#endif //_LIGHT_H