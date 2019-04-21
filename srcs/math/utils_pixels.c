/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:52:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/21 15:56:15 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = pixel;
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	int				bpp;
	Uint8			*p;
	Uint32			ret;

	x = ft_abs(--x);
	y = ft_abs(--y);
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	ret = *(Uint32 *)p;
	return (ret);
}
