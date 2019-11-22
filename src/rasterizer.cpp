#include <utility>
#include "rasterizer.hpp"

float min(float value1, float value2)
{
    if (value2 <= value1)
        return value2;
    else
        return value1;
}

float max(float value1, float value2)
{
    if (value1 >= value2)
        return value1;
    else
        return value2;
}

Vertex projectVertex(const Vertex &vec)
{
    Vertex newVer;
    newVer.position_.x_ = ((vec.position_.x_ / 5) + 1) * 0.5 * 800;
    newVer.position_.y_ = 600 - ((vec.position_.y_ / 5) + 1) * 0.5 * 600;

    return newVer;
}

float crossProduct(Vertex& v1, Vertex& v2)
{
    return v1.position_.x_ * v2.position_.y_ - v1.position_.y_ * v2.position_.x_;
}

void Rasterizer::drawLine(Texture &target, Vertex &v1, Vertex &v2)
{
    Vertex pV1 = v1;
    Vertex pV2 = v2;

    // Bresenham's line algorithm
    const bool steep = (fabs(pV2.position_.y_ - pV1.position_.y_) > fabs(pV2.position_.x_ - pV1.position_.x_));

    if (steep)
    {
        std::swap(pV1.position_.x_, pV1.position_.y_);
        std::swap(pV2.position_.x_, pV2.position_.y_);
    }

    if (pV1.position_.x_ > pV2.position_.x_)
    {
        std::swap(pV1.position_.x_, pV2.position_.x_);
        std::swap( pV1.position_.y_, pV2.position_.y_);
    }

    const float dx = pV2.position_.x_ - pV1.position_.x_;
    const float dy = fabs(pV2.position_.y_ -  pV1.position_.y_);

    float error = dx / 2.0f;
    const int ystep = ( pV1.position_.y_ < pV2.position_.y_) ? 1 : -1;
    int y = (int) pV1.position_.y_;

    const int maxX = (int)pV2.position_.x_;

    for (int x = (int)pV1.position_.x_; x < maxX; x++)
    {
        if (steep)
        {
            target.setPixelColor(y, x, {0, 255, 0, 255});
        }
        else
        {
            target.setPixelColor(x, y, {0, 255, 0, 255});
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Rasterizer::drawTriangle(Texture &target, const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    // Get the bounding box of the triangle
    float maxX, minX, maxY, minY = 0;

    maxX = max(max(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    minX = min(min(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    maxY = max(max(v1.position_.y_, v2.position_.y_), v3.position_.y_);
    minY = min(min(v1.position_.y_, v2.position_.y_), v3.position_.y_);

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x_ - v1.position_.x_, v2.position_.y_ - v1.position_.y_, 0};
    Vertex vs2 = {v3.position_.x_ - v1.position_.x_, v3.position_.y_ - v1.position_.y_, 0};

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x_, y - v1.position_.y_, 0};

            float crossproductV1V2 = crossProduct(vs1, vs2);
            if (crossproductV1V2 == 0.f)
                continue;

            float w1 = crossProduct(q, vs2) / crossproductV1V2;
            float w2 = crossProduct(vs1, q) / crossproductV1V2;
            float w3 = 1.f - w1 - w2;

            // If inside of the triangle
            if ((w1 >= 0) && (w2 >= 0) && (w3 >= 0))
            {
              //  float depth = (v1.position_.z_ +  v2.position_.z_ + v3.position_.z_) / 3;
             //   float depth = 1.f;
                 target.setPixelColor(x, y, {static_cast<ubyte>(w1 * 255.f),
                                            static_cast<ubyte>(w2 * 255.f),
                                            static_cast<ubyte>(w3 * 255.f),
                                            255}, 1.f);
            }
        }
    }
}
