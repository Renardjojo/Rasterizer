#ifndef _MATERIALS_H
#define _MATERIALS_H

#include <memory>
#include <vector>
#include "color.hpp"
#include "texture.hpp"

class Materials
{
public:
    Materials(/* args */);
    ~Materials();

    #pragma region constructor/destructor

    #pragma endregion //!constructor/destructor

	#pragma region methods

	#pragma endregion //!methods

	#pragma region accessor


    ColorRGBA                       getColor() noexcept                         { return color_;}
    const ColorRGBA                 getColor() const noexcept                   { return color_;}

    shared_ptr<Texture>	           getTexture() noexcept                        { return pTexture_;}
    const shared_ptr<Texture>	   getTexture() const noexcept                  { return pTexture_;}

	#pragma endregion //!accessor

	#pragma region mutator

	#pragma endregion //!mutator

	#pragma region operator

	#pragma endregion //!operator

	#pragma region convertor

	#pragma endregion //!convertor

protected:

	#pragma region attribut
    ColorRGBA               color_;
    shared_ptr<Texture>		pTexture_;

	#pragma endregion //!attribut

	#pragma region static attribut

	#pragma endregion //! static attribut

	#pragma region methods

	#pragma endregion //!methods

	private:
};

#endif //_MATERIALS_H