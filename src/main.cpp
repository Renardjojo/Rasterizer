#include <iostream>
#include "vec3.hpp"
#include "mat4.hpp"
#include "scene.hpp"
#include "entity.hpp"

using namespace std;
using namespace math;

int main()
{
	Scene scene;

	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 10.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 15.f, 0.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 15.f, 0.f}, {0.f, 0.f, 0.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 10.f, 0.f}, E_primitive3D::NONE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 8.f}, E_primitive3D::CUBE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {3.f, 0.f, 0.f}, E_primitive3D::SPHERE);
	scene.addEntity({1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, {0.f, 2.f, 0.f}, E_primitive3D::CUBE);
	
	return 0;
}
