#include "doom.h"

int		scale_img(Uint32 *dest, Uint32 *src, SDL_Rect rect, SDL_Surface *img)
{
	int		x;
	int		y;
	t_vtx	scale;
	Uint32	p;

	scale.x = (float)img->w / (float)(rect.w - rect.x);
	scale.y = (float)img->h / (float)(rect.h - rect.y);
	x = 0;
	while (x < rect.w - rect.x)
	{
		y = 0;
		while (y < rect.h - rect.y)
		{
			p = src[img->w * (int)(y * scale.y) + (int)(x * scale.x)];
			dest[rect.w * (y + rect.h / 12) + (x + rect.w / 12)] = p;
			y++;
		}
		x++;
	}
	return (0);
}
