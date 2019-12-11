#include "mesh.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace math;
using namespace std;

shared_ptr<Mesh> Mesh::createCube	()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	//cube contain 12 triangle, 8 vertex 4 texture coordonate and 6 normal
	mesh->facesIndices_	.reserve(12);
	mesh->vertex_		.reserve(8);
	mesh->textCoord_	.reserve(4);
	mesh->normal_		.reserve(6);

	//initialize the index of cube :
	//Face 1
	mesh->facesIndices_	.push_back({{0, 0, 0}, {1, 1, 0}, {2, 2, 0}});
	mesh->facesIndices_	.push_back({{2, 2, 0}, {1, 1, 0}, {3, 3, 0}});

	//Face 2
	mesh->facesIndices_	.push_back({{2, 0, 1}, {3, 1, 1}, {4, 2, 1}});
	mesh->facesIndices_	.push_back({{4, 2, 1}, {3, 1, 1}, {5, 3, 1}});

	//Face 3
	mesh->facesIndices_	.push_back({{4, 3, 2}, {5, 2, 2}, {6, 1, 2}});
	mesh->facesIndices_	.push_back({{6, 1, 2}, {5, 2, 2}, {7, 0, 2}});

	//Face 4
	mesh->facesIndices_	.push_back({{6, 0, 3}, {7, 1, 3}, {0, 2, 3}});
	mesh->facesIndices_	.push_back({{0, 2, 3}, {7, 1, 3}, {1, 3, 3}});

	//Face 5
	mesh->facesIndices_	.push_back({{1, 0, 4}, {7, 1, 4}, {3, 2, 4}});
	mesh->facesIndices_	.push_back({{3, 2, 4}, {7, 1, 4}, {5, 3, 4}});

	//Face 6
	mesh->facesIndices_	.push_back({{6, 0, 5}, {0, 1, 5}, {4, 2, 5}});
	mesh->facesIndices_	.push_back({{4, 2, 5}, {0, 1, 5}, {2, 3, 5}});

	//initialize vertex :
	mesh->vertex_			.push_back({-0.5f, -0.5f,  0.5});
	mesh->vertex_			.push_back({ 0.5f, -0.5f,  0.5});
	mesh->vertex_			.push_back({-0.5f,  0.5f,  0.5});
	mesh->vertex_			.push_back({ 0.5f,  0.5f,  0.5});
	mesh->vertex_			.push_back({-0.5f,  0.5f, -0.5});
	mesh->vertex_			.push_back({ 0.5f,  0.5f, -0.5});
	mesh->vertex_			.push_back({-0.5f, -0.5f, -0.5});
	mesh->vertex_			.push_back({ 0.5f, -0.5f, -0.5});

	//initialize texture coord : 
	mesh->textCoord_		.push_back({ 0.f, 0.f});
	mesh->textCoord_		.push_back({ 1.f, 0.f});
	mesh->textCoord_		.push_back({ 0.f, 1.f});
	mesh->textCoord_		.push_back({ 1.f, 1.f});

	//initialize normal :
	mesh->normal_			.push_back({ 0.f,  0.f,  1.f});
	mesh->normal_			.push_back({ 0.f,  1.f,  0.f});
	mesh->normal_			.push_back({ 0.f,  0.f, -1.f});
	mesh->normal_			.push_back({ 0.f, -1.f,  0.f});
	mesh->normal_			.push_back({ 1.f,  0.f,  0.f});
	mesh->normal_			.push_back({-1.f,  0.f,  0.f});

	return mesh;
}
		
