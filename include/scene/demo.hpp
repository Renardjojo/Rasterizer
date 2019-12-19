//Project : rasterizer
//Editing by Six Jonathan
//Date : 16/12/2019 - 11 h 14

#ifndef _DEMO_H
#define _DEMO_H

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

typedef enum E_DemoFlag
{
	//camera is integrat int each version
	V0_FREE 						= 0,
	V1_COLOR						= 1,
	V2_ZBUFFER						= 2,
	V3_4_LIGTH						= 3,
	V5_PROJECTION					= 4,
	V6_TEXTURE						= 5,
	V8_ALPHA_BACKFACE_CULLING		= 6,
	V9_AA							= 7

} DemoFlag;

void runDemo ();

void initSceneDemoFree      (Scene& scene, Window& win);
void initSceneDemoColor     (Scene& scene, Window& win);
void initSceneDemoZBuffer   (Scene& scene, Window& win);
void initSceneDemoLight (Scene& scene, Window& win);
void initSceneDemoProjection (Scene& scene, Window& win);
void initSceneDemoTexturing (Scene& scene, Window& win);
void initSceneDemoAlpha (Scene& scene, Window& win);
void initSceneDemoAA (Scene& scene, Window& win);

void runDemoFree        (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoColor       (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoZBuffer     (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoLight       (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoProjection  (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoTexturing   (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoAlpha       (Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);
void runDemoAA      	(Scene& scene, Window& win, Renderer& ren, Input& input, TimeManager& time);


#endif // _DEMO_H