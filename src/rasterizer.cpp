#include "rasterizer.hpp"


void Rasterizer::drawLine(Texture& target, Vertex& v1, Vertex& v2)
{
    /*float dx = v2.position_.x_ - v1.position_.x_;
    float dy = v2.position_.y_ - v1.position_.y_;

    float minX = min(v1.position_.x_, v2.position_.x_);

    for (int x = v1.position_.x_; x < v2.position_.x_; x++)
    {

    }*/
}

void Rasterizer::drawTriangle(Texture& target, Vertex& v1, Vertex& v2, Vertex& v3)
{

    projectVertex(v1);
    projectVertex(v2);
    projectVertex(v3);

    // Get the bounding box of the triangle
    float maxX, minX, maxY, minY = 0;

    maxX = max(max(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    minX = min(min(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    maxY = max(max(v1.position_.y_, v2.position_.y_), v3.position_.y_);
    minY = min(min(v1.position_.y_, v2.position_.y_), v3.position_.y_);

    // Spanning vectors of edge (v1,v2) and (v1,v3)
    Vertex vs1 = {v2.position_.x_ - v1.position_.x_, v2.position_.y_ - v1.position_.y_, 0};
    Vertex vs2 = {v3.position_.x_ - v1.position_.x_, v3.position_.y_ - v1.position_.y_, 0};

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            Vertex q = {x - v1.position_.x_, y - v1.position_.y_, 0};
            //Vertex p = {x - v2.position_.x_, y - v2.position_.y_, 0};

            float s = crossProduct(q, vs2) / crossProduct(vs1, vs2);
            float t = crossProduct(vs1, q) / crossProduct(vs1, vs2);
            
            // If inside of the triangle
            if ((s >= 0) && (t >= 0) && (s + t <= 1))
            {
                target.setPixelColor(x, y, {255, 255, 255, 255});
            }
        }
    }
}

float Rasterizer::dotProduct(Vertex& v1, Vertex& v2)
{
    return ((v1.position_.x_ * v2.position_.x_) + (v1.position_.y_ * v2.position_.y_));
}

float Rasterizer::crossProduct(Vertex& v1, Vertex& v2)
{
    return (v1.position_.x_ * v2.position_.y_) / (v2.position_.x_ * v1.position_.y_);
}

float Rasterizer::min(float value1, float value2)
{
    if (value2 <= value1)
        return value2;
    else
        return value1;
}

float Rasterizer::max(float value1, float value2)
{
    if (value1 >= value2)
        return value1;
    else
        return value2;
}

void	Rasterizer::projectVertex		(Vertex& vec)
{
    vec.position_.x_ = ((vec.position_.x_ / 5) + 1) * 0.5 * 1024;
    vec.position_.y_ = 700 - ((vec.position_.y_ / 5) + 1) * 0.5 * 700;
}
