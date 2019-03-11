/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:22:32 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 12:51:57 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static SDL_Color	inttorgb(Uint32 color)
{
	SDL_Color	rgb;

	rgb.r = color >> 24;
	rgb.g = color >> 16;
	rgb.b = color >> 8;
	rgb.a = color;
	return (rgb);
}

int			blend_alpha(int c1a, int c2a, float p)
{
	return ((1 - p) * c1a + p * c2a);
}

int			blend_color(int c1, int c2, float p)
{
	return (sqrt((1 - p) * (c1 * c1) + p * (c2 * c2)));
}

Uint32			mix_colors(Uint32 cr1, Uint32 cr2, float p, int *mix)
{
	SDL_Color	c[2];
	SDL_Color	color;

	if (*mix)
	{	if (cr1 == cr2)
			return (cr1);
		c[0] = inttorgb(cr1);
		c[1] = inttorgb(cr2);
		color.r = blend_color(c[0].r, c[1].r, p);
		color.g = blend_color(c[0].g, c[1].g, p);
		color.b = blend_color(c[0].b, c[1].b, p);
		color.a = blend_alpha(c[0].a, c[1].a, p);
		*mix = 0;
		return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
	}
	return (0);
}
