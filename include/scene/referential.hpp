#ifndef _REFERENTIAL_3D_H
#define _REFERENTIAL_3D_H

#include <iostream>
#include <string>
#include <vector>
#include "mat4.hpp"
#include "vec3.hpp"

typedef struct S_ColorRGBA
{ 
	float r, g, b, a;

} ColorRGBA;

typedef enum   E_TypePrimitive
{
	NONE 	= -1,
	BOX 	= 0,
	SPHERE 	= 1,
	CYLINDRE= 2

} TypePrimitive;

typedef class Referential3D
{
	public:

		//default ref init "World" referential
		Referential3D 	();

		/**
		 * function : Referential3D
		 *
		 * parameter : 
		 *		const char* name					: name of the referential
		 *		const math::Vec3& origin			: origin of local referential in axe X, Y and Z (width, higth and depth)
		 *		const math::Vec3& orientation		: orentiation of local ref in radian in axe X, Y and Z
		 *		const math::Vec3& scale				: Homotetie of local ref in axe X, Y and Z (width, higth and depth)
		 *		const Referential3D& dependance		: Dependance referential. Use reference to world referential to create entity in world.
		 *		E_TypePrimitive	primitive			: Primitive to display at this referential. By default don't display primitve
		 *		const struct S_Color& color 		: Color of primitive display if it is. By default in black;
		 *
		 * return (type ):
		 *
		 * brief : LValue constructor to init local referential with dependance. Else init world ref without argument.
		 */					
		Referential3D 	(	const char* 			name, 
							const math::Vec3& 		origin, 
							const math::Vec3& 		orientation, 
							const math::Vec3& 		scale, 
							Referential3D& 			dependance,
							E_TypePrimitive			primitive	= E_TypePrimitive::NONE,
							ColorRGBA 				color 		= {0.f, 0.f, 0.f, 1.f});

		//Like constructor upper but with Rvalue to move attribut for more optimisation
		Referential3D 	(	const char* 			name, 
							const math::Vec3&& 		origin, 
							const math::Vec3&& 		orientation, 
							const math::Vec3&& 		scale, 
							Referential3D& 			dependance,
							E_TypePrimitive			primitive	= E_TypePrimitive::NONE,
							ColorRGBA&& 			color 		= {0.f, 0.f, 0.f, 1.f});

		//copy constructor
		Referential3D 	(const Referential3D& other) = delete; //TODO
		~Referential3D 	() = default;

		 /*----------*/
		/* methode  */
	   /*----------*/
		
		//this function add to referential child matrix. Each child matrix depende of parent referential.
		void 		addChildReferential (Referential3D& child) 	noexcept;

		// few function to display entity of ref in function of his TRS matrix.
		void 		displayAxis 		() 						noexcept;
		void		display				()	const				noexcept;
		
		 /*----------*/
		/* accessor */
	   /*----------*/

		//few function to change TRS matrix. Update each child ref after changement.
		// Param : this axe X, Y and Z (width, higth and depth). Orientation in rad in indirect referential
		void 		setOrigin				(math::Vec3 tVec)						noexcept;
		void 		setOrientation			(math::Vec3 rVec)						noexcept;
		void 		setScale				(math::Vec3 sVec)						noexcept;

		void 		translate				(math::Vec3 tVec)						noexcept; //TODO
		void 		rotate					(math::Vec3 rVec)						noexcept; //TODO
		void 		scale					(math::Vec3 sVec)						noexcept; //TODO

		 /*----------*/
		/* mutator  */
	   /*----------*/

		const std::string& 				getName					()	const noexcept	{ return name_;}
		const math::Mat4&				getTRSMatrix			()	const noexcept	{ return TRSMat_;}
		const vector<Referential3D*>&	getChild				()	const noexcept	{ return childRef_;}
		const Referential3D*			getpParent				()	const noexcept	{ return parentRef_;}

		 /*----------*/
		/* operator */
	   /*----------*/

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

	protected:

		std::string 				name_;			//name of ref
		math::Vec3					origin_; 		//Local origin in parent ref
		math::Vec3					orientation_; 	//Local Euler angle arround axis Ox, Oy and Oz
		math::Vec3					scale_; 		//Local coef scale in x, y and z
	
		ColorRGBA					color_;			//color of primitive between 0.f and 1.f and between 0 and 255 in integer.
		TypePrimitive				typePrimitive_;	//type of primitive support by referential
		vector<Referential3D*>		childRef_;		//List of child referential
		Referential3D*				parentRef_;		//dependant referential

		math::Mat4					TRSMat_;		//global TRS matrix (translation/Rotation/Scale), comput with mother ref. Allow to pass from local to global

		//update the TRS matrix in function of his origin, euler angle and scale. 
		//TRS Mat must be update if there component change.
		//This function update each dependent referential TRS Matrix.
		//This function use in parameter the TRS matrix of his parent. So, world nether use this function, because is nether modifie.
		void 		updateTRSMat		() 			noexcept;

	private:

} Ref3; // Give abbreviated name

//debug function. Matrix TRS is display with prescision of 3 number befor coma.
std::ostream& 	operator<<		(std::ostream& out, const Ref3& ref);

#endif // _REFERENTIAL_3D_H


