#ifndef _REFERENTIAL_3D_H
#define _REFERENTIAL_3D_H

#include <iostream>
#include <string>
#include <vector>
#include "mat4.hpp"
#include "vec3.hpp"
#include "texture.hpp"

typedef class Referential3D
{
	public:

		#pragma region constructor/destructor

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
		 *
		 * return (type ):
		 *
		 * brief : LValue constructor to init local referential with dependance. Else init world ref without argument.
		 */					
		Referential3D 	(	const char* 			name, 
							const math::Vec3& 		origin, 
							const math::Vec3& 		orientation, 
							const math::Vec3& 		scale, 
							Referential3D& 			dependance);

		//Like constructor upper but with Rvalue to move attribut for more optimisation
		Referential3D 	(	const char* 			name, 
							const math::Vec3&& 		origin, 
							const math::Vec3&& 		orientation, 
							const math::Vec3&& 		scale, 
							Referential3D& 			dependance);

		//copy constructor
		Referential3D 	(const Referential3D& other);
		~Referential3D 	() = default;

		#pragma endregion constructor/destructor

		#pragma region methods

		//this function add to referential child matrix. Each child matrix depende of parent referential.
		void 		addChildReferential (Referential3D& child) 	noexcept;

		// few function to display entity of ref in function of his TRS matrix.
		void 		displayAxis 		(Texture& RenBuffer)	const noexcept;

		#pragma endregion //!methods

		#pragma region static methods
		#pragma endregion //!static methods

		#pragma region accessor

		const std::string& 				getName					()	const noexcept	{ return name_;}
		const math::Mat4&				getTRSMatrix			()	const noexcept	{ return TRSMat_;}
		const vector<Referential3D*>&	getChild				()	const noexcept	{ return childRef_;}
		const Referential3D*			getpParent				()	const noexcept	{ return parentRef_;}
		const math::Vec3&				getLocalOrigin			()	const noexcept	{ return origin_;}
		const math::Vec3&				getLocalOrientation		()	const noexcept	{ return orientation_;}
		const math::Vec3&				getLocalScale			()	const noexcept	{ return scale_;}

		#pragma endregion //!accessor

		#pragma region mutator

		//few function to change TRS matrix. Update each child ref after changement.
		// Param : this axe X, Y and Z (width, higth and depth). Orientation in rad in indirect referential
		void 		setOrigin				(math::Vec3 tVec)						noexcept;
		void 		setOrientation			(math::Vec3 rVec)						noexcept;
		void 		setScale				(math::Vec3 sVec)						noexcept;

		void 		translate				(math::Vec3 tVec)						noexcept;
		void 		rotate					(math::Vec3 rVec)						noexcept;
		void 		scale					(math::Vec3 sVec)						noexcept;

		#pragma endregion //!mutator

		#pragma region operator
		#pragma endregion //!operator

		#pragma region convertor
		#pragma endregion //!convertor

	protected:

		#pragma region attribut

		std::string 				name_;			//name of ref
		math::Vec3					origin_; 		//Local origin in parent ref
		math::Vec3					orientation_; 	//Local Euler angle arround axis Ox, Oy and Oz
		math::Vec3					scale_; 		//Local coef scale in x, y and z
	
		vector<Referential3D*>		childRef_;		//List of child referential
		const Referential3D*		parentRef_;		//dependant referential

		math::Mat4					TRSMat_;		//global TRS matrix (translation/Rotation/Scale), comput with mother ref. Allow to pass from local to global

		#pragma endregion //!attribut

		#pragma region static attribut
		#pragma endregion //! static attribut

		#pragma region methods

		//update the TRS matrix in function of his origin, euler angle and scale. 
		//TRS Mat must be update if there component change.
		//This function update each dependent referential TRS Matrix.
		//This function use in parameter the TRS matrix of his parent. So, world nether use this function, because is nether modifie.
		void 		updateTRSMat		() 			noexcept;

		#pragma endregion //!methods

	private:

} Ref3; // Give abbreviated name

//debug function. Matrix TRS is display with prescision of 3 number befor coma.
std::ostream& 	operator<<		(std::ostream& out, const Ref3& ref);

#endif // _REFERENTIAL_3D_H