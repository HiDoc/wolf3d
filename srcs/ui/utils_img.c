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

int	 SetSurfaceAlpha (SDL_Surface *surface, Uint8 alpha, t_rgba *c)
{
    SDL_PixelFormat	*fmt;
	int				x;
	int				y;
	Uint32			*p;
	unsigned		bpp;

	fmt = surface->format;
	bpp = fmt->BytesPerPixel;
	// Scaling factor to clamp alpha to [0, alpha].
	SDL_LockSurface(surface);
	y = 0;
	while (y < surface->h)
	{
		x = 0;
		while (x < surface->w)
		{
			p = (Uint32 *)(
				(Uint8 *)surface->pixels
				+ y * surface->pitch
				+ x * bpp
				);
			// Get the old pixel components.
			SDL_GetRGBA( *p, fmt, &c->r, &c->g, &c->b, &c->a );
			// Set the pixel with the new alpha.
			*p = SDL_MapRGBA( fmt, c->r, c->g, c->b, (float)(alpha / 255.0f) * c->a );
			x++;
		}
		y++;
	}
	SDL_UnlockSurface(surface);
	return (1);
}