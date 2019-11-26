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

	Rasterizer::setColor4ub(255, 255, 0, 255);
	int id = scene.addEntity({2.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	int id2 = scene.addEntity({-2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);

	Rasterizer::setColor4ub(255, 0, 0, 255);
	int id3 = scene.addEntity({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);
	int id4 = scene.addEntity({2.f, -2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);
	scene.addLigth({1.f, 1.f, 1.f}, 0.9f, 0.2f, 1.f);

do
	{
		//update
		input.pollEvent(SDL_GetWindowID(win.get()));

		if (input.keyboard.escIsRelease)
		{
			running = false;
			break;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_F1])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, true);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
		}

		if (input.keyboard.isDown[SDL_SCANCODE_F2])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, true);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
		}


		if (input.keyboard.isDown[SDL_SCANCODE_F3])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, true);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
		}

		if (input.keyboard.isDown[SDL_SCANCODE_F4])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, true);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
		}

		if (input.keyboard.isDown[SDL_SCANCODE_F5])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, false);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
		}

/*
		Rasterizer::setColor4ub(0, 255, 255, 0);
		scene.getEntity(id).getTransform().rotate({0.1f * time.dtf_, 0.f, 0.5f* time.dtf_});
		scene.getEntity(id).getTransform().translate({0.f * time.dtf_, 0.f, 0.2f* time.dtf_});
		scene.getEntity(id2).getTransform().rotate({0.5f* time.dtf_, 0.f, 0.1f* time.dtf_});
		scene.getEntity(id3).getTransform().rotate({0.5f* time.dtf_, 0.5f* time.dtf_, 0.f* time.dtf_});
		scene.getEntity(id4).getTransform().rotate({0.05f* time.dtf_, 0.05f* time.dtf_, 0.05f* time.dtf_});	
*/
		id = id2 = id3 = id4;
		(void)id;

		static float rot = 0.f;
		rot += 0.05f;


		//scene.getLight(1).setDiffuseIntensity(abs(cosf(rot)));
		scene.getLight(1).setPosition({cosf(rot), 1.f, sin(rot)});

		//display
		ren.clear ();

		scene.draw(ren.getDrawBuffer());
		ren.swapBuffer ();

		time.update();

	} 	while (running);

	return 0;

}
