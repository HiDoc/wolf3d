#include "wolf.h"

int		main()
{
	SDL_Window      *window;
	SDL_Texture     *texture;
	SDL_Renderer    *renderer;
	t_engine		e;

	window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = NULL;
	e.NumSectors = 0;
	e.sectors = NULL;
	e.surface = SDL_CreateRGBSurface(0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	LoadData(&e);
	sdl_loop(texture, renderer, &e);
	UnloadData(texture, renderer, window, &e);
	SDL_Quit();
	return 0;
}
