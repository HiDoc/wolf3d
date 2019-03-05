#include "doom.h"

void	draw_img(t_env *env, t_edge edge, SDL_Surface *img)
{
	int		i;
	int		j;
	int		x;
	int		y;

	SDL_LockSurface(env->engine.surface);
	x = 0;
	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		y = 0;
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

SDL_Surface		*surface_fr_rgb(char *path)
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
	SDL_Surface	*tmp;
	Uint32		*pixls[2];

	path = ft_strjoin("./rsrc/img/weapons/", filename);
	path = ft_strljoin(path, (char *)png);
	new = surface_fr_rgb(path);
	free(path);
	path = NULL;
	if (new->w > W || new->h > H )
	{
		tmp = SDL_CreateRGBSurface(0, W, H , 32, 
		0xff000000, 0xff0000, 0xff00, 0xff);
		pixls[0] = tmp->pixels;
		pixls[1] = new->pixels;
		scale_img(pixls[0], pixls[1], (SDL_Rect){W, H, 0, 0}, new);
		free(new);
		new = tmp;
		pixls[0] = NULL;
		pixls[1] = NULL;
	}
	return (new);
}