shared_ptr<Mesh> Mesh::createSphere(int latitudeCount, int longitudeCount)
{
	assert(latitudeCount > 2 && longitudeCount > 2);

	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	latitudeCount *= 2.f;

	float latitudeStep = 2.f * M_PI / latitudeCount;
	float longitudeStep = M_PI / longitudeCount;

	//found each point of sphere in function of latitude and longitude count in parameter
	//souce to more informaiton : http://www.songho.ca/opengl/gl_sphere.html
	{
		float xy;
		float latitudeAngle, longitudeAngle;
		float radius = 1.f; 			// radius of 1
		float posX, posY, posZ; 		//position of point
		float s, t;						//few constant for texture position

		for(unsigned int i = 0; i <= static_cast<unsigned int>(longitudeCount); i++)
		{
			longitudeAngle = M_PI / 2.f - i * longitudeStep;    // starting from pi/2 to -pi/2
			xy = radius * cosf(longitudeAngle);
			posZ = radius * sinf(longitudeAngle);

			for(unsigned int j = 0; j <= static_cast<unsigned int>(latitudeCount); j++)
			{
				latitudeAngle = j * latitudeStep;           // starting from 0 to 2pi
				posX = xy * cosf(latitudeAngle);
				posY = xy * sinf(latitudeAngle);
				s = (float)j / latitudeCount;
				t = (float)i / longitudeCount;

				// vertex position (x, y, z)
				mesh->vertex_		.push_back({ posX, posY, posZ});
				mesh->normal_		.push_back({ posX * radius, posY * radius, posZ * radius});
				mesh->textCoord_	.push_back({s, t});
				
				mesh->normal_.back().normalize();
			}
		}
	}

	//generate each indices in function of point create upper
	{
		unsigned int ver1, ver2; //vertices with differente longitude. ver2 = longitude +1

		for(unsigned int i = 0; i < static_cast<unsigned int>(longitudeCount); i++)
		{
			ver1 = i * (latitudeCount + 1);
			ver2 = ver1 + latitudeCount + 1;  //ver2 = longitude + 1
 
			for(unsigned int j = 0; j < static_cast<unsigned int>(latitudeCount); j++, ver1++, ver2++)
			{
				if(i != 0)
				{
					// ver1 -> ver2 -> ver1+1 : like this shema
					// ver1	 <-	ver1+1
					//	|	   /	 
					// ver2	 

					//to create triangle like shema
				    mesh->facesIndices_.push_back({{ver1, ver1, ver1}, {ver2, ver2, ver2}, {ver1 + 1, ver1 + 1, ver1 + 1}});
				}

				if(i != static_cast<unsigned int>(longitudeCount)-1)
				{
					// ver1+1 -> ver2 -> ver2+1 : like this shema
					//			ver1+1
					//		 /	  |
					// ver2	 ->	ver2+1

				    mesh->facesIndices_.push_back({{ver1 + 1, ver1 + 1, ver1 + 1}, {ver2, ver2, ver2}, {ver2 + 1, ver2 + 1, ver2 + 1}});
				}
			}
		}
	}
	
	return mesh;
}

shared_ptr<Mesh> Mesh::createCylindre(unsigned int prescision)
{
	assert(prescision > 2);

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
/*
	// Cylindre contain prescision * 2 + 2
	mesh->getVertices().reserve(prescision * 2 + 2);

	float angleRad = M_PI*2 / prescision;

	//near face

	//middle of near face is in front
	mesh->getVertices().push_back({ { 0.f, 0.f, 0.5f}, { 0.f, 0.f, 1.f}, { 0.f, 1.f}, Rasterizer::getColor4ub()});
	for(unsigned int i = 0; i < prescision; i++)
	{
		mesh->getVertices().push_back({ { 	0.5f * cosf(i * angleRad), 
											0.5f * sinf(i * angleRad),
											0.5f},
											{ cosf(i * angleRad), sinf(i * angleRad), 1.f},
											{ 0.f, 1.f},
											Rasterizer::getColor4ub()});
		mesh->getVertices().back().normal_.normalize();
	}
	
	//far face
	for(unsigned int i = 0; i < prescision; i++)
	{
		mesh->getVertices().push_back({ { 	0.5f * cosf(i * angleRad), 
											0.5f * sinf(i * angleRad),
											-0.5f},
											{ cosf(i * angleRad), sinf(i * angleRad), -1.f},
											{ 0.f, 1.f},
											Rasterizer::getColor4ub()});
		mesh->getVertices().back().normal_.normalize();
	}

	//middle of far face is in back
	mesh->getVertices().push_back({ { 0.f, 0.f, -0.5f}, { 0.f, 0.f, -1.f}, { 0.f, 1.f}, Rasterizer::getColor4ub()});


	//calcul indice of mesh : 

	//near face triangle indice
	for(unsigned int i = 1; i < prescision; i++)
	{
		mesh->getIndices().push_back(0);
		mesh->getIndices().push_back(i);
		mesh->getIndices().push_back(i + 1);
	}
		
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(prescision);
	mesh->getIndices().push_back(1);

	//side face triangle indice
	for(unsigned int i = 1; i < prescision ; i++)
	{
		//face is blit in 2 triangle : 
		mesh->getIndices().push_back(i);
		mesh->getIndices().push_back(i + 1);
		mesh->getIndices().push_back(i + prescision);

		//triangle 2 : 
		mesh->getIndices().push_back(i + prescision);
		mesh->getIndices().push_back(i + prescision + 1);
		mesh->getIndices().push_back(i + 1);
	}

	//face is blit in 2 triangle : 
	mesh->getIndices().push_back(prescision);
	mesh->getIndices().push_back(1);
	mesh->getIndices().push_back(prescision + prescision);

	//triangle 2 : 
	mesh->getIndices().push_back(prescision + prescision);
	mesh->getIndices().push_back(prescision + 1);
	mesh->getIndices().push_back(1);

	float middleFarPointIndice = prescision * 2 + 1;

	//far face triangle indice
	for(unsigned int i = prescision + 1; i < prescision + prescision; i++)
	{
		mesh->getIndices().push_back(middleFarPointIndice);
		mesh->getIndices().push_back(i);
		mesh->getIndices().push_back(i + 1);
	}

	mesh->getIndices().push_back(middleFarPointIndice);
	mesh->getIndices().push_back(prescision + prescision);
	mesh->getIndices().push_back(prescision + 1);
*/
	return mesh;
}

