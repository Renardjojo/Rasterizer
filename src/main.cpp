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
	//int skyBox = scene.addEntity({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {10.f, 10.f, 10.f}, "./media/skybox.obj");
	int light = scene.addEntity({0.f, 0.f, -2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
	Rasterizer::setColor4ub(255, 0, 0, 255);
	//int teaPot = scene.addEntity({1.f, 0.f, -10.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "./media/teapot.obj");
	int character = scene.addEntity({0.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {0.13f, 0.13f, 0.13f}, "./media/Crash.obj");
	scene.addLigth({1.f, 1.f, 1.f}, .2f, 0.8f, 0.7f);
	//scene.getEntity(teaPot).setTexture("./media/marber.jpg");
	scene.getEntity(character).setTexture("./media/crash5f.png");
	scene.getEntity(light).setTexture("./media/sp.png");
	//scene.getEntity(skyBox).setTexture("./media/cube3.png");

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

		if (input.keyboard.isDown[SDL_SCANCODE_F7])
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, false);
		}
		else
		{
			Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
		}

		if (input.keyboard.isDown[SDL_SCANCODE_UP])
		{
			Vec3 vec = scene.playerDir_ * (20.f * time.dtf_);
			scene.camPos_ += vec;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_DOWN])
		{
			Vec3 vec = scene.playerDir_ * (20.f * time.dtf_);
			scene.camPos_ -= vec;
		}

	/*	if (input.keyboard.isDown[SDL_SCANCODE_LEFT])
		{
			Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
			vecDirPlayer.rotate(-0.7f * time.dtf_ * 180 / M_PI);
			scene.playerDir_.x = vecDirPlayer.x;
			scene.playerDir_.z = vecDirPlayer.y;

			scene.camOrientation_.y += 0.7f * time.dtf_;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_RIGHT])
		{
			Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
			vecDirPlayer.rotate(0.7f * time.dtf_ * 180 / M_PI);
			scene.playerDir_.x = vecDirPlayer.x;
			scene.playerDir_.z = vecDirPlayer.y;

			scene.camOrientation_.y -= 0.7f * time.dtf_;
		}*/

		if (input.keyboard.isDown[SDL_SCANCODE_LEFT])
		{
			Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
			vecDirPlayer.rotate(-input.mouse.motion.x * 0.1f * time.dtf_ * 180 / M_PI).rotated90();
			Vec3 playerDirOrtho {vecDirPlayer.x, scene.playerDir_.y, vecDirPlayer.y};

			playerDirOrtho *= (20.f * time.dtf_);
			scene.camPos_ -= playerDirOrtho;
		}

		if (input.keyboard.isDown[SDL_SCANCODE_RIGHT])
		{
			Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
			vecDirPlayer.rotate(-input.mouse.motion.x * 0.1f * time.dtf_ * 180 / M_PI).rotated90();
			Vec3 playerDirOrtho {vecDirPlayer.x, scene.playerDir_.y, vecDirPlayer.y};

			playerDirOrtho *= (20.f * time.dtf_);
			scene.camPos_ += playerDirOrtho;
		}

		if (input.mouse.motion.y != 0)
		{
			scene.camOrientation_.x -= input.mouse.motion.y * 0.1f * time.dtf_ ;
		}

		if (input.mouse.motion.x != 0)
		{
			Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
			vecDirPlayer.rotate(input.mouse.motion.x * 0.1f * time.dtf_ * 180 / M_PI);
			scene.playerDir_.x = vecDirPlayer.x;
			scene.playerDir_.z = vecDirPlayer.y;

			scene.camOrientation_.y -= input.mouse.motion.x * 0.1f * time.dtf_;
		}

		static int exFrameWheelVal = input.mouse.wheel_scrolling;

		if (input.mouse.wheel_scrolling != exFrameWheelVal)
		{
			if(input.mouse.wheel_scrolling > exFrameWheelVal)
			{
				scene.zoom(0.1f);
			}
			else
			{
				scene.zoom(-0.1f);
			}
			
			exFrameWheelVal = input.mouse.wheel_scrolling;
		}

		static float rot = 0.f;


		if (!input.keyboard.isDown[SDL_SCANCODE_SPACE])
		{
			rot += .5f * time.dtf_;

			Rasterizer::setColor4ub(0, 255, 255, 0);
			scene.getEntity(light).getTransform().setOrigin({2.f * cos(rot), 0.f, -40.f + 20.f * sin(rot)});
			//scene.getEntity(skyBox).getTransform().rotate({1.f* time.dtf_, 1.5f* time.dtf_, 0.f})
			//scene.getEntity(character).getTransform().translate({5 * cos(rot) * time.dtf_, 0.f, 5 * sin(rot) * time.dtf_});

			//scene.getEntity(skyBox).getTransform().scale({0.5f * time.dtf_, 0.5f * time.dtf_, 0.5f * time.dtf_});


			//std::cout << __FILE__ << ":" <<__LINE__ << ": " << scene.getLight(1).getPosition().z << std::endl;

			scene.getLight(1).setPosition({2.f * cos(rot), 0.f, -40.f + 20.f * sin(rot)});
		}
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
