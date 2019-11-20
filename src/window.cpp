#include "window.hpp"

Window::Window (unsigned int width, unsigned int heigth)
{
	// Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("window_initilize : SDL_Init error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

   	win	= SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, heigth, 0);

    if (win == NULL)
    {
        SDL_Log("window_initilize : SDL_CreateWindow error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

Window::~Window ()
{
	SDL_DestroyWindow (win);
}
