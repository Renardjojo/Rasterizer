#include "mesh.hpp"

using namespace std;

shared_ptr<Mesh> Mesh::createCube	()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	//cube contain 8 vertex
	mesh->getVertices().reserve(8);

	//cube is center arround local zero
	//Start with point of front face
	mesh->getVertices().push_back({ 0.5f,  0.5f, 0.5});
	mesh->getVertices().push_back({ 0.5f, -0.5f, 0.5});
	mesh->getVertices().push_back({-0.5f, -0.5f, 0.5});
	mesh->getVertices().push_back({-0.5f,  0.5f, 0.5});
	
	//point of back face
	mesh->getVertices().push_back({ 0.5f,  0.5f, -0.5});
	mesh->getVertices().push_back({ 0.5f, -0.5f, -0.5});
	mesh->getVertices().push_back({-0.5f, -0.5f, -0.5});
	mesh->getVertices().push_back({-0.5f,  0.5f, -0.5});

	//cube contain 12 triangles this 3 indices. Cube contain 36 indices
	mesh->getIndices().reserve(36);

	//front
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(1);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(3);

	//left
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(2);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(7);

	//back
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(6);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(4);

	//up
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(7);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(3);
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(0);

	//right
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(4);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(5);
	mesh->getIndices().push_back(0);
	mesh->getIndices().push_back(1);

	//down
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
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	float latitudeStep = 2.f * M_PI / latitudeCount;
	float longitudeStep = M_PI / longitudeCount;

	//found each point of sphere in function of latitude and longitude count in parameter
	{
		float xy;
		float latitudeAngle, longitudeAngle;
		float radius = 1.f; // radius of 1

		for(unsigned int i = 0; i <= static_cast<unsigned int>(longitudeCount); i++)
		{
			longitudeAngle = M_PI / 2.f - i * longitudeStep;    // starting from pi/2 to -pi/2
			xy = radius * cosf(longitudeAngle);

			for(unsigned int j = 0; j <= static_cast<unsigned int>(latitudeCount); j++)
			{
				latitudeAngle = j * latitudeStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				mesh->getVertices().push_back({	xy * cosf(latitudeAngle), 
											xy * sinf(latitudeAngle) , 
											radius * sinf(longitudeAngle)});
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
