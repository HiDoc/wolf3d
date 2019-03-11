/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:22:32 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 15:42:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static SDL_Color	inttorgb(Uint32 color)
{
	SDL_Color	rgb;

	rgb.r = (color >> 24) / 255;
	rgb.g = (color >> 16) / 255;
	rgb.b = (color >> 8) / 255;
	rgb.a = color / 255;
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

Uint32			mix_colors(Uint32 cr1, Uint32 cr2, int *mix)
{
	SDL_Color	c[2];
	SDL_Color	color;

	if (cr1 == cr2)
		return (cr1);
	c[0] = inttorgb(cr1);
	c[1] = inttorgb(cr2);
	color.a = 1 - (1 - c[1].a) * (1 - c[0].a);
	color.r = c[1].r * c[1].a / color.a + c[0].r * c[0].a * (1 - c[1].a) / color.a;
	color.g = c[1].g * c[1].a / color.a + c[0].g * c[0].a * (1 - c[1].a) / color.a;
	color.b = c[1].b * c[1].a / color.a + c[0].b * c[0].a * (1 - c[1].a) / color.a;
	// color.r = blend_color(c[0].r, c[1].r, p);
	// color.g = blend_color(c[0].g, c[1].g, p);
	// color.b = blend_color(c[0].b, c[1].b, p);
	// color.a = blend_alpha(c[0].a, c[1].a, p);
	color.a *= 255;
	color.r *= 255;
	color.g *= 255;
	color.b *= 255;
	*mix = 0;
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}
// r.A = 1 - (1 - fg.A) * (1 - bg.A); // 0.75
// r.R = fg.R * fg.A / r.A + bg.R * bg.A * (1 - fg.A) / r.A; // 0.67
// r.G = fg.G * fg.A / r.A + bg.G * bg.A * (1 - fg.A) / r.A; // 0.33
// r.B = fg.B * fg.A / r.A + bg.B * bg.A * (1 - fg.A) / r.A; // 0.00