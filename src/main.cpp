#include <iostream>
#include <math.h>
#include "vec3.hpp"
#include "mat4.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "rasterizer.hpp"
#include "vertex.hpp"
#include "input.hpp"

using namespace std;
using namespace math;

int main()
{
	Window 			win (800, 600);
	Renderer 		ren (win.get(), 800, 600);
	Input 			input;
	Rasterizer 		ras;
	Scene 			scene;
	bool 			running = true;

	//int id = scene.addEntity({2.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {2.f, 2.f, 2.f}, -1, E_primitive3D::SPHERE);
//	int id2 = scene.addEntity({-2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, -1, E_primitive3D::SPHERE);
	//int id3 = scene.addEntity({-2.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {2.f, 2.f, 2.f}, -1, E_primitive3D::CUBE);
	int id4 = scene.addEntity({2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, -1, E_primitive3D::CUBE);


do
	{
		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if (input.keyboard.escIsRelease)
		{
			running = false;
			break;
		}

	//	scene.getEntity(id).getTransform().rotate({0.01f, 0.f, 0.05f});
	//	scene.getEntity(id2).getTransform().rotate({0.05f, 0.f, 0.01f});
	//	scene.getEntity(id3).getTransform().rotate({0.02f, 0.05f, 0.002f});
		scene.getEntity(id4).getTransform().rotate({0.005f, 0.005f, 0.005f});	
		

		//display
		ren.clear ();

		scene.draw(ren.getDrawBuffer());
		ren.swapBuffer ();

		SDL_Delay((1.f /60.f) * 1000);

	} 	while (running);

	return 0;

}
