#include <iostream>
#include <memory>
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
#include "time.hpp"

using namespace std;
using namespace math;

int main()
{
	Window 			win (800, 600);
	Renderer 		ren (win.get(), 800, 600);
	Input 			input;
	Scene 			scene;
	TimeManager		time;
	bool 			running = true;

	int id = scene.addEntity({2.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	int id2 = scene.addEntity({-2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	int id3 = scene.addEntity({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);
	int id4 = scene.addEntity({2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);

	//for (unsigned int i = 0; i < 50; i ++)
	//	scene.addEntity({2.f, 2.f, -5.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, -1, E_primitive3D::SPHERE);



do
	{
		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if (input.keyboard.escIsRelease)
		{
			running = false;
			break;
		}

		scene.getEntity(id).getTransform().rotate({0.1f * time.dtf_, 0.f, 0.5f* time.dtf_});
		scene.getEntity(id).getTransform().translate({0.f * time.dtf_, 0.f, 0.2f* time.dtf_});
		scene.getEntity(id2).getTransform().rotate({0.5f* time.dtf_, 0.f, 0.1f* time.dtf_});
		scene.getEntity(id3).getTransform().rotate({0.5f* time.dtf_, 0.5f* time.dtf_, 0.f* time.dtf_});
		scene.getEntity(id4).getTransform().rotate({0.05f* time.dtf_, 0.05f* time.dtf_, 0.05f* time.dtf_});	

		//display
		ren.clear ();

		scene.draw(ren.getDrawBuffer());
		ren.swapBuffer ();

		time.update();

	} 	while (running);

	return 0;

}
