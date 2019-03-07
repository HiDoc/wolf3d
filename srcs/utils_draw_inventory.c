#include "doom.h"

void	draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color)
{
	int		i;
	int		j;

	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			setpixel(surface, i, j, color);
			j++;
		}
		i++;
	}
}

void	put_img_inv(t_env *env, SDL_Surface *img, t_edge bloc, t_edge padding)
{
	SDL_Rect	rect;
	SDL_Surface	*new;
	Uint32		*pixls;

	rect.w = bloc.v2.x - bloc.v1.x;
	rect.h = bloc.v2.y - bloc.v1.y;
	rect.y = padding.v1.x;
	rect.x = padding.v1.y;
	if (img)
	{
		if (rect.w < img->w || rect.h < img->h)
		{
			new = SDL_CreateRGBSurface(0, rect.w, rect.h, 32,
			0xff000000, 0xff0000, 0xff00, 0xff);
			SDL_LockSurface(new);
			pixls = new->pixels;
			scale_img(pixls, rect, img, (t_ixy){padding.v2.x, padding.v2.y});
			SDL_UnlockSurface(new);
			draw_img(env, bloc, new, (t_ixy){0, 0});
			SDL_FreeSurface(new);
			new = NULL;
		}
		else
			draw_img(env, bloc, img, (t_ixy){0, 0});
	}
}