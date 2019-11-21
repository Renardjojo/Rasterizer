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
	Window win (800, 600);
	Renderer ren (win.get(), 800, 600);
	Input input;
	Rasterizer ras;

	bool running = true;

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

		for (float i = 0.f; i < 6.28f; i+= 0.05f)
		{
			ren.clear ();

			Vertex v1 = {0.f * cosf(i), -2.f * sinf(i), 0.f};
			Vertex v2 = {-4.f * cosf(i), 3.f * sinf(i), 0.f};
			Vertex v3 = {5.f * cosf(i), 5.f * sinf(i), 0.f};

			ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);

		ren.swapBuffer ();	

		}
	} 	while (running);
	
	return 0;

}
