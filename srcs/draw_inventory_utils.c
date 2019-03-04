#include "doom.h"

void	surface_drawrect(SDL_Surface *surface, t_edge edge, Uint32 color)
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

void	surface_draw_img(SDL_Surface *surface, t_edge edge, SDL_Surface *img)
{
	int		i;
	int		j;
	int		x;
	int		y;

	SDL_LockSurface(surface);
	x = 0;
	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		y = 0;
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			getpixel(img, x, y) & 0xFF000000
			? setpixel(surface, i, j, getpixel(img, x, y))
			: setpixel(surface, i, j, 0x88888888);
			j++;
			y++;
		}
		x++;
		i++;
	}
	SDL_UnlockSurface(surface);
}

int		scale_img(Uint32 *dest, Uint32 *src, SDL_Rect rect, SDL_Surface *img)
{
	int		x;
	int		y;
	t_vtx	scale;
	Uint32	p;

	scale.x = (float)img->w / (float)(rect.w - rect.w / 8);
	scale.y = (float)img->h / (float)(rect.h - rect.h / 8);
	x = 0;
	while (x < rect.w - rect.w / 8)
	{
		y = 0;
		while (y < rect.h - rect.h / 8)
		{
			p = src[img->w * (int)(y * scale.y) + (int)(x * scale.x)];
			p = ((p & 0xFF) << 24)
			+ (((p & 0xFF00) >> 8) << 16)
			+ (((p & 0xFF0000) >> 16) << 8)
			+ (((p & 0xFF000000) >> 24));
			dest[rect.w * (y + rect.h / 12) + (x + rect.w / 12)] = p;
			y++;
		}
		x++;
	}
	return (0);
}
