#include "material.hpp"
#include <cassert>
#include <fstream>

using namespace std;

Material::Material(LightComponent&& lc, string textureAmbPath, float alpha)
    :   lightComp_      {{lc.Ka.r, lc.Ka.g, lc.Ka.b}, {lc.Kd.r, lc.Kd.g, lc.Kd.b}, {lc.Ks.r, lc.Ks.g, lc.Ks.b}, lc.shininess},
        pTexture_       (nullptr),
        alpha_          {alpha}
{
    assert(alpha >= 0.f && alpha <= 1.f);

    if (!textureAmbPath.empty())
    {
        pTexture_ = make_unique<Texture>(textureAmbPath.c_str());
    }
}

map<string, unique_ptr<Material>>::iterator Material::addMaterial(string name, LightComponent&& LightComponent, string textureAmbPath, float alpha)
{
    assert(alpha >= 0.f && alpha <= 1.f);

    //auto for std::pair<std::map<std::string, std::unique_ptr<Material>>::iterator, bool>
    auto it = pMaterial_.insert(pair<string, unique_ptr<Material>>(name, make_unique<Material>(move(LightComponent), textureAmbPath, alpha)));

    if (!it.second)
    {
        cerr << __FILE__ << ':' << __LINE__ << ": Warning, material already exist with this name : " << name << endl;
    }

    return it.first;
}

map<string, unique_ptr<Material>>::iterator Material::addMaterial(string mtlPath)
{
    assert(!mtlPath.empty());

    std::vector<tinyobj::material_t> materials;
    std::ifstream matIStream(mtlPath.c_str());
    std::map<std::string, int> material_map;

    tinyobj::LoadMtl(&material_map, &materials, &matIStream, nullptr, nullptr);

	//Load information about material and create materal if doesn't exist
	if (!materials.empty())
	{
		map<string, unique_ptr<Material>>::iterator it = Material::addMaterial(materials.back().name,
										                {{ materials.back().ambient[0] , materials.back().ambient[1] , materials.back().ambient[2]}, 
										                { materials.back().diffuse[0] , materials.back().diffuse[1] , materials.back().diffuse[2]},
						 				                { materials.back().specular[0], materials.back().specular[1], materials.back().specular[2]},
						  				                 static_cast<unsigned int>(materials.back().shininess)},
										                materials.back().ambient_texname.empty() ? "" : "media/picture/" + materials.back().ambient_texname,
										                materials.back().dissolve);

        return it;    
	}
	else
	{
		cerr << __FILE__ << ':' << __LINE__ <<": Error  file .mlt not found or void : " << mtlPath << endl;
        exit(EXIT_FAILURE);
	}
}




Material* Material::getMaterial(string id_material)
{
    assert(!id_material.empty());

    auto search = pMaterial_.find(id_material); //iterator to map

    if (search == pMaterial_.end())
    {
        cerr << __FILE__ << ':' << __LINE__ << ": Warning, material dosn't exist : " << id_material << endl;
        return nullptr;
    }

    return search->second.get();
}

map<string, unique_ptr<Material>>	defaultValueMapMaterial()
{
    map<string, unique_ptr<Material>> m;
    LightComponent l {{1.f, 1.f, 1.f},  {1.f, 1.f, 1.f},  {1.f, 1.f, 1.f}, 16};
    m["Default"] = make_unique<Material>(std::move(l), "", 1.f);
    return m;
}

map<string, unique_ptr<Material>>	Material::pMaterial_ = defaultValueMapMaterial();