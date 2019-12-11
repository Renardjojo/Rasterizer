#include <iostream>
#include <memory>
#include <math.h>
#include "vec.hpp"
#include "mat.hpp"
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
	Window 			win (1200, 800);
	Renderer 		ren (win.get(), 1200, 800);
	Input 			input;
	Scene 			scene;
	TimeManager		time;

	bool 			running = true;

	Rasterizer::setColor4ub(255, 255, 0, 255);
	//int id = scene.addEntity({2.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	int light = scene.addEntity({0.f, 0.f, -2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	Rasterizer::setColor4ub(255, 0, 0, 255);
	//int id3 = scene.addEntity({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CYLINDRE);
	//int id4 = scene.addEntity({1.f, 0.f, -10.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "./media/teapot.obj");
	int id3 = scene.addEntity({0.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {0.13f, 0.13f, 0.13f}, "./media/Crash.obj");
	scene.addLigth({1.f, 1.f, 1.f}, .2f, 1.f, 1.f);
	//scene.getEntity(id4).setTexture("./media/marber.jpg");
	scene.getEntity(id3).setTexture("./media/crash5f.png");
	scene.getEntity(light).setTexture("./media/sp.png");

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
		if (input.keyboard.isDown[SDL_SCANCODE_F6])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, true);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
		}

		if (input.keyboard.isDown[SDL_SCANCODE_SPACE])
		{
			time.dtf_ = 0.f;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_W])
		{
			scene.camPos_.z -= 20 * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_S])
		{
			scene.camPos_.z += 20 * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_UP])
		{
			scene.camDir_.x += 0.7f * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_DOWN])
		{
			scene.camDir_.x -= 0.7f * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_LEFT])
		{
			scene.camDir_.y += 0.7f * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_RIGHT])
		{
			scene.camDir_.y -= 0.7f * time.dtf_;
		}

		float camScale = static_cast<float>(input.mouse.wheel_scrolling * 0.1f + 1.f);
		scene.camScale_ = {camScale, camScale, camScale};

		static float rot = 0.f;
		rot += .5f * time.dtf_;

		Rasterizer::setColor4ub(0, 255, 255, 0);
		scene.getEntity(light).getTransform().setOrigin({2.f * cos(rot), 0.f, -40.f + 20.f * sin(rot)});
		/*scene.getEntity(id4).getTransform().rotate({1.f* time.dtf_, 1.5f* time.dtf_, 0.f});	
		scene.getEntity(id4).getTransform().translate({5 * cos(rot) * time.dtf_, 0.f, 5 * sin(rot) * time.dtf_});*/

		//(void)id4;

		//std::cout << __FILE__ << ":" <<__LINE__ << ": " << scene.getLight(1).getPosition().z << std::endl;

		scene.getLight(1).setPosition({2.f * cos(rot), 0.f, -40.f + 20.f * sin(rot)});

		//display
		ren.clear ();

		scene.draw(ren);

		ren.swapBuffer ();

		time.update();

		if (time.secondIsPassing())
		{
			std::cout << "NbTriangle Render this frame : " << Rasterizer::getNbTringleRender()<< std::endl;
		}
		Rasterizer::resetNbTriangleRender();

	} 	while (running);

	return 0;

}
