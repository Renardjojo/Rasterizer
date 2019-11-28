#include <cmath>
#include <utility>
#include "rasterizer.hpp"
#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"

using namespace math;

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

float crossProduct(const Vertex &v1, const Vertex &v2)
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
        std::swap(pV1.position_.y_, pV2.position_.y_);
    }

    const float dx = pV2.position_.x_ - pV1.position_.x_;
    const float dy = fabs(pV2.position_.y_ - pV1.position_.y_);

    float error = dx / 2.0f;
    const int ystep = (pV1.position_.y_ < pV2.position_.y_) ? 1 : -1;
    int y = (int)pV1.position_.y_;

    const int maxX = (int)pV2.position_.x_;

    for (int x = (int)pV1.position_.x_; x < maxX; x++)
    {
        if (steep)
        {
            target.setPixelColor(y, x, color);
        }
        else
        {
            target.setPixelColor(x, y, color);
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
    //float maxZ = -5;
    // float minZ = +5;

    maxX = max(max(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    minX = min(min(v1.position_.x_, v2.position_.x_), v3.position_.x_);
    maxY = max(max(v1.position_.y_, v2.position_.y_), v3.position_.y_);
    minY = min(min(v1.position_.y_, v2.position_.y_), v3.position_.y_);

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x_ - v1.position_.x_, v2.position_.y_ - v1.position_.y_, 0.f};
    Vertex vs2 = {v3.position_.x_ - v1.position_.x_, v3.position_.y_ - v1.position_.y_, 0.f};

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x_, y - v1.position_.y_, 0.f};

            float crossproductV1V2 = crossProduct(vs1, vs2);
            if (crossproductV1V2 == 0.f)
                continue;

            float w1 = crossProduct(q, vs2) / crossproductV1V2;
            float w2 = crossProduct(vs1, q) / crossproductV1V2;
            float w3 = 1.f - w1 - w2;

            // If inside of the triangle
            if ((w1 >= 0) && (w2 >= 0) && (w3 >= 0))
            {
                float depth = (w1 * v2.position_.z_ + w2 * v3.position_.z_ + w3 * v1.position_.z_);

                //maxZ = depth > maxZ ? depth : maxZ;
                //minZ = depth < minZ ? depth : minZ;

                unsigned int zValue = -((-depth - 1) / 2) * 0xffffffff;

                if (drawShapeFill)
                {
                    if (drawEdge && (w1 < 0.02f || w2 < 0.02f || w3 < 0.02f))
                    {
                        target.setPixelColor(x, y, {0, 0, 0, 255}, zValue);
                    }
                    /*else if (drawEdge && (w1 < 0.03f || w2 < 0.03f || w3 < 0.03f))
					{
						target.setPixelColor(x, y, {0, 0, 0, 100}, zValue);
					}*/
                    //TODO: AAfunction When apha was implement
                    else if (drawZBuffer)
                    {
                        ubyte color = (depth + 1) / 2 * 255;
                        target.setPixelColor(x, y, {static_cast<ubyte>(color), static_cast<ubyte>(color), static_cast<ubyte>(color), 255}, zValue);
                    }
                    else if (drawMutliColor)
                    {
                        target.setPixelColor(x, y, {static_cast<ubyte>(w1 * 255), static_cast<ubyte>(w2 * 255), static_cast<ubyte>(w3 * 255), 255}, zValue);
                    }
                    else
                    {
                        ColorRGBA color;
                        color.r = w1 * v2.color_.r + w2 * v3.color_.r + w3 * v1.color_.r;
                        color.g = (w1 * v2.color_.g) + (w2 * v3.color_.g) + (w3 * v1.color_.g);
                        color.b = (w1 * v2.color_.b) + (w2 * v3.color_.b) + (w3 * v1.color_.b);
                        color.a = w1 * v2.color_.a + w2 * v3.color_.a + w3 * v1.color_.a;

                        target.setPixelColor(x, y, color, zValue);
                    }
                }
            }
        }
    }
}

