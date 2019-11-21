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
		//diaply

=======
		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if(input.keyboard.escIsRelease)
		{
			running = false; 
			break;
		}

		//display
		ren.clear ();

		Vertex v1 = {-1.f, 0.f, 0.f};
		Vertex v2 = {0.f, 1.f, 0.f};
		Vertex v3 = {1.f, 0.f, 0.f};
>>>>>>> 7b63f122d42087b5a3bf59f0615980927660c021

		for (int i = 0; i < 100; i++)
		{
			Vertex v1 = {100.f, 100.f, 0.f};
			Vertex v2 = {300.f, 500.f, 0.f};
			Vertex v3 = {500.f, 100.f, 0.f};

			ren.clear ();
			ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);
			ren.swapBuffer ();
		}
	

	} 	while (running);
	
	return 0;
}
