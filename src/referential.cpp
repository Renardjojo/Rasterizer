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

Vertex convertVertexLocalToGlobalAndApplyProjection(Renderer& ren, Vertex vertex, const Mat4 &projectionMatrix, const Mat4 &TRSMat)
{
    //Aplly transformation and projection to get vector in 4D
    Vec4 clipBoard = (Matrix)TRSMat * vertex.position_;
    
    clipBoard = (Matrix)projectionMatrix * clipBoard;

    //convert vector in 4D to 3D this homogenize
    if (clipBoard.w_ != 0.f && clipBoard.w_ != 1.f)
    {
       clipBoard.homogenize();
    }

    //adapte vertex to 2D
    vertex.position_.x_ = static_cast<float>(((clipBoard.x_ / 5) + 1) * 0.5f * ren.width());
    vertex.position_.y_ = static_cast<float>(ren.heigth() - ((clipBoard.y_ / 5) + 1) * 0.5 * ren.heigth());
    vertex.position_.z_ = clipBoard.z_;

   // std::cout << vertex.position_.x_ << "   "  << vertex.position_.z_ << std::endl;

    Vec4 vecN(vertex.normal_);
    vecN = TRSMat * vecN;
    vertex.normal_  = {vecN.x_, vecN.y_, vecN.z_};
    vertex.normal_.normalize();

    return vertex;
}

void 		Referential3D::displayAxis 	(Renderer& ren, const math::Mat4& projectionMatrix) const noexcept
{
	Vertex origin (0.f, 0.f, 0.f);
	origin = convertVertexLocalToGlobalAndApplyProjection(ren, origin, projectionMatrix, TRSMat_);

	Vertex axisX = {1.f, 0.f, 0.f};
	axisX = convertVertexLocalToGlobalAndApplyProjection(ren, axisX, projectionMatrix, TRSMat_);

	Vertex axisY = {0.f, 1.f, 0.f};
	axisY = convertVertexLocalToGlobalAndApplyProjection(ren, axisY, projectionMatrix, TRSMat_);

	Vertex axisZ = {0.f, 0.f, 1.f};
	axisZ = convertVertexLocalToGlobalAndApplyProjection(ren, axisZ, projectionMatrix, TRSMat_);

	Rasterizer::setColor4ub(255, 0, 0, 255);
	Rasterizer::drawLine(ren, axisX, origin); // (Ox)
	Rasterizer::setColor4ub(0, 255, 0, 255);
	Rasterizer::drawLine(ren, axisY, origin); // (Oy)
	Rasterizer::setColor4ub(0, 0, 255, 255);
	Rasterizer::drawLine(ren, axisZ, origin); // (Oz)
/*
	Vertex origin (origin_.x_, origin_.y_, origin_.z_);
	Vec4 vecO(origin.position_);
	origin = {((vecO.x_ / 5) + 1) * 0.5f * ren.width(), 
			(ren.heigth() - (( vecO.y_/ 5) + 1) * 0.5f *ren.heigth()), vecO.z_};
	
	Vertex axisX = {1.f, 0.f, 0.f};
	Vec4 vec(axisX.position_);
	vec = TRSMat_ * vec;
	axisX = {((vec.x_ / 5) + 1) * 0.5f * ren.width(), 
			(ren.heigth() - (( vec.y_/ 5) + 1) * 0.5f *ren.heigth()), vec.z_};
	
	Vertex axisY = {0.f, 1.f, 0.f};
	Vec4 vec1(axisY.position_);
	vec1 = TRSMat_ * vec1;
	axisY = {((vec1.x_ / 5) + 1) * 0.5f * ren.width(), 
			(ren.heigth() - (( vec1.y_/ 5) + 1) * 0.5f *ren.heigth()), vec1.z_};

	Vertex axisZ = {0.f, 0.f, 1.f};
	Vec4 vec2(axisZ.position_);
	vec2 = TRSMat_ * vec2;
	axisZ = {((vec2.x_ / 5) + 1) * 0.5f * ren.width(), 
			(ren.heigth() - (( vec2.y_/ 5) + 1) * 0.5f *ren.heigth()), vec2.z_};

	Rasterizer::setColor4ub(255, 0, 0, 255);
	Rasterizer::drawLine(ren, axisX, origin); // (Ox)
	Rasterizer::setColor4ub(0, 255, 0, 255);
	Rasterizer::drawLine(ren, axisY, origin); // (Oy)
	Rasterizer::setColor4ub(0, 0, 255, 255);
	Rasterizer::drawLine(ren, axisZ, origin); // (Oz)*/
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