#include "doom.h"

void	put_img(t_env *env, SDL_Surface *img, int x, int y)
{
	SDL_Rect	rect;

	rect.w = 128;
	rect.h = 128;
	rect.x = x;
	rect.y = y;
	if (img)
		SDL_BlitSurface(img, NULL, env->sdl.surface, &rect);
}

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

SDL_Surface		*img_wpn(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/weapons/", filename);
	path = ft_strljoin(path, (char *)png);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}
