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

	bool running = true;

	while (running)
	{
		//ren.clear ();

		Vertex v1 = {1.f, 1.f, 1.f};
		Vertex v2 = {1.f, 10.f, 1.f};

		ras.drawTriangle(ren.getDrawBuffer(), v1, v2, v1);

		ren.swapBuffer ();
	}
	
	return 0;
}
