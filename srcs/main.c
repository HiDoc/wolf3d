#include "doom.h"

int		main()
{
	t_env			env;

	env.sdl.window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	env.sdl.renderer = SDL_CreateRenderer(env.sdl.window, -1, 0);
	env.sdl.texture = NULL;
	env.engine.nsectors = 0;
	env.engine.sectors = NULL;
	env.sdl.surface = SDL_CreateRGBSurface(0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env.engine.surface = env.sdl.surface;
	LoadData(&env.engine);
	verify_map(&env.engine);
	sdl_loop(&env);
	UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
	SDL_Quit();
	return 0;
}
