#ifndef _MATERIALS_H
#define _MATERIALS_H

#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include "color.hpp"
#include "texture.hpp"
#include "light.hpp"
#include "tiny_obj_loader.h"

using namespace tinyobj;

class Materials
{
public:

    #pragma region constructor/destructor

	Materials();
	//Materials(real_t a, real_t d, real_t s);
	Materials(const Materials& other) = default;
    ~Materials() = default;

    #pragma endregion //!constructor/destructor

	#pragma region methods

	// Load the file mtl in a global container, if doesn't exist ->assert
	static void addMaterial(const char* pathMtl); 

	#pragma endregion //!methods

	#pragma region accessor


    ColorRGB                       						getColor()		noexcept		{ return color_;}
    const ColorRGB                 						getColor()		const noexcept	{ return color_;}

    Texture*	           								getTexture()	noexcept		{ return pTexture_;}
    const Texture*	   									getTexture()	const noexcept	{ return pTexture_;}

	const float											getAlpha()		const noexcept	{ return alpha_;}
	float												getAlpha()		noexcept		{ return alpha_;}

	/*const std::map<std::string, unique_ptr<Materials>>	getMaterial()	const noexcept	{ return pMaterial_;}
	std::map<std::string, unique_ptr<Materials>>		getMaterial()	noexcept		{ return pMaterial_;}

	const real_t& 								getAmbientComponent()	const noexcept	{ return ambientComponent_[3];}
    real_t& 									getAmbientComponent()	noexcept		{ return ambientComponent_[3];}

    const real_t& 								getDiffuseComponent()	const noexcept	{ return diffuseComponent_[3];}
    real_t& 									getDiffuseComponent()	noexcept		{ return diffuseComponent_[3];}

    const real_t& 								getSpecularComponent()	const noexcept	{ return specularComponent_[3];}
    real_t& 									getSpecularComponent()	noexcept		{ return specularComponent_[3];}*/

	#pragma endregion //!accessor

	#pragma region static method

	// Return a pointer to the indicated material, if doesn't exist -> assert
	//static Materials* getMaterial(std::string id_material); 

	#pragma endregion

	#pragma region mutator

	// This function allow to integret texture in entity. Texture must be shared ptr initilize outside 
	// with make shared to don't load multiple same texture
	void setTexture (Texture* pTexture)	noexcept   			{	pTexture_	= pTexture;};
	void setColor	(ColorRGB& color);
	void setAlpha	(float alpha);

	/*void setAmbient (real_t kr, real_t kg, real_t kb)		{	ambientComponent_[0] = kr; 
																ambientComponent_[1] = kg;  
																ambientComponent_[2] = kb;};

	void setDiffuse	(real_t kr, real_t kg, real_t kb)		{	diffuseComponent_[0] = kr;
																diffuseComponent_[1] = kg;
																diffuseComponent_[2] = kb;};

	void setSpecular(real_t kr, real_t kg, real_t kb)		{	specularComponent_[0] = kr;
																specularComponent_[1] = kg;
																specularComponent_[2] = kb;};*/

	#pragma endregion //!mutator

	#pragma region operator

	#pragma endregion //!operator

	#pragma region convertor

	#pragma endregion //!convertor

	//static std::map<std::string, unique_ptr<Materials>>		pMaterial_; // Library of Materials (.mtl)

protected:

	#pragma region attribut
    ColorRGB               									color_;
    Texture*												pTexture_;	// Texture of entity. 
																		// Nullptr if texture doesn't have any texture.
	float													alpha_ = 1; // Used for the Alpha Blending

	/*real_t													ambientComponent_[3];
    real_t	       											diffuseComponent_[3];
    real_t	       											specularComponent_[3];*/

	#pragma endregion //!attribut

	#pragma region static attribut

	#pragma endregion //! static attribut

	#pragma region methods

	#pragma endregion //!methods

	private:
};

#endif //_MATERIALS_H