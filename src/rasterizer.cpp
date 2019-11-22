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

void Rasterizer::drawLine(Texture &target, Vertex &v1, Vertex &v2)
{
    Vertex pV1 = projectVertex(v1);
    Vertex pV2 = projectVertex(v2);

    float dx = pV2.position_.x_ - pV1.position_.x_;
    float dy = pV2.position_.y_ - pV1.position_.y_;

    assert(dx == NULL);

    float maxX = max(pV1.position_.x_, pV2.position_.x_);
    float minX = min(pV1.position_.x_, pV2.position_.x_);

    int y = 0;
    for (int x = minX; x < maxX; x++)
    {
        y = pV1.position_.y_ + dy * (x - pV1.position_.x_) / dx;

        target.setPixelColor(x, y, {0, 255, 0, 255});
    }
}

float dotProduct(Vertex &v1, Vertex &v2)
{
    return v1.position_.x_ * v2.position_.y_ - v1.position_.y_ * v2.position_.x_;
}

void Rasterizer::drawTriangle(Texture &target, const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    std::cout << v1.position_ << "  " << v2.position_ << "  " << v3.position_ << std::endl;

    Vertex pV1 = projectVertex(v1);
    Vertex pV2 = projectVertex(v2);
    Vertex pV3 = projectVertex(v3);

    // Get the bounding box of the triangle
    float maxX, minX, maxY, minY = 0;

    maxX = max(max(pV1.position_.x_, pV2.position_.x_), pV3.position_.x_);
    minX = min(min(pV1.position_.x_, pV2.position_.x_), pV3.position_.x_);
    maxY = max(max(pV1.position_.y_, pV2.position_.y_), pV3.position_.y_);
    minY = min(min(pV1.position_.y_, pV2.position_.y_), pV3.position_.y_);

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {pV2.position_.x_ - pV1.position_.x_, pV2.position_.y_ - pV1.position_.y_, 0};
    Vertex vs2 = {pV3.position_.x_ - pV1.position_.x_, pV3.position_.y_ - pV1.position_.y_, 0};

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - pV1.position_.x_, y - pV1.position_.y_, 0};

            float s = dotProduct(q, vs2) / dotProduct(vs1, vs2);
            float t = dotProduct(vs1, q) / dotProduct(vs1, vs2);

            // If inside of the triangle
            if ((s >= 0) && (t >= 0) && (s + t <= 1))
            {
                target.setPixelColor(x, y, {static_cast<ubyte>(s * 255.f), static_cast<ubyte>(t * 255.f), static_cast<ubyte>((1.f - s - t) * 255.f), 255});
            }
        }
    }
}
