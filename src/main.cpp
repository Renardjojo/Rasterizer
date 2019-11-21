#include <iostream>
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
	Window win(1024, 700);
	Renderer ren(win.get(), 1024, 700);
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
		Vertex v1 = {-4.f, 4.f, 0.f};
		Vertex v2 = {0.f, -4.f, 0.f};
		Vertex v3 = {4.f, 4.f, 0.f};

		ren.clear();
		ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);
		ren.swapBuffer();

	} while (running);

	return 0;
}
