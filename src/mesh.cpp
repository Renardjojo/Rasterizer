#include "mesh.hpp"

using namespace std;

shared_ptr<Mesh> Mesh::createCube	()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	//cube contain 8 vertex
	mesh->getVertices().reserve(8);

	//cube is center arround local zero
	//Start with point of front face
	mesh->getVertices()[0] = { 0.5f,  0.5f, 0.5};
	mesh->getVertices()[1] = { 0.5f, -0.5f, 0.5};
	mesh->getVertices()[2] = {-0.5f, -0.5f, 0.5};
	mesh->getVertices()[3] = {-0.5f,  0.5f, 0.5};
	
	//point of back face
	mesh->getVertices()[4] = { 0.5f,  0.5f, -0.5};
	mesh->getVertices()[5] = { 0.5f, -0.5f, -0.5};
	mesh->getVertices()[6] = {-0.5f, -0.5f, -0.5};
	mesh->getVertices()[7] = {-0.5f,  0.5f, -0.5};


	//cube contain 12 triangles this 3 indices. Cube contain 36 indices
	mesh->getIndices().reserve(36);

	//front
	mesh->getIndices()[0]  = 0;
	mesh->getIndices()[1]  = 1;
	mesh->getIndices()[2]  = 2;
	mesh->getIndices()[3]  = 2;
	mesh->getIndices()[4]  = 0;
	mesh->getIndices()[5]  = 3;

	//left
	mesh->getIndices()[6]  = 3;
	mesh->getIndices()[7]  = 2;
	mesh->getIndices()[8]  = 6;
	mesh->getIndices()[9]  = 6;
	mesh->getIndices()[10] = 3;
	mesh->getIndices()[11] = 7;

	//back
	mesh->getIndices()[12] = 7;
	mesh->getIndices()[13] = 6;
	mesh->getIndices()[14] = 5;
	mesh->getIndices()[15] = 5;
	mesh->getIndices()[16] = 7;
	mesh->getIndices()[17] = 4;

	//up
	mesh->getIndices()[18] = 4;
	mesh->getIndices()[19] = 7;
	mesh->getIndices()[20] = 3;
	mesh->getIndices()[21] = 3;
	mesh->getIndices()[22] = 4;
	mesh->getIndices()[23] = 0;

	//right
	mesh->getIndices()[24] = 0;
	mesh->getIndices()[25] = 4;
	mesh->getIndices()[26] = 5;
	mesh->getIndices()[27] = 5;
	mesh->getIndices()[28] = 0;
	mesh->getIndices()[29] = 1;

	//down
	mesh->getIndices()[30] = 1;
	mesh->getIndices()[31] = 5;
	mesh->getIndices()[32] = 6;
	mesh->getIndices()[33] = 6;
	mesh->getIndices()[34] = 1;
	mesh->getIndices()[35] = 2;

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