shared_ptr<Mesh> Mesh::loadObj	(const char* path)
{
	assert(path != nullptr);

	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	string warn;
	string err;
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	
	tinyobj::LoadObj(&attrib, &shapes, NULL, &warn, &err, path);
	
	if (!err.empty())
		cerr << "Error loading obj: " << err << " . Path : " << path << endl;
	if (!warn.empty())
		cerr << "Warning loading obj: " << warn << " . Path : " << path << endl;


	mesh->vertex_.reserve(attrib.vertices.size());
	mesh->normal_.reserve(attrib.normals.size());
	mesh->textCoord_.reserve(attrib.texcoords.size());

	for (unsigned int i = 0; i < attrib.vertices.size() ; i+=3)
	{
		mesh->vertex_.push_back({attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]});	
	}

	for (unsigned int i = 0; i < attrib.normals.size() ; i+=3)
	{
		mesh->normal_.push_back({attrib.normals[i], attrib.normals[i + 1], attrib.normals[i + 2]});
	}

	if (attrib.texcoords.empty())
	{
		mesh->textCoord_.push_back({0, 0});
		mesh->textCoord_.push_back({1, 0});
		mesh->textCoord_.push_back({0, 1});
		mesh->textCoord_.push_back({1, 1});
	}
	else
	{	
		for (unsigned int i = 0; i < attrib.texcoords.size() ; i+=2)
		{
			mesh->textCoord_.push_back({attrib.texcoords[i], attrib.texcoords[i + 1]});
		}
	}

	for (const tinyobj::shape_t& shape : shapes)
	{
		bool firstFace = true;
		for (unsigned int i = 0; i < shape.mesh.indices.size() ; i+=3)
		{
			const tinyobj::index_t& indexV1 = shape.mesh.indices[i];
			const tinyobj::index_t& indexV2 = shape.mesh.indices[i + 1];
			const tinyobj::index_t& indexV3 = shape.mesh.indices[i + 2];

			mesh->facesIndices_.push_back({	{(unsigned int)indexV1.vertex_index, attrib.texcoords.empty() ? (firstFace ? 0 : 2) : (unsigned int)indexV1.texcoord_index, (unsigned int)indexV1.normal_index},
											{(unsigned int)indexV2.vertex_index, attrib.texcoords.empty() ? (firstFace ? 1 : 3) : (unsigned int)indexV2.texcoord_index, (unsigned int)indexV2.normal_index},
											{(unsigned int)indexV3.vertex_index, attrib.texcoords.empty() ? (firstFace ? 2 : 1) : (unsigned int)indexV3.texcoord_index, (unsigned int)indexV3.normal_index}});

			firstFace = !firstFace;
		}
	}

/*
	for (const tinyobj::shape_t& shape : shapes)
	{
		for (unsigned int i = 0; i < shape.mesh.indices.size() ; i+=3)
		{
			const tinyobj::index_t& index = shape.mesh.indices[i];
			mesh->facesIndices_.push_back({	{(unsigned int)index.vertex_index  + 0  , 0   , (unsigned int)index.normal_index + 0 },
											{(unsigned int)index.vertex_index + 1, 0, (unsigned int)index.normal_index + 1},
											{(unsigned int)index.vertex_index + 2, 0, (unsigned int)index.normal_index + 2}});
		}
	}*/

	return mesh;
}
