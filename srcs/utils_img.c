#include "doom.h"

int		scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding)
{
	int		x;
	int		y;
	t_vtx	scale;
	Uint32	p;
    Uint32  *src;

    src = img->pixels;
	scale.x = fabs((float)img->w / (float)(rect.w - rect.x));
	scale.y = fabs((float)img->h / (float)(rect.h - rect.y));
	x = 0;
	while (x < rect.w - rect.x)
	{
		y = 0;
		while (y < rect.h - rect.y)
		{
			p = src[img->w * (int)(y * scale.y) + (int)(x * scale.x)];
			dest[rect.w * (y + padding.y) + (x + padding.x)] = p;
			y++;
		}
		x++;
	}
	return (0);
}
