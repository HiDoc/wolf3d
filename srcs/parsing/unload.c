#include "doom.h"

void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window, t_engine *e)
{
	unsigned	a;

	a = 0;
	while (a < e->nsectors)
	{
		free(e->sectors[a].vertex);
		a++;
	}
	a = 0;
	while (a < e->nsectors)
	{
		free(e->sectors[a].neighbors);
		a++;
	}
	free(e->sectors);
	e->sectors = NULL;
	e->nsectors = 0;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	window = NULL;
	renderer = NULL;
}