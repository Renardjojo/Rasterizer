#include <iostream>
#include "vec3.hpp"
#include "mat4.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "renderer.hpp"


using namespace std;
using namespace math;

int main()
{
	Window win (1024, 700);
	Renderer ren (win.get(), 1024, 700);
	bool running = true;

	while (running)
	{
		ren.clear ();


		ren.swapBuffer ();
	}
	
	return 0;
}
