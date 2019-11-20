#include <iostream>
#include "vec3.hpp"
#include "mat4.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "rasterizer.hpp"
#include "vertex.hpp"


using namespace std;
using namespace math;

int main()
{
	Window win (1024, 700);
	Renderer ren (win.get(), 1024, 700);
	Rasterizer ras;

	bool running = false;

	do
	{
		for (unsigned int i = 0; i < 200; i++)
		{
			//ren.clear ();

			Vertex v1 = {100.f + i, 100.f, 0.f};
			Vertex v2 = {300.f + i, 500.f, 0.f};
			Vertex v3 = {500.f + i, 100.f, 0.f};

			ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v3);

			ren.swapBuffer ();			
		}

	} 	while (running);
	
	return 0;
}
