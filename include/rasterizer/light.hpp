#ifndef _LIGHT_H
#define _LIGHT_H

#include "vec3.hpp"

class Light
{
public:
    Light()             =  default;
    Light(math::Vec3&, float, float, float);

    // Copy constructor
    Light(const Light& other);

    virtual ~Light()    = default;

    /*----------*/
	/* accessor */
	/*----------*/

    const math::Vec3& 		getPosition             () const throw()    { return position_;}
	math::Vec3& 			getPosition		        () throw()          { return position_;}

    const float& 		    getAmbientComponent		() const throw()    { return ambientComponent_;}
	float& 				    getAmbientComponent		() throw()          { return ambientComponent_;}

    const float& 		    getDiffuseComponent		() const throw()    { return diffuseComponent_;}
	float& 				    getDiffuseComponent		() throw()          { return diffuseComponent_;}

    const float& 		    getSpecularComponent	() const throw()    { return specularComponent_;}
	float& 				    getSpecularComponent	() throw()          { return specularComponent_;}

    /*----------*/
	/* mutator  */
	/*----------*/

    void 		            setPosition				(math::Vec3 pos)					noexcept;
	void 		            setAmbientComponent     (float ambientCompo)				noexcept;
	void 		            setDiffuseComponent     (float diffuseCompo)				noexcept;
    void 		            setSpecularComponent	(float specularCompo)				noexcept;


protected:
    math::Vec3  position_;
    float       ambientComponent_;
    float       diffuseComponent_;
    float       specularComponent_;

private:

};

#endif //_LIGHT_H