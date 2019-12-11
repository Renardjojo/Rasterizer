#include <cmath>
#include <utility>
#include "rasterizer.hpp"
#include "vec.hpp"

using namespace math;

inline float min(float value1, float value2)
{
    if (value2 <= value1)
        return value2;
    else
        return value1;
}

inline float max(float value1, float value2)
{
    if (value1 >= value2)
        return value1;
    else
        return value2;
}

inline float crossProduct(const Vertex &v1, const Vertex &v2)
{
    return v1.position_.x * v2.position_.y - v1.position_.y * v2.position_.x;
}

void Rasterizer::drawLine(Renderer& ren, Vertex &v1, Vertex &v2)
{
    Vertex pV1 = v1;
    Vertex pV2 = v2;

    // Bresenham's line algorithm
    const bool steep = (fabs(pV2.position_.y - pV1.position_.y) > fabs(pV2.position_.x - pV1.position_.x));

    if (steep)
    {
        std::swap(pV1.position_.x, pV1.position_.y);
        std::swap(pV2.position_.x, pV2.position_.y);
    }

    if (pV1.position_.x > pV2.position_.x)
    {
        std::swap(pV1.position_.x, pV2.position_.x);
        std::swap(pV1.position_.y, pV2.position_.y);
    }

    const float dx = pV2.position_.x - pV1.position_.x;
    const float dy = fabs(pV2.position_.y - pV1.position_.y);

    float error = dx / 2.0f;
    const int ystep = (pV1.position_.y < pV2.position_.y) ? 1 : -1;
    int y = (int)pV1.position_.y;

    const int maxX = (int)pV2.position_.x;

    for (int x = (int)pV1.position_.x; x < maxX; x++)
    {
        if (steep)
        {
            ren.setPixelColor(y, x, color);
        }
        else
        {
            ren.setPixelColor(x, y, color);
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Rasterizer::drawTriangle(Renderer& ren, const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    // Get the bounding box of the triangle
    float maxX, minX, maxY, minY = 0;
    //float maxZ = -5;
    // float minZ = +5;

    maxX = max(max(v1.position_.x, v2.position_.x), v3.position_.x);
    minX = min(min(v1.position_.x, v2.position_.x), v3.position_.x);
    maxY = max(max(v1.position_.y, v2.position_.y), v3.position_.y);
    minY = min(min(v1.position_.y, v2.position_.y), v3.position_.y);

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x - v1.position_.x, v2.position_.y - v1.position_.y, 0.f};
    Vertex vs2 = {v3.position_.x - v1.position_.x, v3.position_.y - v1.position_.y, 0.f};

    Rasterizer::nbTriangleRender++;

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x, y - v1.position_.y, 0.f};

            float crossproductV1V2 = crossProduct(vs1, vs2);
            if (crossproductV1V2 == 0.f)
                continue;

            float w1 = crossProduct(q, vs2) / crossproductV1V2;
            float w2 = crossProduct(vs1, q) / crossproductV1V2;
            float w3 = 1.f - w1 - w2;

            // If inside of the triangle
            if ((w1 >= 0) && (w2 >= 0) && (w3 >= 0))
            {
                float depth = (w1 * v2.position_.z + w2 * v3.position_.z + w3 * v1.position_.z);

                //maxZ = depth > maxZ ? depth : maxZ;
                //minZ = depth < minZ ? depth : minZ;

                unsigned int zValue = -((-depth - 1) / 2) * 0xffffffff;

                if (drawShapeFill)
                {
                    if (drawEdge && (w1 < 0.02f || w2 < 0.02f || w3 < 0.02f))
                    {
                        ren.setPixelColor(x, y, {0, 0, 0, 255}, zValue);
                    }
                    else if (drawZBuffer)
                    {
                        ubyte color = (depth + 1) / 2 * 255;
                        ren.setPixelColor(x, y, {static_cast<ubyte>(color), static_cast<ubyte>(color), static_cast<ubyte>(color), 255}, zValue);
                    }
                    else if (drawMutliColor)
                    {
                        ren.setPixelColor(x, y, {static_cast<ubyte>(w1 * 255), static_cast<ubyte>(w2 * 255), static_cast<ubyte>(w3 * 255), 255}, zValue);
                    }
                    else
                    {                          
                        ColorRGBA color;
                        color.r = w1 * v2.color_.r + w2 * v3.color_.r + w3 * v1.color_.r;
                        color.g = (w1 * v2.color_.g) + (w2 * v3.color_.g) + (w3 * v1.color_.g);
                        color.b = (w1 * v2.color_.b) + (w2 * v3.color_.b) + (w3 * v1.color_.b);
                        color.a = w1 * v2.color_.a + w2 * v3.color_.a + w3 * v1.color_.a;                      

                        ren.setPixelColor(x, y, color, zValue);
                    }
                }
            }
        }
    }
}

