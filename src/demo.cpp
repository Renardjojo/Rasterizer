#include "demo.hpp"

using namespace std;
using namespace math;




void runDemo ()
{
    Window 			win         (1200, 800);
	Renderer 		ren         (win.get(), 1200, 800);
	Input 			input;
    TimeManager		time;
    Scene           scene;
    bool            f1IsPress   (false);
    bool            f2IsPress   (false);
    bool            f3IsPress   (false);
    bool            f4IsPress   (false);
    bool            f5IsPress   (false);
    bool            f6IsPress   (false);
    bool            f7IsPress   (false);
    bool            f8IsPress   (false);
    bool            f9IsPress   (false);
    bool            f10IsPress  (false);
    bool            f11IsPress  (false);
    bool            f12IsPress  (false);
    bool            IsInOrtho   (false);

    bool            PauseIsPress   (false);
    bool            IsInPause      (false);

	bool 			running     (true);
    DemoFlag        demo        (E_DemoFlag::V0_FREE);

    switch (demo)
    {
        case E_DemoFlag::V0_FREE:                   initSceneDemoFree (scene, win);         break;
        case E_DemoFlag::V1_COLOR:                  initSceneDemoColor (scene, win);        break;
        case E_DemoFlag::V2_ZBUFFER:                initSceneDemoZBuffer (scene, win);      break;
        case E_DemoFlag::V3_4_LIGTH:                initSceneDemoLight (scene, win);        break;
        case E_DemoFlag::V5_PROJECTION:             initSceneDemoProjection (scene, win);   break;
        case E_DemoFlag::V6_TEXTURE:                initSceneDemoTexturing (scene, win);    break;
        case E_DemoFlag::V8_ALPHA_BACKFACE_CULLING: initSceneDemoAlpha (scene, win);        break;
        case E_DemoFlag::V9_AA:                     initSceneDemoAA (scene, win);           break;
        default: break;
    }

	do
	{
        if (input.keyboard.escIsRelease)
        {
            running = false;
            break;
        }

        //Manage input
        if (input.keyboard.isDown[SDL_SCANCODE_F1] && !f1IsPress)
        {
            int idNextDemo = static_cast<int>(demo) + 1;
            demo = static_cast<DemoFlag>(idNextDemo > 7 ? 0 : idNextDemo);

            scene.clear();

            switch (demo)
            {
                case E_DemoFlag::V0_FREE:                   initSceneDemoFree (scene, win);         break;
                case E_DemoFlag::V1_COLOR:                  initSceneDemoColor (scene, win);        break;
                case E_DemoFlag::V2_ZBUFFER:                initSceneDemoZBuffer (scene, win);      break;
                case E_DemoFlag::V3_4_LIGTH:                initSceneDemoLight (scene, win);        break;
                case E_DemoFlag::V5_PROJECTION:             initSceneDemoProjection (scene, win);   break;
                case E_DemoFlag::V6_TEXTURE:                initSceneDemoTexturing (scene, win);    break;
                case E_DemoFlag::V8_ALPHA_BACKFACE_CULLING: initSceneDemoAlpha (scene, win);        break;
                case E_DemoFlag::V9_AA:                     initSceneDemoAA (scene, win);           break;
                default: break;
            }
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F2] && !f2IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_EDGE);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F3] && !f3IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F4] && !f4IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F5] && !f5IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_NORMAL);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F6] && !f6IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F7] && !f7IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL);
            Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F8] && !f8IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING);
            Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F9] && !f9IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING);
            Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F10] && !f10IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME);
            Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F11] && !f11IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME);
            Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F11] && !f11IsPress)
        {
            bool status = Rasterizer::getSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME);
            Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, !status);
        }

        if (input.keyboard.isDown[SDL_SCANCODE_F12] && !f12IsPress)
        {
            IsInOrtho = !IsInOrtho;

            if(IsInOrtho)
            {
                Rasterizer::loadOrthoMatrix(-1, 1, -1, 1, 0.01, 100);
            }
            else
            {
                Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);
            }
            
        }


        f1IsPress = input.keyboard.isDown[SDL_SCANCODE_F1];
        f2IsPress = input.keyboard.isDown[SDL_SCANCODE_F2];
        f3IsPress = input.keyboard.isDown[SDL_SCANCODE_F3];
        f4IsPress = input.keyboard.isDown[SDL_SCANCODE_F4];
        f5IsPress = input.keyboard.isDown[SDL_SCANCODE_F5];
        f6IsPress = input.keyboard.isDown[SDL_SCANCODE_F6];
        f7IsPress = input.keyboard.isDown[SDL_SCANCODE_F7];
        f8IsPress = input.keyboard.isDown[SDL_SCANCODE_F8];
        f9IsPress = input.keyboard.isDown[SDL_SCANCODE_F9];
        f10IsPress = input.keyboard.isDown[SDL_SCANCODE_F10];
        f11IsPress = input.keyboard.isDown[SDL_SCANCODE_F11];
        f12IsPress = input.keyboard.isDown[SDL_SCANCODE_F12];

        //update
        input.pollEvent(SDL_GetWindowID(win.get()));

        if (input.keyboard.isDown[SDL_SCANCODE_UP] || input.keyboard.isDown[SDL_SCANCODE_W])
        {
            Vec3 vec = scene.playerDir_ * (20.f * time.dtf_);
            scene.camPos_ += vec;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_DOWN] || input.keyboard.isDown[SDL_SCANCODE_S])
        {
            Vec3 vec = scene.playerDir_ * (20.f * time.dtf_);
            scene.camPos_ -= vec;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_SPACE])
        {
            scene.camPos_.y += 20.f * time.dtf_;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_LCTRL ])
        {
            scene.camPos_.y -= 20.f * time.dtf_;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_LEFT] || input.keyboard.isDown[SDL_SCANCODE_A])
        {
            Vec2 vecDirPlayer = {scene.playerDir_.x, scene.playerDir_.z};
            vecDirPlayer.rotate(-input.mouse.motion.x * 0.1f * time.dtf_ * 180 / M_PI).rotated90();
            Vec3 playerDirOrtho {vecDirPlayer.x, scene.playerDir_.y, vecDirPlayer.y};

            playerDirOrtho *= (20.f * time.dtf_);
            scene.camPos_ -= playerDirOrtho;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_RIGHT] || input.keyboard.isDown[SDL_SCANCODE_D])
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

        //update time

        if (input.keyboard.isDown[SDL_SCANCODE_P] && !PauseIsPress)
        {
            IsInPause = !IsInPause;
        }

        if (input.keyboard.isDown[SDL_SCANCODE_BACKSPACE])
        {
           time.dtf_ = -time.dtf_;
        } 
        else if (IsInPause)
        {
            time.dtf_ = 0.f;
        }

        PauseIsPress = input.keyboard.isDown[SDL_SCANCODE_P];

        //Run demo
        switch (demo)
        {
            case E_DemoFlag::V0_FREE:
                runDemoFree (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V1_COLOR:
                runDemoColor (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V2_ZBUFFER:
                runDemoZBuffer (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V3_4_LIGTH:
                runDemoLight    (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V5_PROJECTION:
                runDemoProjection (scene, win, ren, input, time);
            break;
            case E_DemoFlag::V6_TEXTURE:
                runDemoTexturing (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V8_ALPHA_BACKFACE_CULLING:
                runDemoAlpha (scene, win, ren, input, time);
            break;

            case E_DemoFlag::V9_AA:
                runDemoAA (scene, win, ren, input, time);
            break;
            
            default:
            break;
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
}

void initSceneDemoFree (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

 	scene.addEntity({0.f, 0.f, -2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);                 //light
	scene.addEntity({10.f, 0.5f, -29.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");           //teapot1
	scene.addEntity({-10.f, 0.5f, -29.f}, {0.f, M_PI, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");         //teapot2
	scene.addEntity({0.f, 4.5f, -29.f}, {0.f, -M_PI_2, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");        //teapot3
	scene.addEntity({0.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {0.13f, 0.13f, 0.13f}, "./media/obj/crash.obj");       //character

	scene.addLigth({0.f, 0.f, -30.f}, 0.2f, 0.7f, 0.9f);
}

void initSceneDemoColor (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

	scene.addEntity({0.f, 0.f, -5.f}, {0.f, 0.f, 0.f}, {3.f, 3.f, 3.f}, E_primitive3D::TRIANGLE);  //triangle
}

void initSceneDemoZBuffer (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 30);

 	scene.addEntity({-0.5f, 0.f, -5.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);                 //Cube
    scene.addEntity({ 0.5f, 0.f, -5.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);               //Sphere
    scene.addEntity({ 0.5f, 0.f, -5.f}, {0.f, 0.f, 0.f}, {0.2f, 0.2f, 0.2f}, E_primitive3D::SPHERE);            //Sphere2

	scene.addLigth({0.f, 0.f, 0.f}, 1.f, 1.f, 1.f);
}

void initSceneDemoLight (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

 	scene.addEntity({0.f, 0.f, -2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);                         //light
	int idTeaPot = scene.addEntity({10.f, 0.5f, -29.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");    //teapot1
	scene.addEntity({-10.f, 0.5f, -29.f}, {0.f, M_PI, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");                 //teapot2
	scene.addEntity({0.f, 4.5f, -29.f}, {0.f, -M_PI_2, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");                //teapot3
	int crashId = scene.addEntity({0.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {0.13f, 0.13f, 0.13f}, "./media/obj/crash.obj"); //character
	scene.addEntity({5.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {3.f, 3.f, 3.f}, E_primitive3D::SPHERE);                       //Sphere
	scene.addEntity({-5.f, -7.f, -30.f}, {0.f, 0.f, 0.f}, {3.f, 3.f, 3.f}, E_primitive3D::CUBE);                        //Cube
	scene.addEntity({0.f, -7.f, -30.f}, {M_PI, 0.f, 0.f}, {50.f, 1.f, 50.f}, E_primitive3D::CUBE);                      //Ground

    scene.getEntity(idTeaPot).getpMaterial()->lightComp_.Ks = {0.f, 1.f, 0.f};
    scene.getEntity(crashId).getpMaterial()->lightComp_.Ks = {0.f, 1.f, 0.f};

	int light = scene.addLigth({0.f, 0.f, -30.f}, 0.1f, 1.f, 1.f);
	scene.getLight(light).setDiffuseColor(1.f, 0.f, 0.f);
	scene.getLight(light).setSpecularColor(1.f, 1.f, 0.f);
}

void initSceneDemoProjection (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

    srand(SDL_GetTicks());

//	scene.addEntity({0.f, 0.f, -30.f}, {M_PI, 0.f, 0.f}, {50.f, 1.f, 50.f}, E_primitive3D::CUBE);     //Ground

    //create 10 cubes
    for (float c = 0.f; c != 100.f; c++)
    {
        float posX = rand() % 100 - 50.f;
        scene.addEntity({posX, 1.f, -c}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);
    }

    //create 10 spheres
    for (float s = 0.f; s != 100.f; s++)
    {
        float posX = rand() % 100 - 50.f;
        scene.addEntity({posX, 1.f, -s}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);
    }    
}

void initSceneDemoTexturing (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

    int idSun =   scene.addEntity({0.f, 0.f, -40.f}, {0.f, 0.f, 0.f}, {3.f, 3.f, 3.f}, E_primitive3D::SPHERE);      //Sun
    int idEarth = scene.addEntity({0.f, 0.f, -40.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);      //Earth
    int idMoon  = scene.addEntity({0.f, 0.f, -40.f}, {0.f, 0.f, 0.f}, {0.3f, 0.3f, 0.3f}, E_primitive3D::SPHERE);   //Moon

    auto itMatSun = Material::addMaterial("media/material/sun.mtl");
    auto itMatMoon = Material::addMaterial("media/material/moon.mtl");
    auto itMatEarth = Material::addMaterial("media/material/earth.mtl");

    scene.getEntity(idSun).setMaterial(itMatSun->second.get());
    scene.getEntity(idMoon).setMaterial(itMatMoon->second.get());
    scene.getEntity(idEarth).setMaterial(itMatEarth->second.get());

    //create asteroid
    for (float c = 0.f; c < 2000.f; c++)
    {
        float posX = ((rand() % 500) / 100.f);
        float posZ = ((rand() % 500) / 100.f);

        scene.addEntity({(posX + 4.f) * sinf(M_PI / 1000.f * c), 0.f, -40 + (posZ + 4.f )*  cosf(M_PI / 1000.f * c)}, {0.f, 0.f, 0.f}, {0.1f, 0.1f, 0.1f}, E_primitive3D::CUBE);
    }


	scene.addLigth({0.f, 0.f, -20.f}, 0.4f, 1.f, 0.8f);
}

void initSceneDemoAlpha (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, true);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

	scene.addEntity({0.f, 0.f, -10.f}, {M_PI, 0.f, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //White cube
	int idC2 = scene.addEntity({2.f, 1.f, -8.f}, {M_PI, 0.f, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //Green cube
	int idC3 = scene.addEntity({1.f,-1.f, -6.f}, {M_PI, 0.f, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //Red cube
	int idC4 = scene.addEntity({1.5f, 0.f, -4.f}, {M_PI, 0.f, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //Blue cube

    int idC5 = scene.addEntity({8.f, 0.f, -6.f}, {M_PI, M_PI_4, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //Red cube
	int idC6 = scene.addEntity({7.f, 0.f, -6.f}, {M_PI, -M_PI_4, 0.f}, {3.f, 3.f, 0.2f}, E_primitive3D::CUBE);  //Green cube

	int idS1 = scene.addEntity({-4.f, 0.f, -6.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);  //Red cube
	int idS2 = scene.addEntity({-3.f, 0.f, -6.f}, {0.f, 0.f, 0.f}, {0.7f, 0.7f, 0.7f}, E_primitive3D::SPHERE);  //Blue cube

    auto itMatGlassR = Material::addMaterial("media/material/glassRed.mtl");
    auto itMatGlassG = Material::addMaterial("media/material/glassGreen.mtl");
    auto itMatGlassB = Material::addMaterial("media/material/glassBlue.mtl");


    scene.getEntity(idC2).setMaterial(itMatGlassG->second.get());
    scene.getEntity(idC3).setMaterial(itMatGlassR->second.get());
    scene.getEntity(idC4).setMaterial(itMatGlassB->second.get());

    scene.getEntity(idC5).setMaterial(itMatGlassR->second.get());
    scene.getEntity(idC6).setMaterial(itMatGlassG->second.get());

    scene.getEntity(idS1).setMaterial(itMatGlassR->second.get());
    scene.getEntity(idS2).setMaterial(itMatGlassB->second.get());

    scene.addLigth({0.f, 0.f, 0.f}, 1.f, 0.f, 0.f);
}

void initSceneDemoAA (Scene& scene, Window& win)
{
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_EDGE, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_MULTI_COLOR, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_DEPTH_BUFFER, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_NORMAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_SHAPE_FILL, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_DRAW_REFERENTIAL, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_BACK_FACE_CULLING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_CLIPPING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_LETTERBOX_CLIPPING, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ANTI_ALIASING, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_PHONG_LIGHT_ALGORYTHME, false);
    Rasterizer::setSetting(E_rasterizerSetting::R_USE_BLINN_PHONG_LIGHT_ALGORYTHME, true);
    Rasterizer::setSetting(E_rasterizerSetting::R_ENABLE_ALPHA_BLENDING, false);

    Rasterizer::loadPerspectiveMatrix(150, win.width() / (float)win.heigth(), 0.01, 100);

	scene.addEntity({-5.f, -5.f, -50.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::TRIANGLE);  //triangle
	int idCrate = scene.addEntity({-5.f, 5.f, -50.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::CUBE);  //White cube
	int idSphere = scene.addEntity({5.f, 5.f, -50.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, E_primitive3D::SPHERE);  //White cube
	scene.addEntity({5.f, -5.f, -50.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "./media/obj/teapot.obj");         //teapot3

    auto itMatPorc = Material::addMaterial("media/material/porcelaine.mtl");
    auto itMatCrate = Material::addMaterial("media/material/crate.mtl");

    scene.getEntity(idCrate).setMaterial(itMatCrate->second.get());
    scene.getEntity(idSphere).setMaterial(itMatPorc->second.get());

    scene.addLigth({0.f, 0.f, 0.f}, 1.f, 0.f, 0.f);


}

void runDemoFree (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time)
{
    int light       = 1;
/*	int teaPot      = 1;
	int teaPot2     = 2;
	int teaPot3     = 3;
	int character   = 4;*/

    static float rot = 0.f;

    rot += 1.5f * time.dtf_;

    scene.getEntity(light).getTransform().setOrigin({5.f * cos(rot), 0.f, -30.f + 5.f * sin(rot)});
    scene.getLight(light).setPosition({5.f * cos(rot), 0.f, -30.f + 5.f * sin(rot)});
}

void runDemoColor (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{
    int triangle        = 1;
    static float rot    = 0.f;

    rot += .5f * time.dtf_;
    scene.getEntity(triangle).getTransform().setOrientation({rot, rot, rot});

}

void runDemoZBuffer (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time)
{
    int sphere2         = 3;
    static float rot    = 0.f;

    rot += .5f * time.dtf_;
    scene.getEntity(sphere2).getTransform().setOrigin({0.5f + 2 * cos(rot), 0.f, -5 + 2 * sin(rot)});
}

void runDemoLight (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{
    int light       = 1;
/*	int teaPot      = 1;
	int teaPot2     = 2;
	int teaPot3     = 3;
	int character   = 4;*/

    static float rot = 0.f;
    static float rotY = 0.f;

    rot += 1.f * time.dtf_;
    rotY += 6.f * time.dtf_;

    scene.getEntity(light).getTransform().setOrigin({10.f * cos(rot), 3 * sin(rotY), -30.f + 10.f * sin(rot)});
    scene.getLight(light).setPosition({10.f * cos(rot), 3 * sin(rotY), -30.f + 10.f * sin(rot)});
}

void runDemoProjection (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{

}

void runDemoTexturing (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{
    int sun      = 1;
	int earth    = 2;
	int moon     = 3;

    static float rotEarthArroundSun = M_PI_2;
    static float rotEarth = 0.f;
    static float rotMoonArroundEarth = 0.f;
    static float rotSun = 0.f;
    static float rotAsteroide = 0.f;

    rotEarthArroundSun  += 0.1f * time.dtf_;
    rotEarth            += 0.5f * time.dtf_;
    rotMoonArroundEarth += 0.9f * time.dtf_;
    rotSun              += 0.1f * time.dtf_;
    rotAsteroide        += 0.1f * time.dtf_;

    scene.getEntity(sun).getTransform().setOrientation({rotSun, rotSun, rotSun});

    scene.getEntity(earth).getTransform().setOrigin({25.f * cos(rotEarth), 0.f, -40.f + 25.f * sin(rotEarth)});
    scene.getEntity(earth).getTransform().setOrientation({(float)(M_PI_2 + M_PI + M_PI_4), 0.f, (float)(M_PI_4) + rotEarth});

    scene.getEntity(moon).getTransform().setOrigin({4.f * cosf(rotMoonArroundEarth) + 25.f * cosf(rotEarth), 1.f * cosf(rotMoonArroundEarth), 4.f * sinf(rotMoonArroundEarth) + -40.f + 25.f * sinf(rotEarth)});

    for (int c = 0; c < 2000; c++)
    {
       scene.getEntity(4 + c).getTransform().setOrientation({rotAsteroide, 0.f, rotAsteroide});
    }
}

void runDemoAlpha (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{}

void runDemoAA (Scene& scene, Window& win,	Renderer& ren, Input& input, TimeManager& time)
{
    int idTriangle  =  1;
	int idCrate     =  2;
	int idSphere    =  3;
	int idTeapot    =  3;

    static float rotT = 0.f;
    static float rotC = 0.f;
    static float rotS = 0.f;
    static float rotTP = 0.f;

    rotT  += 0.5f * time.dtf_;
    rotC  += 0.5f * time.dtf_;
    rotS  += 0.5f * time.dtf_;
    rotTP += 0.5f * time.dtf_;

    scene.getEntity(idTriangle).getTransform().setOrientation({rotT, 0.f, rotT});
    scene.getEntity(idCrate).getTransform().setOrientation({rotC, 0.f, rotC});
    scene.getEntity(idSphere).getTransform().setOrientation({rotS, 0.f, rotS});
    scene.getEntity(idTeapot).getTransform().setOrientation({rotTP, rotTP, 0.f});
}