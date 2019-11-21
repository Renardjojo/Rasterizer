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

	scene.addEntity({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, -1, E_primitive3D::CUBE);

do
	{
		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if (input.keyboard.escIsRelease)
		{
			running = false;
			break;
		}

		//display
		ren.clear ();

		static float rot = 0.f;
		rot += 0.1;

		Vertex v1(0.f + cosf(rot), 3.f + sinf(rot), 0.f);
		Vertex v2(-3.f + cosf(rot), 0.f + sinf(rot), 0.f);
		Vertex v3(3.f + cosf(rot), 0.f + sinf(rot), 0.f);

		ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);

		//scene.draw(ren.getDrawBuffer());
		ren.swapBuffer ();	

		SDL_Delay((1.f /60.f) * 1000);

	} 	while (running);
	
	return 0;

}