inline float cross_product_z (const Vec3& a, const Vec3& b)
{
	return (a.x * b.y) - (a.y * b.x);
}

inline bool faceIsVisible(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    float crossZ = cross_product_z((v2.position_ - v1.position_), (v3.position_ - v1.position_));
    return crossZ > 0.f;
}

void Rasterizer::drawTriangleWithLights(Renderer& ren, const std::vector<Light> &lights, const Vec3& viewerPosition, const Vec3& entityPos, const Vertex &v1, const Vertex &v2, const Vertex &v3, const Texture* pTexture)
{
    float zNear = 0.01f;
    float zFar  = 100.f;

    if (enableBackFaceCulling)
    {
        if (faceIsVisible(v1, v2, v3))
        return;
    }
    // Get the bounding box of the triangle
    float maxX = max(max(v1.position_.x, v2.position_.x), v3.position_.x);

    if (maxX > ren.width())
       maxX = ren.width();
    else if (maxX < 0.f) //clipping Xmax
        return;

    float minX = min(min(v1.position_.x, v2.position_.x), v3.position_.x);

    //clipping Xmin
    if (minX < 0.f)
       minX = 0.f;
    else if (minX > ren.width())
        return;
    
    float maxY = max(max(v1.position_.y, v2.position_.y), v3.position_.y);

    //clipping Ymax
    if (maxY > ren.heigth() - 100.f)
        maxY = ren.heigth() - 100.f;
    else if (maxY < 0.f)
        return;

    float minY = min(min(v1.position_.y, v2.position_.y), v3.position_.y);

    //clipping Ymin
    if (minY < 100.f)
        minY = 100.f;
    else if (minY > ren.heigth())
        return;

    float maxZ = max(max(v1.position_.z, v2.position_.z), v3.position_.z);

    //clipping maxZ
    if (maxZ < zNear)
        return;

    float minZ = min(min(v1.position_.z, v2.position_.z), v3.position_.z);

    //clipping minZ
    if (minZ > zFar) //clipping Ymin
        return;    


    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x - v1.position_.x, v2.position_.y - v1.position_.y, 0.f};
    Vertex vs2 = {v3.position_.x - v1.position_.x, v3.position_.y - v1.position_.y, 0.f};

    Rasterizer::nbTriangleRender++;

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x, y - v1.position_.y, 0.f};

            float crossproductV1V2 = crossProduct(vs1, vs2);
            if (crossproductV1V2 == 0.f)
                continue;

            float w1 = crossProduct(q, vs2) / crossproductV1V2;
            float w2 = crossProduct(vs1, q) / crossproductV1V2;
            float w3 = 1.f - w1 - w2;

            // If inside of the triangle
            if ((w1 >= 0) && (w2 >= 0) && (w3 >= 0))
            {
                float depth = (w1 * v2.position_.z + w2 * v3.position_.z + w3 * v1.position_.z);
                //std::cout << depth << std::endl;

                if (depth < zNear || depth > zFar)
                {
                    continue;
                }

                unsigned int zValue = 0xffffffff - (depth * 0xffffffff / (zFar - abs(zNear)));
               // unsigned int zValue = ((depth - zNear) / (zFar + abs(zNear))) * 0xffffffff;
               //unsigned int zValue = (((depth - Znear) / (Zfar + abs(Znear))) * 0xffffffff);

                if (drawShapeFill)
                {
                    if (drawEdge && (w1 < 0.02f || w2 < 0.02f || w3 < 0.02f))
                    {
                        ren.setPixelColor(x, y, {0, 0, 0, 255}, zValue);
                    }
                    else if (drawZBuffer)
                    {
                        //ubyte color = ((depth - zNear) / (zFar + abs(zNear))) * 255;
                        ubyte color = 255 - (depth * 255 / (zFar - abs(zNear)));
                        //ubyte color = (((depth - Znear) / (Zfar + abs(Znear))) * 255); // 10 is Z far
                        ren.setPixelColor(x, y, {static_cast<ubyte>(color), static_cast<ubyte>(color), static_cast<ubyte>(color), 255}, zValue);
                    }
                    else if (drawMutliColor)
                    {
                        ren.setPixelColor(x, y, {static_cast<ubyte>(w1 * 255), static_cast<ubyte>(w2 * 255), static_cast<ubyte>(w3 * 255), 255}, zValue);
                    }
                    else
                    {
                        if (pTexture == nullptr) //color this color of vertex
                        { 
                            ColorRGBA color;
                            color.r = w1 * v2.color_.r + w2 * v3.color_.r + w3 * v1.color_.r;
                            color.g = w1 * v2.color_.g + w2 * v3.color_.g + w3 * v1.color_.g;
                            color.b = w1 * v2.color_.b + w2 * v3.color_.b + w3 * v1.color_.b;
                            color.a = w1 * v2.color_.a + w2 * v3.color_.a + w3 * v1.color_.a;

                            for (auto &light : lights)
                            {
                                light.computLightComponent( color,
                                                            ((w1 * v2.normal_) + (w2 * v3.normal_) + (w3 * v1.normal_)).getNormalize(),
                                                            viewerPosition,
                                                            entityPos,
                                                            32.f);
                            }
                    
                            ren.setPixelColor(x, y, color, zValue);
                        }
                        else //color with texture of entity
                        {
                            Vec2 coordText = w1 * v2.texCoords_ + w2 * v3.texCoords_ + w3 * v1.texCoords_;

                            coordText.x = coordText.x - floor(coordText.x);
                            coordText.y = coordText.y - floor(coordText.y);
                            coordText.x *= (pTexture->width() - 1);
                            coordText.y *= (pTexture->heigth() - 1);

                            //if (coordText.y < 0.f)
                             //   return;

                            ColorRGBA color = pTexture->getRGBAPixelColor(coordText.x, coordText.y);

                            for (auto &light : lights)
                            {
                                light.computLightComponent( color, 
                                                            ((w1 * v2.normal_) + (w2 * v3.normal_) + (w3 * v1.normal_)).getNormalize(),
                                                            viewerPosition, 
                                                            entityPos,
                                                            32.f);
                            }
                            ren.setPixelColor(x, y, color, zValue);
                        }
                    }
                }
            }
        }
    }
}


