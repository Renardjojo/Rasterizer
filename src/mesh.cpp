#include "mesh.hpp"
#include "rasterizer.hpp"
#include <cassert>

using namespace math;
using namespace std;

shared_ptr<Mesh> Mesh::createCube	()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	// Cube contain 8 vertex
	mesh->getVertices().reserve(8);

	// Cube is center arround local zero
	// Start with point of front face
	mesh->getVertices().push_back({{0.5f,  0.5f, 0.5}, {1.f, 1.f, 1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{0.5f, -0.5f, 0.5}, {1.f, -1.f, 1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{-0.5f, -0.5f, 0.5}, {-1.f, -1.f, 1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{-0.5f,  0.5f, 0.5}, {-1.f, 1.f, 1.f}, Rasterizer::getColor4ub()});
	
	// Point of back face
	mesh->getVertices().push_back({{0.5f,  0.5f, -0.5}, {1.f, 1.f, -1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{0.5f, -0.5f, -0.5}, {1.f, -1.f, -1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{-0.5f, -0.5f, -0.5}, {-1.f, -1.f, -1.f}, Rasterizer::getColor4ub()});
	mesh->getVertices().push_back({{-0.5f,  0.5f, -0.5}, {-1.f, 1.f, -1.f}, Rasterizer::getColor4ub()});

	// Cube contain 12 triangles this 3 indices. Cube contain 36 indices
	mesh->getIndices().reserve(36);

	// Front
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(1);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(3);

	// Left
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(7);

	// Back
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(4);

	// Up
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(0);

	// Right
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(1);

	// Down
	mesh->getIndices().push_back(1);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(1);
	mesh->getIndices().push_back(2);

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
	{
		float xy;
		float latitudeAngle, longitudeAngle;
		float radius = 1.f; 			// radius of 1
		float posX, posY, posZ; 		//position of point

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

				// vertex position (x, y, z)
				mesh->getVertices().push_back({ { posX, posY, posZ},
												{ posX * radius, posY * radius, posZ * radius},
												Rasterizer::getColor4ub()}); //point * radius
				
				mesh->getVertices().back().normal_.normalize();
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

				    mesh->getIndices().push_back(ver1);
				    mesh->getIndices().push_back(ver2);
				    mesh->getIndices().push_back(ver1 + 1); //to create triangle like shema
				}

				if(i != static_cast<unsigned int>(longitudeCount)-1)
				{
					// ver1+1 -> ver2 -> ver2+1 : like this shema
					//			ver1+1
					//		 /	  |
					// ver2	 ->	ver2+1

				    mesh->getIndices().push_back(ver1 + 1);
				    mesh->getIndices().push_back(ver2);
				    mesh->getIndices().push_back(ver2 + 1);
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

	// Cylindre contain prescision * 2 + 2
	mesh->getVertices().reserve(prescision * 2 + 2);

	float angleRad = M_PI*2 / prescision;

	//near face

	//middle of near face is in front
	mesh->getVertices().push_back({ { 0.f, 0.f, 0.5f}, { 0.f, 0.f, 1.f}, Rasterizer::getColor4ub()});
	for(unsigned int i = 0; i < prescision; i++)
	{
		mesh->getVertices().push_back({ { 	0.5f * cosf(i * angleRad), 
											0.5f * sinf(i * angleRad),
											0.5f},
											{ cosf(i * angleRad), sinf(i * angleRad), 1.f},
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
											Rasterizer::getColor4ub()});
		mesh->getVertices().back().normal_.normalize();
	}

	//middle of far face is in back
	mesh->getVertices().push_back({ { 0.f, 0.f, -0.5f}, { 0.f, 0.f, -1.f}, Rasterizer::getColor4ub()});


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

	return mesh;
}
