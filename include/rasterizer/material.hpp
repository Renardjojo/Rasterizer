#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include "color.hpp"
#include "texture.hpp"
#include "tiny_obj_loader.h"

using namespace tinyobj;

struct LightComponent
{
	struct AmbiantComponent
	{
		float r, g, b;
	} Ka;

	struct DiffuseComponent
	{
		float r, g, b;
	} Kd;

	struct SpecularComponent
	{
		float r, g, b;
	} Ks;

	unsigned int shininess;
};

class Material
{
public:

    #pragma region constructor/destructor

	Material() = default;
	Material(LightComponent&& LightComponent, std::string textureAmbPath, float alpha);
	Material(const Material& other) = default;
    ~Material() = default;

    #pragma endregion //!constructor/destructor

	#pragma region methods

	#pragma endregion //!methods

	#pragma region accessor

	#pragma endregion //!accessor

	#pragma region static method

	// Load the file mtl in a global container, if doesn't exist ->assert
	static std::map<std::string, std::unique_ptr<Material>>::iterator addMaterial(std::string name, LightComponent&& LightComponent, std::string textureAmbPath, float alpha); 
	static std::map<std::string, std::unique_ptr<Material>>::iterator addMaterial(std::string mtlPath);


	// Return a pointer to the indicated material, if doesn't exist -> assert
	static Material* getMaterial(std::string id_material); 

	#pragma endregion

	#pragma region mutator

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