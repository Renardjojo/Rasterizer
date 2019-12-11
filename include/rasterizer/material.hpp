#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include "color.hpp"
#include "texture.hpp"
#include "light.hpp"
#include "tiny_obj_loader.h"

using namespace tinyobj;

struct LightComponent
{
	typedef struct AmbiantComponent
	{
		float r, g, b;
	} Ka;

	typedef struct DiffuseComponent
	{
		float r, g, b;
	} Kd;

	typedef struct SpecularComponent
	{
		float r, g, b;
	} Ks;

	unsigned int shiny;
};

class Material
{
public:

    #pragma region constructor/destructor

	Material() = default;
	Material(LightComponent&& LightComponent);
	Material(const Material& other) = default;
    ~Material() = default;

    #pragma endregion //!constructor/destructor

	#pragma region methods

	#pragma endregion //!methods

	#pragma region accessor

	#pragma endregion //!accessor

	#pragma region static method

	// Load the file mtl in a global container, if doesn't exist ->assert
	static void addMaterial(LightComponent&& LightComponent); 

	// Return a pointer to the indicated material, if doesn't exist -> assert
	static const Material* getMaterial(std::string id_material); 

	#pragma endregion

	#pragma region mutator

	// This function allow to integret texture in entity. Texture must be shared ptr initilize outside 
	// with make shared to don't load multiple same texture
	void setTexture (Texture* pTexture)	noexcept   			{	pTexture_	= pTexture;};
	void setColor	(ColorRGB& color);
	void setAlpha	(float alpha);

	#pragma endregion //!mutator

	#pragma region operator

	#pragma endregion //!operator

	#pragma region convertor

	#pragma endregion //!convertor

	LightComponent				lightComp_;
    std::unique_ptr<Texture>	pTexture_;	// Texture of entity. Nullptr if texture doesn't have any texture.
	float						alpha_; // Used for the Alpha Blending

protected:

	#pragma region attribut

	#pragma endregion //!attribut

	#pragma region static attribut

	static std::map<std::string, std::unique_ptr<Material>>		pMaterial_; // Library of materials

	#pragma endregion //! static attribut

	#pragma region methods

	#pragma endregion //!methods

	private:
};

#endif //_MATERIAL_H