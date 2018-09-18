/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:38:35 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/18 18:04:22 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		surface_set_pixel(SDL_Surface *s, SDL_Color c, size_t x, size_t y)
{
	Uint32	*pixels;
	Uint32	color;

	SDL_LockSurface(s);
	pixels = s->pixels;
	color = SDL_MapRGBA(s->format, c.r, c.g, c.b, c.a);
	pixels[y * s->w + x] = color;
	SDL_UnlockSurface(s);
}

SDL_Surface	*surface_new(Uint32 *pixels, int width, int height)
{
	SDL_Surface	*new;

	new = SDL_CreateRGBSurfaceFrom(
			(void *)pixels,
			width,
			height,
			32,
			4 * width,
			0x00FF0000,
			0x0000FF00,
			0x000000FF,
			0xFF000000);

	return (new);
}
