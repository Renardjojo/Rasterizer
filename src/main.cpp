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
	Window win (1024, 700);
	Renderer ren (win.get(), 1024, 700);
	Input input;
	Rasterizer ras;

	bool running = true;

	do
	{
<<<<<<< HEAD
		for (unsigned int i = 0; i < 400; i++)
		{
			ren.clear ();
=======
		//diaply
		ren.clear ();
>>>>>>> 46b11e112034aaca41ca62aae378f24cc0ace1c4

		Vertex v1 = {100.f, 100.f, 0.f};
		Vertex v2 = {300.f, 500.f, 0.f};
		Vertex v3 = {500.f, 100.f, 0.f};

		ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);

		ren.swapBuffer ();

		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if(input.keyboard.escIsRelease)
			running = false;

	} 	while (running);
	
	return 0;
}
