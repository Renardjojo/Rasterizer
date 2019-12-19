#include <cmath>
#include <utility>
#include <algorithm>

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

    int minX = pV1.position_.x;
    int maxX = (int)pV2.position_.x;

    //clipping
    if (steep) // x = y
    {
        if (minX < (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            minX = (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);

        if (maxX > (int)ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            maxX = ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);
    }
    else // x = x
    {
        if (minX < 0)
            minX = 0;

        if (maxX > (int)ren.width())
            maxX = ren.width();
    }
    
    double depthStep = fabs((v2.position_.z - v1.position_.z)) / (maxX - minX);
    float minZ = v2.position_.z < v1.position_.z ?  v2.position_.z : v1.position_.z;
    float maxZ = v2.position_.z > v1.position_.z ?  v2.position_.z : v1.position_.z;

    //clipping maxZ
    if (maxZ < Rasterizer::zNear)
        return;

    //clipping minZ
    if (minZ > Rasterizer::zFar) //clipping Ymin
        return;

    for (int x = minX; x < maxX; x++)
    {
        if (steep)
        {
            if(y < (int)ren.width() && y >= 0)
            {
                unsigned int zValue = 0xffffffff - ((minZ + (x - minX) * depthStep) * 0xffffffff / (Rasterizer::zFar - abs(Rasterizer::zNear)));
                ren.setPixelColor(y, x, color, zValue);
            }
        }
        else
        {
            if(y < (int)ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f) && y >= (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            {
                unsigned int zValue = 0xffffffff - ((minZ + (x - minX) * depthStep) * 0xffffffff / (Rasterizer::zFar - abs(Rasterizer::zNear)));
                ren.setPixelColor(x, y, color, zValue);

            }
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
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
    return crossZ <= 0.f;
}

void Rasterizer::drawTriangleWithLights(ArgRasterizer& arg)
{
    if (!drawShapeFill)
        return;

    if (enableBackFaceCulling && arg.entityMat->alpha_ == 1.f)
    {
        if (!faceIsVisible(arg.v1, arg.v2, arg.v3))
        return;
    }

    // Get the bounding box of the triangle
    float maxX = max(max(arg.v1.position_.x, arg.v2.position_.x), arg.v3.position_.x);
    float minX = min(min(arg.v1.position_.x, arg.v2.position_.x), arg.v3.position_.x);
    float maxY = max(max(arg.v1.position_.y, arg.v2.position_.y), arg.v3.position_.y);
    float minY = min(min(arg.v1.position_.y, arg.v2.position_.y), arg.v3.position_.y);
    float maxZ = max(max(arg.depthV1, arg.depthV2), arg.depthV3);
    float minZ = min(min(arg.depthV1, arg.depthV2), arg.depthV3);

    if (Rasterizer::enableClipping)
    {
        //clipping maxX
        if (maxX > arg.ren.width())
        maxX = arg.ren.width();
        else if (maxX < 0.f) //clipping Xmax
            return;

        //clipping minX
        if (minX < 0.f)
        minX = 0.f;
        else if (minX > arg.ren.width())
            return;

        //clipping Ymax
        if (maxY > arg.ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            maxY = arg.ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);
        else if (maxY < 0.f)
            return;

        //clipping Ymin
        if (minY < (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            minY = (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);
        else if (minY > arg.ren.heigth())
            return;

        //clipping maxZ
        if (maxZ < Rasterizer::zNear + 3) //3 to have better presentation of Z cliping in Znear
            return;

        //clipping minZ
        if (minZ > Rasterizer::zFar) //clipping Ymin
            return;
    }
    Rasterizer::nbTriangleRender++;

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {arg.v2.position_.x - arg.v1.position_.x, arg.v2.position_.y - arg.v1.position_.y, 0.f};
    Vertex vs2 = {arg.v3.position_.x - arg.v1.position_.x, arg.v3.position_.y - arg.v1.position_.y, 0.f};

    float crossproductV1V2 = crossProduct(vs1, vs2);
    if (crossproductV1V2 == 0.f)
        return;

    crossproductV1V2 = 1 / crossproductV1V2;

    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - arg.v1.position_.x, y - arg.v1.position_.y, 0.f};

            float w2 = crossProduct(q, vs2) * crossproductV1V2;
            float w3 = crossProduct(vs1, q) * crossproductV1V2;
            float w1 = 1.f - w2 - w3;

            // If inside of the triangle
            if ((w2 >= 0) && (w3 >= 0) && (w1 >= 0))
            {
                float depth = (w2 * arg.v2.position_.z + w3 * arg.v3.position_.z + w1 * arg.v1.position_.z);

                //Z Cliping with Real Z coordonnat (don't homogenous)
                float realDepth = (w2 * arg.depthV2 + w3 * arg.depthV3 + w1 * arg.depthV1);

                //correction of perspective
                w1 /= arg.wV1;
                w2 /= arg.wV2;
                w3 /= arg.wV3;

                float total = w1 + w2 + w3;

                w1 /= total;
                w2 /= total;
                w3 /= total;

                if (realDepth < Rasterizer::zNear + 3 || realDepth > Rasterizer::zFar)
                {
                    continue;
                }

                unsigned int zValue = 0xffffffff - (depth * 0xffffffff / (Rasterizer::zFar - abs(Rasterizer::zNear)));

                if (drawEdge && (w2 < 0.02f || w3 < 0.02f || w1 < 0.02f))
                {
                    arg.ren.setPixelColor(x, y, {0, 0, 0, 255}, zValue);
                }
                else if (drawZBuffer)
                {
                    ubyte color = 255 - (realDepth * 255 /  (Rasterizer::zFar - abs(Rasterizer::zNear)));
                    arg.ren.setPixelColor(x, y, {static_cast<ubyte>(color), static_cast<ubyte>(color), static_cast<ubyte>(color), 255}, zValue);
                }
                else if (drawMutliColor)
                {
                    arg.ren.setPixelColor(x, y, {static_cast<ubyte>(w2 * 255), static_cast<ubyte>(w3 * 255), static_cast<ubyte>(w1 * 255), 255}, zValue);
                }
                else
                {
                    if (arg.pTexture == nullptr) //color this color of vertex
                    { 
                        ColorRGBA color {255, 255, 255, static_cast<ubyte>(255 * arg.entityMat->alpha_)};
                        Vec3 pixelPos   {w2 * arg.v2RealPos + w3 * arg.v3RealPos + w1 * arg.v1RealPos};
                        pixelPos.z = -pixelPos.z;
                        
                        for (auto &light : arg.lights)
                        {
                            light.computLightComponent( color,
                                                        ((w2 * arg.v2.normal_) + (w3 * arg.v3.normal_) + (w1 * arg.v1.normal_)).getNormalize(),
                                                        arg.viewerPosition,
                                                        pixelPos,
                                                        arg.entityMat);
                        }

                        arg.ren.setPixelColor(x, y, color, zValue);
                    }
                    else //color with texture of entity
                    {
                        Vec2 coordText  {w2 * arg.v2.texCoords_ + w3 * arg.v3.texCoords_ + w1 * arg.v1.texCoords_};
                        Vec3 pixelPos   {w2 * arg.v2RealPos + w3 * arg.v3RealPos + w1 * arg.v1RealPos};
                        pixelPos.z = -pixelPos.z;

                        coordText.x = coordText.x - floor(coordText.x);
                        coordText.y = coordText.y - floor(coordText.y);
                        coordText.x *= (arg.pTexture->width() - 1);
                        coordText.y *= (arg.pTexture->heigth() - 1);

                        ColorRGBA color = arg.pTexture->getRGBAPixelColor(coordText.x, coordText.y);
                        color.a *= arg.entityMat->alpha_;

                        for (auto &light : arg.lights)
                        {
                            light.computLightComponent( color,
                                                        ((w2 * arg.v2.normal_) + (w3 * arg.v3.normal_) + (w1 * arg.v1.normal_)).getNormalize(),
                                                        arg.viewerPosition, 
                                                        pixelPos,
                                                        arg.entityMat,
                                                        Rasterizer::usePhongLigthAlgorythme ? E_LightAlgorythm::PHONG : 
                                                        Rasterizer::useBlinnPhongLigthAlgorythme ? E_LightAlgorythm::BLINN_PHONG : E_LightAlgorythm::NONE);
                        }
                        arg.ren.setPixelColor(x, y, color, zValue);
                    }
                }
            }
        }
    }
}

//this function apply blur to pixel with near pixel arround
inline void blurPixel (Renderer& ren, unsigned int x, unsigned int y)
{
    bool lettterBox = Rasterizer::getSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING);

    if (x < 1 || y < (lettterBox ? 101.f : 1.f) || x > ren.width() - 1 || y > ren.heigth() - (lettterBox ? 101.f : 1.f))
        return;

    int r(0), g(0), b(0);

    for (unsigned int y2 = y - 1; y2 <= y + 1; y2++)
    {
        for (unsigned int x2 = x - 1; x2 <= x + 1; x2++)
        {
            r += ren.getPixelColor(x2, y2).r;
            g += ren.getPixelColor(x2, y2).g;
            b += ren.getPixelColor(x2, y2).b;
        }
    }

    ren.setPixelColor(x, y, {static_cast<ubyte>(r / 9), static_cast<ubyte>(g / 9), static_cast<ubyte>(b / 9), 255});
}

void Rasterizer::applyMSAA	(Renderer& ren, const Vertex &v1, const Vec3& v1RealPos, float depthV1, const Vertex &v2, const Vec3& v2RealPos, float depthV2, const Vertex &v3, const Vec3& v3RealPos, float depthV3)
{
    if (!faceIsVisible(v1, v2, v3))
    {
        return;
    }

    // Get the bounding box of the triangle
    float maxX = max(max(v1.position_.x, v2.position_.x), v3.position_.x);
    float minX = min(min(v1.position_.x, v2.position_.x), v3.position_.x);
    float maxY = max(max(v1.position_.y, v2.position_.y), v3.position_.y);
    float minY = min(min(v1.position_.y, v2.position_.y), v3.position_.y);
    float maxZ = max(max(depthV1, depthV2), depthV3);
    float minZ = min(min(depthV1, depthV2), depthV3);

    if (Rasterizer::enableClipping)
    {
        //clipping maxX
        if (maxX > ren.width())
        maxX = ren.width();
        else if (maxX < 0.f) //clipping Xmax
            return;

        //clipping minX
        if (minX < 0.f)
        minX = 0.f;
        else if (minX > ren.width())
            return;

        //clipping Ymax
        if (maxY > ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            maxY = ren.heigth() - (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);
        else if (maxY < 0.f)
            return;

        //clipping Ymin
        if (minY < (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f))
            minY = (Rasterizer::enableLetterBoxClipping ? 100.f : 0.f);
        else if (minY > ren.heigth())
            return;

        //clipping maxZ
        if (maxZ < Rasterizer::zNear + 3)
            return;

        //clipping minZ
        if (minZ > Rasterizer::zFar) //clipping Ymin
            return;
    }

    // Spanning vectors of edge (pV1,pV2) and (pV1,v3)
    Vertex vs1 = {v2.position_.x - v1.position_.x, v2.position_.y - v1.position_.y, 0.f};
    Vertex vs2 = {v3.position_.x - v1.position_.x, v3.position_.y - v1.position_.y, 0.f};

    float crossproductV1V2 = crossProduct(vs1, vs2);
    if (crossproductV1V2 == 0.f)
        return;
        
    for (int x = minX; x < maxX; x++)
    {
        for (int y = minY; y < maxY; y++)
        {
            Vertex q = {x - v1.position_.x, y - v1.position_.y, 0.f};

            float w2 = crossProduct(q, vs2) / crossproductV1V2;
            float w3 = crossProduct(vs1, q) / crossproductV1V2;
            float w1 = 1.f - w2 - w3;

            // If inside of the triangle
            if ((w2 >= 0) && (w3 >= 0) && (w1 >= 0))
            {
                if ((w2 < 0.04f || w3 < 0.04f || w1 < 0.04f))
                {
                    blurPixel (ren, x, y);
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
        clipBoard.homogenize();
    }

    return clipBoard.xyz;
}

inline void applyViewportTransformation (Vec3& vec, unsigned int winH, unsigned int winW)
{
    vec.x = static_cast<float>(((vec.x / 5) + 1) * 0.5f * winW);
    vec.y = static_cast<float>(winH - ((vec.y / 5) + 1) * 0.5f * winH);
}

//draw normal of global vertex 
inline void drawnNormal(Renderer& ren, Vertex& vertexLocal, Vertex& vertexGlobal, const Mat4 &projectionMatrix, const Mat4 &inverseCameraMatrix, const Mat4 &TRSMat)
{
    Vertex origin = vertexGlobal;
	Vertex axis = {	(vertexLocal.normal_.x * 0.5f + vertexLocal.position_.x),
					(vertexLocal.normal_.y * 0.5f + vertexLocal.position_.y),
					(vertexLocal.normal_.z * 0.5f + vertexLocal.position_.z)};

    Vec4 modelViewV1 = creatModelViewVector(axis.position_, TRSMat);
    modelViewV1 = inverseCameraMatrix * modelViewV1;
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

inline vector<Vertex> convertLocalToGlobalVertex (const Entity& ent, vector<float>& w, const Mat4 &projectionMatrix, unsigned int winH, unsigned int winW, const math::Mat4& inverseCameraMatrix)
{
    //Step 1 : Create global vertex
    vector<Vec3> globalPosVertices = ent.getpMesh()->vertex_;
    vector<float> wCopy;

    for (auto& vertex : globalPosVertices)
    {
        //Model & view transform
        Vec4 modelViewV1 = creatModelViewVector(vertex, ent.getTransform().getTRSMatrix());
        modelViewV1 = inverseCameraMatrix * modelViewV1;

        //apply projection
        modelViewV1 = projectionMatrix * modelViewV1;

        wCopy.push_back(modelViewV1.w);

        //convert vector in 4D to 3D this homogenize
        if (modelViewV1.w != 0.f && modelViewV1.w != 1.f)
        {
            modelViewV1.homogenize();
        }

        Vec3 clipCoordV1 = std::move(modelViewV1.xyz);

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
        w.push_back(wCopy[ent.getpMesh()->facesIndices_[i].iV1.iV]);

        globalVertices.push_back(  {  globalPosVertices[ent.getpMesh()->facesIndices_[i].iV2.iV],
                                      globalNormal[ent.getpMesh()->facesIndices_[i].iV2.iVn],
                                      ent.getpMesh()->textCoord_[ent.getpMesh()->facesIndices_[i].iV2.iVt]});
        w.push_back(wCopy[ent.getpMesh()->facesIndices_[i].iV2.iV]);

        globalVertices.push_back(  {globalPosVertices[ent.getpMesh()->facesIndices_[i].iV3.iV],
                                      globalNormal[ent.getpMesh()->facesIndices_[i].iV3.iVn],
                                      ent.getpMesh()->textCoord_[ent.getpMesh()->facesIndices_[i].iV3.iVt]});
        w.push_back(wCopy[ent.getpMesh()->facesIndices_[i].iV3.iV]);
    }

    return globalVertices;
}

inline void convertLocalPosToClippCoordWithRealZ (Vec3& pos, float& depth, const Entity& ent, const math::Mat4& inverseCameraMatrix)
{
    //Model & view transform
    Vec4 modelViewV1 = creatModelViewVector(pos, ent.getTransform().getTRSMatrix());

    Vec4 depthVec = inverseCameraMatrix * modelViewV1;
    depthVec.homogenize();
    depth = -(depthVec).z;

    if (modelViewV1.w != 0.f && modelViewV1.w != 1.f)
    {
        modelViewV1.x /= modelViewV1.w;
        modelViewV1.y /= modelViewV1.w;
        modelViewV1.z /= modelViewV1.w;
    }

    pos = modelViewV1.xyz;
    pos.z = -pos.z;
}

inline bool customSortEntByAlpha(const Entity* a, const Entity* b)
{   
    return a->getpMaterial()->alpha_ < b->getpMaterial()->alpha_;
}

inline bool customSortEntByDistanceIfAlpha(const Entity* a, const Entity* b, const Vec3& camPos)
{  
    if(a->getpMaterial()->alpha_ == 1.f)
	{
        return false;
	}

	float distance1 = (camPos - a->getTransform().getLocalOrigin()).length();
	float distance2 = (camPos - b->getTransform().getLocalOrigin()).length();

    return distance1 > distance2;
}

//this function sort all entity of scene in function of there alpha and there position with camera. Use for blending mod
void sortEntityForBlending  (vector<const Entity*>& tabpEnt, const Vec3& camPos)
{
    sort(tabpEnt.begin(), tabpEnt.end(), customSortEntByAlpha);    
    sort(tabpEnt.begin(), tabpEnt.end(), std::bind(customSortEntByDistanceIfAlpha, std::placeholders::_1, std::placeholders::_2, camPos));
}

void Rasterizer::renderScene(Renderer& ren, const Scene& scene, const math::Mat4& inverseCameraMatrix, const Vec3& camPos)
{
    vector<const Entity*> entCopy;
    
    for (auto& ent : scene.getEntities())
    {
        entCopy.push_back(ent.get());
    }

    if(Rasterizer::enableAlphaBlending)
    {
        sortEntityForBlending (entCopy, camPos);
    }

    for (unsigned int i = 0; i < entCopy.size(); i++)
    {
        std::shared_ptr<Mesh> entMesh = entCopy[i]->getpMesh();

        if (Rasterizer::getSetting(R_DRAW_REFERENTIAL))
        {
            entCopy[i]->getTransform().displayAxis(ren, Rasterizer::projectionMatrix, inverseCameraMatrix);
        }

        if ( entMesh == nullptr)
            continue;

        vector<float> w;
        vector<Vertex> globalVertex (convertLocalToGlobalVertex(*entCopy[i], w, Rasterizer::projectionMatrix, ren.heigth(), ren.width(), inverseCameraMatrix));

        for (size_t ent = 0; ent < globalVertex.size(); ent += 3)
        {
            const Face triangle = entMesh->getFace(ent / 3);
            Vertex v1Local  {triangle.v1.pos, triangle.v1.normal, triangle.v1.textCord};
            Vertex v2Local  {triangle.v2.pos, triangle.v2.normal, triangle.v2.textCord};
            Vertex v3Local  {triangle.v3.pos, triangle.v3.normal, triangle.v3.textCord};

            if (Rasterizer::getSetting(R_DRAW_NORMAL))
            {               
                drawnNormal(ren, v1Local, globalVertex[ent], Rasterizer::projectionMatrix, inverseCameraMatrix, entCopy[i]->getTransform().getTRSMatrix());
                drawnNormal(ren, v2Local, globalVertex[ent + 1], Rasterizer::projectionMatrix, inverseCameraMatrix, entCopy[i]->getTransform().getTRSMatrix());
                drawnNormal(ren, v3Local, globalVertex[ent + 2], Rasterizer::projectionMatrix, inverseCameraMatrix, entCopy[i]->getTransform().getTRSMatrix());
            }
            float depthV1, depthV2, depthV3;

            convertLocalPosToClippCoordWithRealZ(v1Local.position_, depthV1, *entCopy[i], inverseCameraMatrix);
            convertLocalPosToClippCoordWithRealZ(v2Local.position_, depthV2, *entCopy[i], inverseCameraMatrix);
            convertLocalPosToClippCoordWithRealZ(v3Local.position_, depthV3, *entCopy[i], inverseCameraMatrix);

            Texture* pTex = entCopy[i]->getpMaterial() == nullptr ? nullptr : entCopy[i]->getpMaterial()->pTexture_.get();

            ArgRasterizer argRas {  ren,
                                    scene.getLights(), 
                                    scene.camPos_, 
                                    entCopy[i]->getpMaterial(),
                                    globalVertex[ent],
                                    globalVertex[ent + 1],
                                    globalVertex[ent + 2],
                                    v1Local.position_,
                                    v2Local.position_,
                                    v3Local.position_,
                                    depthV1, 
                                    depthV2,
                                    depthV3,
                                    w[ent],
                                    w[ent + 1],
                                    w[ent + 2],
                                    inverseCameraMatrix, 
                                    pTex};

            Rasterizer::drawTriangleWithLights(argRas);
        }
    }

    if(Rasterizer::enableAntiAliasing)
    {
        for (unsigned int i = 0; i < entCopy.size(); i++)
        {
            vector<float> w;
            vector<Vertex> globalVertex (convertLocalToGlobalVertex(*entCopy[i], w, Rasterizer::projectionMatrix, ren.heigth(), ren.width(), inverseCameraMatrix));

            for (size_t ent = 0; ent < globalVertex.size(); ent += 3)
            {
                const Face triangle = entCopy[i]->getpMesh()->getFace(ent / 3);
                Vertex v1Local  {triangle.v1.pos, triangle.v1.normal, triangle.v1.textCord};
                Vertex v2Local  {triangle.v2.pos, triangle.v2.normal, triangle.v2.textCord};
                Vertex v3Local  {triangle.v3.pos, triangle.v3.normal, triangle.v3.textCord};

                float depthV1, depthV2, depthV3;
                convertLocalPosToClippCoordWithRealZ(v1Local.position_, depthV1, *entCopy[i], inverseCameraMatrix);
                convertLocalPosToClippCoordWithRealZ(v2Local.position_, depthV2, *entCopy[i], inverseCameraMatrix);
                convertLocalPosToClippCoordWithRealZ(v3Local.position_, depthV3, *entCopy[i], inverseCameraMatrix);

                Rasterizer::applyMSAA(ren, globalVertex[ent], v1Local.position_, depthV1, globalVertex[ent + 1], v2Local.position_, depthV2, globalVertex[ent + 2], v3Local.position_, depthV3);
            }
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

    case (E_rasterizerSetting::R_ENABLE_CLIPPING):
        return enableClipping;
    break;

    case (E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING):
        return enableLetterBoxClipping;
    break;

    case (E_rasterizerSetting::R_ENABLE_ANTI_ALIASING):
        return enableAntiAliasing;
    break;

    case (E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME):
        return usePhongLigthAlgorythme;
    break;

    case (E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME):
        return useBlinnPhongLigthAlgorythme;
    break;

    case (E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING):
        return enableAlphaBlending;
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
        enableBackFaceCulling  = data;
        break;

    case (E_rasterizerSetting::R_ENABLE_CLIPPING):
        enableClipping = data;
        break;

    case (E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING):
        enableLetterBoxClipping = data;
        break;

    case (E_rasterizerSetting::R_ENABLE_ANTI_ALIASING):
        enableAntiAliasing = data;
        break;

    case (E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME):
        usePhongLigthAlgorythme = data;
        useBlinnPhongLigthAlgorythme = !data;
        break;

    case (E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME):
        useBlinnPhongLigthAlgorythme = data;
        usePhongLigthAlgorythme = !data;
        break;

    case (E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING):
        enableAlphaBlending = data;
        break; 

    default:
        throw runtime_error("Setting doesn't implemented");
        break;
    }
}

void Rasterizer::loadPerspectiveMatrix	(float fovy, float aspect, float zNear, float zFar)
{
    Rasterizer::projectionMatrix    = Mat4::createPerspectiveMatrix(aspect, zNear, zFar, fovy);
    Rasterizer::zNear               = zNear;
    Rasterizer::zFar                = zFar;
}

void Rasterizer::loadOrthoMatrix	(float left, float right, float bottom, float top, float nearVal, float farVal)
{
    Rasterizer::projectionMatrix    = Mat4::createOrthoMatrix(left, right, bottom, top, nearVal, farVal);
    Rasterizer::zNear               = zNear;
    Rasterizer::zFar                = zFar;
}

ColorRGBA Rasterizer::color({255, 255, 255, 255});

bool Rasterizer::drawEdge(false);
bool Rasterizer::drawZBuffer(false);
bool Rasterizer::drawShapeFill(true);
bool Rasterizer::drawMutliColor(false);
bool Rasterizer::drawNormal(false);
bool Rasterizer::drawReferential(false);
bool Rasterizer::enableBackFaceCulling(true);
bool Rasterizer::enableClipping(true);
bool Rasterizer::enableLetterBoxClipping(false);
bool Rasterizer::enableAntiAliasing(false);
bool Rasterizer::usePhongLigthAlgorythme(false);
bool Rasterizer::useBlinnPhongLigthAlgorythme(true);
bool Rasterizer::enableAlphaBlending(false);

unsigned int Rasterizer::nbTriangleRender(0);
Mat4	Rasterizer::projectionMatrix{};
float 	Rasterizer::zNear(0.f);
float	Rasterizer::zFar(0.f);