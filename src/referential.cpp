#include "referential.hpp"
#include "vertex.hpp"
#include "rasterizer.hpp"
#include "entity.hpp"

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
	child.		updateTRSMat();		//update TRS matrix of each of his child because of the new dependance.
}

Vertex convertVertexLocalToGlobalAndApplyProjection(Renderer& ren, Vertex vertex, const Mat4 &projectionMatrix, const Mat4 &TRSMat, const math::Mat4& invertCam)
{
    //Aplly transformation and projection to get vector in 4D
    Vec4 clipBoard = TRSMat * vertex.position_;
	clipBoard = invertCam * clipBoard;
    
    clipBoard = projectionMatrix * clipBoard;

    //convert vector in 4D to 3D this homogenize
    if (clipBoard.w != 0.f && clipBoard.w != 1.f)
    {
	    clipBoard.homogenize();
    }

    //adapte vertex to 2D
    vertex.position_.x = static_cast<float>(((clipBoard.x / 5) + 1) * 0.5f * ren.width());
    vertex.position_.y = static_cast<float>(ren.heigth() - ((clipBoard.y / 5) + 1) * 0.5 * ren.heigth());
    vertex.position_.z = clipBoard.z;

    vertex.normal_ = (TRSMat * vertex.normal_).xyz;
    vertex.normal_.normalize();

    return vertex;
}

void 		Referential3D::displayAxis 	(Renderer& ren, const math::Mat4& projectionMatrix, const math::Mat4& invertCam) const noexcept
{
	Vertex origin (0.f, 0.f, 0.f);
	origin = convertVertexLocalToGlobalAndApplyProjection(ren, origin, projectionMatrix, TRSMat_, invertCam);
	origin.position_.z = 0.01f;

	Vertex axisX = {1.f, 0.f, 0.f};
	axisX = convertVertexLocalToGlobalAndApplyProjection(ren, axisX, projectionMatrix, TRSMat_, invertCam);
	axisX.position_.z = 0.01f;

	Vertex axisY = {0.f, 1.f, 0.f};
	axisY = convertVertexLocalToGlobalAndApplyProjection(ren, axisY, projectionMatrix, TRSMat_, invertCam);
	axisY.position_.z = 0.01f;

	Vertex axisZ = {0.f, 0.f, 1.f};
	axisZ = convertVertexLocalToGlobalAndApplyProjection(ren, axisZ, projectionMatrix, TRSMat_, invertCam);
	axisZ.position_.z = 0.01f;

	Rasterizer::setColor4ub(255, 0, 0, 255);
	Rasterizer::drawLine(ren, axisX, origin); // (Ox)
	Rasterizer::setColor4ub(0, 255, 0, 255);
	Rasterizer::drawLine(ren, axisY, origin); // (Oy)
	Rasterizer::setColor4ub(0, 0, 255, 255);
	Rasterizer::drawLine(ren, axisZ, origin); // (Oz)
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

void		Referential3D::rotateArroundPointY (math::Vec3 point, float rot) noexcept
{
	TRSMat_ = 	Mat4::createTranslationMatrix (origin_) *
				Mat4::createTranslationMatrix (-point) *
				Mat4::createYRotationMatrix	  (rot) *
				Mat4::createTranslationMatrix (point) * 
				Mat4::createScaleMatrix (scale_);
}

void		Referential3D::rotateArroundAxis (math::Vec3 rVec, float rot) noexcept
{
/*	TRSMat_ = 	Mat4::createTranslationMatrix (origin_) *
				Mat4::createRotationMatrixArroundVec(rVec, rot) *
				Mat4::createScaleMatrix (scale_);*/
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