inline Vec4 creatModelViewVector(const Vec3& vecLocalPos, const Mat4 &TRSMat)
{
    return TRSMat * vecLocalPos;
}

inline Vec3 createProjectionVector (Vec4& clipBoard, const Mat4 &projectionMatrix)
{
    clipBoard = projectionMatrix * clipBoard;

    //convert vector in 4D to 3D this homogenize
    if (clipBoard.w != 0.f && clipBoard.w != 1.f)
    {
        //hack : preserve in Z for Z buffer en clipping
        clipBoard.x /= clipBoard.w;
        clipBoard.y /= clipBoard.w;
    }

    return clipBoard.xyz;
}

inline void applyViewportTransformation (Vec3& vec, unsigned int winH, unsigned int winW)
{
    vec.x = static_cast<float>(((vec.x / 5) + 1) * 0.5f * winW);
    vec.y = static_cast<float>(winH - ((vec.y / 5) + 1) * 0.5f * winH);
}

//draw normal of global vertex 
inline void drawnNormal(Renderer& ren, Vertex& vertexLocal, Vertex& vertexGlobal, const Mat4 &projectionMatrix, const Mat4 &TRSMat)
{
    Vertex origin = vertexGlobal;
	Vertex axis = {	(vertexLocal.normal_.x * 0.5f + vertexLocal.position_.x),
					(vertexLocal.normal_.y * 0.5f + vertexLocal.position_.y),
					(vertexLocal.normal_.z * 0.5f + vertexLocal.position_.z)};

    Vec4 modelViewV1 = creatModelViewVector(axis.position_, TRSMat);
    Vec3 clipCoordV1 = createProjectionVector (modelViewV1, projectionMatrix);
    applyViewportTransformation (clipCoordV1, ren.heigth(), ren.width());

    axis.position_ = clipCoordV1;

	Rasterizer::setColor4ub(0, 255, 255, 255);
	Rasterizer::drawLine(ren, origin, axis);
}

inline void updateNormalWithRotation(Vec3& normal, const Vec3& rotation)
{
    normal = Mat3::createFixedAngleEulerRotationMatrix(rotation) * normal;
}

