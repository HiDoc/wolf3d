/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:16:17 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 15:23:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		color_modify(Uint8 *component, double delta, int arg)
{
    if (*component > 0)
        *component = (*component * (1 - delta) + ((0x0 >> arg) * delta));
}

static int  calc_color(Uint32 c, double delta)
{
    SDL_Color color;

    delta > 0.9 ? delta = 0.9 : 0;
    delta /= 1.50;
    c |= 0xFF000000;
	color.a = c >> 24;
	color.b = c >> 16;
	color.g = c >> 8;
	color.r = c;
    color_modify(&color.a, delta, 24);
    color_modify(&color.b, delta, 16);
    color_modify(&color.g, delta, 8);
    color_modify(&color.r, delta, 0);
	return ((color.a << 24) + (color.b << 16) + (color.g << 8) + (color.r));
}

int			wall_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)y;
    (void)env;
	delta = 15 / (100 / line->wdist);
    return (calc_color(c, delta));
}

int			sky_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)env;
    delta = (double)y / (double)line->start_draw * 1.2;
    return (calc_color(c, delta));
}

int			floor_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)env;
    delta = (HEIGHT - (double)y) / (HEIGHT - line->end_draw);
    return (calc_color(c, delta));
}
