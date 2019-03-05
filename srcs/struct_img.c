#include "doom.h"

void	draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl)
{
	int		i;
	int		j;
	int		x;
	int		y;

	SDL_LockSurface(env->engine.surface);
	x = pxl.x;
	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		y = pxl.y;
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			getpixel(img, x, y) & 0xFF000000
			? setpixel(env->engine.surface, i, j, getpixel(img, x, y))
			: 0;
			j++;
			y++;
		}
		x++;
		i++;
	}
	SDL_UnlockSurface(env->engine.surface);
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
