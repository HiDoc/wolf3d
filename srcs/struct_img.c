#include "doom.h"


SDL_Surface		*create_surf(char *path)
{
	SDL_Surface	*new;

	new = IMG_Load(path);
	if (!new)
	{
		printf("Error : %s\n", SDL_GetError());
		return (NULL);
	}
	return (new);
}