inline vector<Vertex> convertLocalToGlobalVertex (const Entity& ent, const Mat4 &projectionMatrix, unsigned int winH, unsigned int winW, const math::Mat4& inverseCameraMatrix)
{
    //Step 1 : Create global vertex
    vector<Vec3> globalPosVertices = ent.getpMesh()->vertex_;

    for (auto& vertex : globalPosVertices)
    {
        //Model & view transform
        Vec4 modelViewV1 = creatModelViewVector(vertex, ent.getTransform().getTRSMatrix());

        modelViewV1 = inverseCameraMatrix * modelViewV1;

        //apply projection
        Vec3 clipCoordV1 = std::move(createProjectionVector (modelViewV1, projectionMatrix));

        //create viewport position
        applyViewportTransformation (clipCoordV1 , winH, winW);
        vertex = std::move(clipCoordV1);
    }

    //Step 2 : Create global normal
    vector<Vec3> globalNormal = ent.getpMesh()->normal_;

    for (auto& normal : globalNormal)
    {
        //update the new normal in function of rotation only
        updateNormalWithRotation(normal, ent.getTransform().getLocalOrientation());
    }

    //Step 3 : englob information into vertex
    vector<Vertex> globalVertices;

    for (size_t i = 0; i < ent.getpMesh()->facesIndices_.size(); i++)
    {
        globalVertices.push_back(  {  globalPosVertices[ent.getpMesh()->facesIndices_[i].iV1.iV], 
                                      globalNormal[ent.getpMesh()->facesIndices_[i].iV1.iVn],
                                      ent.getpMesh()->textCoord_[ent.getpMesh()->facesIndices_[i].iV1.iVt]});

        globalVertices.push_back(  {  globalPosVertices[ent.getpMesh()->facesIndices_[i].iV2.iV],
                                      globalNormal[ent.getpMesh()->facesIndices_[i].iV2.iVn],
                                      ent.getpMesh()->textCoord_[ent.getpMesh()->facesIndices_[i].iV2.iVt]});

        globalVertices.push_back(  {globalPosVertices[ent.getpMesh()->facesIndices_[i].iV3.iV],
                                      globalNormal[ent.getpMesh()->facesIndices_[i].iV3.iVn],
                                      ent.getpMesh()->textCoord_[ent.getpMesh()->facesIndices_[i].iV3.iVt]});
    }

    return globalVertices;
}

void Rasterizer::renderScene(Renderer& ren, const Scene& scene, const math::Mat4& projectionMatrix, const math::Mat4& inverseCameraMatrix)
{
    for (unsigned int i = 0; i < scene.getEntities().size(); i++)
    {
        std::shared_ptr<Mesh> entMesh = scene.getEntities()[i]->getpMesh();

        if (Rasterizer::getSetting(R_DRAW_REFERENTIAL))
        {
            scene.getEntities()[i]->getTransform().displayAxis(ren, projectionMatrix);
        }

        if ( entMesh == nullptr)
            continue;

        vector<Vertex> globalVertex (convertLocalToGlobalVertex(*scene.getEntities()[i].get(), projectionMatrix, ren.heigth(), ren.width(), inverseCameraMatrix));

        for (size_t ent = 0; ent < globalVertex.size(); ent += 3)
        {
            if (Rasterizer::getSetting(R_DRAW_NORMAL))
            {
                const Face triangle = entMesh->getFace(ent / 3);
                Vertex v1Local  {triangle.v1.pos, triangle.v1.normal, triangle.v1.textCord};
                Vertex v2Local  {triangle.v2.pos, triangle.v2.normal, triangle.v2.textCord};
                Vertex v3Local  {triangle.v3.pos, triangle.v3.normal, triangle.v3.textCord};
                
                drawnNormal(ren, v1Local, globalVertex[ent], projectionMatrix, scene.getEntities()[i]->getTransform().getTRSMatrix());
                drawnNormal(ren, v2Local, globalVertex[ent + 1], projectionMatrix, scene.getEntities()[i]->getTransform().getTRSMatrix());
                drawnNormal(ren, v3Local, globalVertex[ent + 2], projectionMatrix, scene.getEntities()[i]->getTransform().getTRSMatrix());
            }

            Rasterizer::drawTriangleWithLights(ren, scene.getLights(), scene.camPos_, scene.getEntities()[i]->getTransform().getLocalOrigin(), globalVertex[ent], globalVertex[ent + 1], globalVertex[ent + 2], scene.getEntities()[i]->getpTexture().get());
        }
    }
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

    case (E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING):
        return enableBackFaceCulling;
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

    case (E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING):
        enableBackFaceCulling = data;
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
bool Rasterizer::enableBackFaceCulling(true);
unsigned int Rasterizer::nbTriangleRender(0);