Vec3 crossProduct2(const Vertex &v1, const Vertex &v2)
{
    return {v1.position_.y_ * v2.normal_.z_ - v1.position_.z_ * v2.normal_.y_,
            v1.position_.z_ * v2.normal_.x_ - v1.position_.x_ * v2.normal_.z_,
            v1.position_.x_ * v2.normal_.y_ - v1.position_.y_ * v2.normal_.x_};
}

bool faceIsVisible(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    Vertex camDirection = {0, 0, 1};
    
    return  v1.normal_.z_ < 0.f || v2.normal_.z_ < 0.f || v3.normal_.z_ < 0.f; 
}

void Rasterizer::drawTriangleWithLights(Texture &target, const std::vector<Light> &lights, const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    float zNear = -2.f;
    float zFar  = 2.f;
    
    if (!faceIsVisible(v1, v2, v3))
        return;

    // Get the bounding box of the triangle
    float maxX = max(max(v1.position_.x_, v2.position_.x_), v3.position_.x_);

    if (maxX > target.width())
       maxX = target.width();

    float minX = min(min(v1.position_.x_, v2.position_.x_), v3.position_.x_);

    if (maxX < 0.f)
       maxX = 0.f;

    float maxY = max(max(v1.position_.y_, v2.position_.y_), v3.position_.y_);

    if (maxY > target.heigth())
        maxY = target.heigth();

    float minY = min(min(v1.position_.y_, v2.position_.y_), v3.position_.y_);

    if (maxY < 0.f)
        maxY = 0.f;

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x_ - v1.position_.x_, v2.position_.y_ - v1.position_.y_, 0.f};
    Vertex vs2 = {v3.position_.x_ - v1.position_.x_, v3.position_.y_ - v1.position_.y_, 0.f};

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x_, y - v1.position_.y_, 0.f};

            float crossproductV1V2 = crossProduct(vs1, vs2);
            if (crossproductV1V2 == 0.f)
                continue;

            float w1 = crossProduct(q, vs2) / crossproductV1V2;
            float w2 = crossProduct(vs1, q) / crossproductV1V2;
            float w3 = 1.f - w1 - w2;

            // If inside of the triangle
            if ((w1 >= 0) && (w2 >= 0) && (w3 >= 0))
            {
                float depth = (w1 * v2.position_.z_ + w2 * v3.position_.z_ + w3 * v1.position_.z_);

                if (depth < zNear || depth > zFar)
                {
                    continue;
                }

                unsigned int zValue = ((depth - zNear) / (zFar + abs(zNear))) * 0xffffffff;
               //unsigned int zValue = (((depth - Znear) / (Zfar + abs(Znear))) * 0xffffffff);

                if (drawShapeFill)
                {
                    if (drawEdge && (w1 < 0.02f || w2 < 0.02f || w3 < 0.02f))
                    {
                        target.setPixelColor(x, y, {0, 0, 0, 255}, zValue);
                    }
                    /*else if (drawEdge && (w1 < 0.03f || w2 < 0.03f || w3 < 0.03f))
					{
						target.setPixelColor(x, y, {0, 0, 0, 100}, zValue);
					}*/
                    //TODO: AAfunction When apha was implement
                    else if (drawZBuffer)
                    {
                        ubyte color = ((depth - zNear) / (zFar + abs(zNear))) * 255;
                        //ubyte color = (((depth - Znear) / (Zfar + abs(Znear))) * 255); // 10 is Z far
                        target.setPixelColor(x, y, {static_cast<ubyte>(color), static_cast<ubyte>(color), static_cast<ubyte>(color), 255}, zValue);
                    }
                    else if (drawMutliColor)
                    {
                        target.setPixelColor(x, y, {static_cast<ubyte>(w1 * 255), static_cast<ubyte>(w2 * 255), static_cast<ubyte>(w3 * 255), 255}, zValue);
                    }
                    else
                    {
                        ColorRGBA color;
                        color.r = w1 * v2.color_.r + w2 * v3.color_.r + w3 * v1.color_.r;
                        color.g = w1 * v2.color_.g + w2 * v3.color_.g + w3 * v1.color_.g;
                        color.b = w1 * v2.color_.b + w2 * v3.color_.b + w3 * v1.color_.b;
                        color.a = w1 * v2.color_.a + w2 * v3.color_.a + w3 * v1.color_.a;

                        for (auto &light : lights)
                        {
                            light.computLightComponent(color, ((w1 * v2.normal_) + (w2 * v3.normal_) + (w3 * v1.normal_)).getNormalize(), 10.f);
                        }

                        target.setPixelColor(x, y, color, zValue);
                    }
                }
            }
        }
    }
}

