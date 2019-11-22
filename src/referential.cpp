#include "referential.hpp"

using namespace math;


Referential3D::Referential3D ()
	:	name_			("World"),
		origin_			({0.f, 0.f, 0.f}),
		orientation_	({0.f, 0.f, 0.f}),
		scale_			({1.f, 1.f, 1.f}),
		childRef_		(),
		parentRef_		(nullptr),
		TRSMat_			()	//constructidentity matrix 
{}

Referential3D::Referential3D (	const char* 			name, 
								const Vec3& 			origin, 
								const Vec3& 			orientation, 
								const Vec3& 			scale, 
								Referential3D& 			dependance)
	:	name_			(name),
		origin_			(origin),
		orientation_	(orientation),
		scale_			(scale),
		childRef_		(),
		parentRef_		(&dependance),
		TRSMat_			()
{
	dependance.addChildReferential((*this));
}

Referential3D::Referential3D (	const char* 			name, 
								const Vec3&& 			origin, 
								const Vec3&&			orientation, 
								const Vec3&& 			scale, 
								Referential3D& 			dependance)
	:	name_			(std::move(name)),
		origin_			(std::move(origin)),
		orientation_	(std::move(orientation)),
		scale_			(std::move(scale)),
		childRef_		(),
		parentRef_		(&dependance),
		TRSMat_			()
{
	dependance.addChildReferential((*this));
}

Referential3D::Referential3D 	(const Referential3D& other) 
	:	name_			(other.getName()),
		origin_			(other.getLocalOrigin()),
		orientation_	(other.getLocalOrientation()),
		scale_			(other.getLocalScale()),
		childRef_		(other.getChild()),
		parentRef_		(other.getpParent()),
		TRSMat_			(other.getTRSMatrix())
{}

void 		Referential3D::addChildReferential (Referential3D& child) noexcept
{
	childRef_.	push_back(&child);
	child.		updateTRSMat();		//update TRS matrix of each of his child because of the new dependace.
}

void 		Referential3D::displayAxis 	(Texture& RenBuffer) 			noexcept
{

}

void 		Referential3D::updateTRSMat	() 			noexcept
{
	if (parentRef_ != nullptr)
		TRSMat_ = parentRef_->getTRSMatrix();

	TRSMat_ = TRSMat_ * Mat4::createTRSMatrix (scale_, orientation_, origin_);	
	for (unsigned int i = 0; i < childRef_.size(); i++)
	{
		childRef_[i]->updateTRSMat();
	}
}

void 		Referential3D::setOrigin (Vec3 tVec) noexcept
{
	origin_	= tVec;
	updateTRSMat();
}

void 		Referential3D::setOrientation (Vec3 rVec) noexcept
{
	orientation_ = rVec;
	updateTRSMat();
}

void 		Referential3D::setScale (Vec3 sVec) noexcept
{
	scale_ = sVec;
	updateTRSMat();
}

void 		Referential3D::translate (math::Vec3 tVec) noexcept
{
	origin_	+= tVec;
	updateTRSMat();
}

void 		Referential3D::rotate (math::Vec3 rVec) noexcept
{
	orientation_ += rVec;
	updateTRSMat();
}

void 		Referential3D::scale (math::Vec3 sVec) noexcept
{
	scale_ += sVec;
	updateTRSMat();
}

std::ostream& 	operator<<(std::ostream& out, const Ref3& ref)
{
	out << ref.getName() << " : " << std::endl << 
	"TRS : " << std::endl << ref.getTRSMatrix() << std::endl << 
	"Parent : " << (ref.getpParent() == nullptr ? "" : ref.getpParent()->getName()) << std::endl << 
	"Child : " << std::endl;

	for (unsigned int i = 0; i < ref.getChild().size(); i++)
	{
		out << "- " << ref.getChild()[i]->getName() << std::endl;
	}

	return out;
}

