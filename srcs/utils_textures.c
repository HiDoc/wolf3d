/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/04 16:50:12 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_point	*get_fwall(t_line *line, t_point *fwall)
{
	if (line->sidew == 0 && line->raydir.x > 0)
	{
		fwall->x = line->map.x;
		fwall->y = line->map.y + line->wall.x;
	}
	else if (line->sidew == 0 && line->raydir.x < 0)
	{
		fwall->x = line->map.x + 1.0;
		fwall->y = line->map.y + line->wall.x;
	}
	else if (line->sidew == 1 && line->raydir.y > 0)
	{
		fwall->x = line->map.x + line->wall.x;
		fwall->y = line->map.y;
	}
	else
	{
		fwall->x = line->map.x + line->wall.x;
		fwall->y = line->map.y + 1.0;
	}
	return (fwall);
}

Uint32			line_floor(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = line->floor->w;
	h = line->floor->h;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (env->hratio * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x + (1.0 - weight) * env->pos.x) * w);
	h = (int)((weight * fwall.y + (1.0 - weight) * env->pos.y) * h);
	return (getpixel(line->floor, w % line->floor->w, h % line->floor->h));
}

Uint32			line_sky(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = line->floor->w * 2;
	h = line->floor->h * 2;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (2.0 * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x - (1.0 / 3.0 + weight) * env->pos.x) * w);
	h = (int)((weight * fwall.y - (1.0 / 3.0 + weight) * env->pos.y) * h);
	w = w % line->floor->w;
	h = h % line->floor->h;
	return (getpixel(line->floor, w % line->floor->w, h % line->floor->h));
}

Uint32			infinite_sky(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	t_point	cfloor;
	t_point	tfloor;
	double	weight;

	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (env->hratio * y - HEIGHT)) / line->wdist;
	cfloor.x = weight * fwall.x - weight * env->pos.x;
	cfloor.y = weight * fwall.y - weight * env->pos.y;
	tfloor.x = (int)(cfloor.x * 64) % 64;
	tfloor.y = (int)((HEIGHT - cfloor.y) * 64) % 64;
	return (getpixel(line->floor, tfloor.x, tfloor.y));
}

Uint32			line_wall(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	x = (int)(line->wall.x * line->text->w);
	x = line->text->w - x - 1;
	delta = y * line->text->h * 4 - HEIGHT * line->text->h * 2
		+ line->lineh * line->text->h * 2;
	yy = ((delta * 64.0) / (line->lineh)) / 256;
	return (getpixel(line->text, x, yy));
}