Vertex convertVertexLocalToGlobalAndApplyProjection(Vertex vertex, const Mat4 &projectionMatrix, const Mat4 &TRSMat, bool& error)
{
    //Aplly transformation and projection to get vector in 4D
    Vec4 clipBoard = (Matrix)projectionMatrix * (Matrix)TRSMat * vertex.position_;

    //convert vector in 4D to 3D this homogenize
    if (clipBoard.w_ >= 1.f)
        clipBoard.homogenize();
    else
    {
        error = true;
        return vertex;
    }
    //adapte vertex to 2D
    vertex.position_.x_ = static_cast<float>(((clipBoard.x_ / 5) + 1) * 0.5f * 800);
    vertex.position_.y_ = static_cast<float>(600 - ((clipBoard.y_ / 5) + 1) * 0.5 * 600);
    vertex.position_.z_ = clipBoard.z_;

    Vec4 vecN(vertex.normal_);
    vecN = TRSMat * vecN;
    vertex.normal_  = {vecN.x_, vecN.y_, vecN.z_};
    vertex.normal_.normalize();

    return vertex;
}

void Rasterizer::renderScene(Texture& renBuffer, const Scene& scene, const math::Mat4& projectionMatrix)
{
    for (unsigned int i = 0; i < scene.getEntities().size(); i++)
    {
        if (Rasterizer::getSetting(R_DRAW_NORMAL))
        {
            scene.getEntities()[i]->getpMesh()->drawNormal(renBuffer, scene.getEntities()[i]->getTransform().getTRSMatrix());
        }

        if (Rasterizer::getSetting(R_DRAW_REFERENTIAL))
        {
            scene.getEntities()[i]->getTransform().displayAxis(renBuffer);
        }

        if ( scene.getEntities()[i]->getpMesh() == nullptr)
            continue; 

        for (size_t ent = 0; ent < scene.getEntities()[i]->getpMesh()->getIndices().size(); ent += 3)
        {
            bool error = false;

            Vertex v1 = convertVertexLocalToGlobalAndApplyProjection(
                scene.getEntities()[i]->getpMesh()->getVertices()[scene.getEntities()[i]->getpMesh()->getIndices()[ent]],
                projectionMatrix,
                scene.getEntities()[i]->getTransform().getTRSMatrix(), error);

            Vertex v2 = convertVertexLocalToGlobalAndApplyProjection(
                scene.getEntities()[i]->getpMesh()->getVertices()[scene.getEntities()[i]->getpMesh()->getIndices()[ent + 1]],
                projectionMatrix,
                scene.getEntities()[i]->getTransform().getTRSMatrix(), error);

            Vertex v3 = convertVertexLocalToGlobalAndApplyProjection(
                scene.getEntities()[i]->getpMesh()->getVertices()[scene.getEntities()[i]->getpMesh()->getIndices()[ent + 2]],
                projectionMatrix,
                scene.getEntities()[i]->getTransform().getTRSMatrix(), error);

            if (error)
                continue;

            Rasterizer::drawTriangleWithLights(renBuffer, scene.getLights(), v1, v2, v3);
        }
    }
}

