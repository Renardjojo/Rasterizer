#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <math.h>
#include <memory>
#include "vertex.hpp"

class Mesh
{
	public:
		Mesh ()						= default;
		Mesh (const Mesh& other) 	= default;
		~Mesh () 					= default;

		 /*----------*/
		/* methode  */
	   /*----------*/

		//create cube of size 1 with triangle and return mesh. Cube is centered on the origin
		static std::shared_ptr<Mesh> createCube	();
		
		//create sphere of radius 1 and return it mesh.	Sphere is centered on the origin	
		static std::shared_ptr<Mesh> createSphere(int latitudeCount, int longitudeCount);


		 /*----------*/
		/* accessor */
	   /*----------*/

		 const 	std::vector<Vertex>&	getVertices	() const 	{ return vertices_;}
		 		std::vector<Vertex>&	getVertices	() 			{ return vertices_;}

		 const 	std::vector<int>&		getIndices	() const	{ return indices_;}
		 		std::vector<int>&		getIndices	() 			{ return indices_;}
		 /*----------*/
		/* mutator  */
	   /*----------*/

		 /*----------*/
		/* operator */
	   /*----------*/

		 /*----------*/
		/* convertor*/ 
	   /*----------*/

		//public variable (get and set with no effect for class)

	protected:
		
		std::vector<Vertex> vertices_; //vertex buffer. Local vertices, doesn't change
		std::vector<int>	indices_;  //indices buffer. Define triangle of mesh. It's a suit of triplet index

	private:
};

#endif // _MESH_H
