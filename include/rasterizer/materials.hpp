#ifndef _MATERIALS_H
#define _MATERIALS_H

#include <memory>
#include <vector>
#include "color.hpp"
#include "texture.hpp"

class Materials
{
public:
    Materials();
	Materials(const Materials& other) = default;
    ~Materials() = default;

    #pragma region constructor/destructor

    #pragma endregion //!constructor/destructor

	#pragma region methods

	#pragma endregion //!methods

	#pragma region accessor


    ColorRGBA                       getColor() noexcept                         { return color_;}
    const ColorRGBA                 getColor() const noexcept                   { return color_;}

    shared_ptr<Texture>	           	getTexture() noexcept                       { return pTexture_;}
    const shared_ptr<Texture>	   	getTexture() const noexcept                 { return pTexture_;}

	const float						getAlpha()	const noexcept					{ return alpha_;}
	float							getAlpha()	noexcept						{ return alpha_;}

	#pragma endregion //!accessor

	#pragma region mutator

	// This function allow to integret texture in entity. Texture must be shared ptr initilize outside 
	// with make shared to don't load multiple same texture
	void setTexture (shared_ptr<Texture>& pTexture)	noexcept   					{pTexture_ = pTexture;};
	void setColor (ColorRGBA& color);
	void setAlpha (float alpha);


	#pragma endregion //!mutator

	#pragma region operator

	#pragma endregion //!operator

	#pragma region convertor

	#pragma endregion //!convertor

protected:

	#pragma region attribut
    ColorRGBA               color_;
    shared_ptr<Texture>		pTexture_; //texture of entity. Nullptr if texture doesn't have any texture.
	float					alpha_ = 1;

	#pragma endregion //!attribut

	#pragma region static attribut

	#pragma endregion //! static attribut

	#pragma region methods

	#pragma endregion //!methods

	private:
};

#endif //_MATERIALS_H