Mat4 Rasterizer::CreatePerspectiveProjectionMatrix(int width, int height, float near, float far, float fov)
{
    float scale = tanf(fov * 0.5f * M_PI / 180.f) * near;
    float imageAspectRatio = (float)width / (float)height;
    float rigth = imageAspectRatio * scale;
    float left = -rigth;
    float top = scale;
    float bottom = -scale;

    Mat4 PMM;
    PMM[0][0] = 2.f * near / (rigth - left); 
    PMM[0][2] = (rigth + left) / (rigth - left); 
 
    PMM[1][1] = 2.f * near / (top - bottom); 
    PMM[1][2] = (top + bottom) / (top - bottom); 
 
    PMM[2][2] = -(far + near) / (far - near); 
    PMM[2][3] = -2.f * far * near / (far - near); 
 
    PMM[3][2] = -1; 
    PMM[3][3] = 0;

PMM.display();
std::cout << left << "   " << right << std::endl;

    return PMM;
}

ColorRGBA Rasterizer::getColor4f()
{
    return {static_cast<ubyte>(color.r / 255.f), static_cast<ubyte>(color.g / 255.f),
            static_cast<ubyte>(color.b / 255.f), static_cast<ubyte>(color.a / 255.f)};
}

ColorRGBA Rasterizer::getColor4ub()
{
    return color;
}

bool Rasterizer::getSetting(E_rasterizerSetting setting) throw()
{
    switch (setting)
    {
    case (E_rasterizerSetting::R_DRAW_EDGE):
        return drawEdge;
        break;

    case (E_rasterizerSetting::R_DRAW_DEPTH_BUFFER):
        return drawZBuffer;
        break;

    case (E_rasterizerSetting::R_DRAW_SHAPE_FILL):
        return drawShapeFill;
        break;

    case (E_rasterizerSetting::R_DRAW_MULTI_COLOR):
        return drawMutliColor;
        break;

    case (E_rasterizerSetting::R_DRAW_NORMAL):
        return drawNormal;
        break;

    case (E_rasterizerSetting::R_DRAW_REFERENTIAL):
        return drawReferential;
        break;

    default:
        throw runtime_error("Setting doesn't implemented");
        break;
    }
    return false;
}

void Rasterizer::setColor4f(float r, float g, float b, float a)
{
    assert((r < 0.f || r > 1.f) && (g < 0.f || g > 1.f) && (b < 0.f || b > 1.f) && (a < 0.f || a > 1.f));

    color = {static_cast<ubyte>(r * 255.f),
             static_cast<ubyte>(g * 255.f),
             static_cast<ubyte>(b * 255.f),
             static_cast<ubyte>(a * 255.f)};
}

void Rasterizer::setColor4ub(ubyte r, ubyte g, ubyte b, ubyte a)
{
    color = {r, g, b, a};
}

void Rasterizer::setSetting(E_rasterizerSetting setting, bool data) throw()
{
    switch (setting)
    {
    case (E_rasterizerSetting::R_DRAW_EDGE):
        drawEdge = data;
        break;

    case (E_rasterizerSetting::R_DRAW_DEPTH_BUFFER):
        drawZBuffer = data;
        break;

    case (E_rasterizerSetting::R_DRAW_SHAPE_FILL):
        drawShapeFill = data;
        break;

    case (E_rasterizerSetting::R_DRAW_MULTI_COLOR):
        drawMutliColor = data;
        break;

    case (E_rasterizerSetting::R_DRAW_NORMAL):
        drawNormal = data;
        break;

    case (E_rasterizerSetting::R_DRAW_REFERENTIAL):
        drawReferential = data;
        break;

    default:
        throw runtime_error("Setting doesn't implemented");
        break;
    }
}

ColorRGBA Rasterizer::color({255, 255, 255, 255});

bool Rasterizer::drawEdge(false);
bool Rasterizer::drawZBuffer(false);
bool Rasterizer::drawShapeFill(true);
bool Rasterizer::drawMutliColor(false);
bool Rasterizer::drawNormal(false);
bool Rasterizer::drawReferential(false);
