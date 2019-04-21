/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hud_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:21:37 by abaille           #+#    #+#             */
/*   Updated: 2019/04/21 15:03:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	 set_surface_alpha(SDL_Surface *surface, Uint8 alpha, t_rgba *c)
{
    SDL_PixelFormat	*fmt;
	int				x;
	int				y;
	Uint32			*p;
	unsigned		bpp;

	fmt = surface->format;
	bpp = fmt->BytesPerPixel;
	y = 0;
	while (y < surface->h)
	{
		x = 0;
		while (x < surface->w)
		{
			p = (Uint32 *)((Uint8 *)surface->pixels
				+ y * surface->pitch
				+ x * bpp);
			SDL_GetRGBA( *p, fmt, &c->r, &c->g, &c->b, &c->a );
			*p = SDL_MapRGBA( fmt, c->r, c->g, c->b, (float)(alpha / 255.0f) * c->a );
			x++;
		}
		y++;
	}
	return (1);
}
