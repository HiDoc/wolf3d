/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:53 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/25 13:41:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_point			*get_fwall(t_line *line, t_point *fwall)
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

Uint32			line_sky_infinite(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	t_point	cfloor;
	t_point	tfloor;
	double	weight;

	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (env->hratio * y - HEIGHT)) / line->wdist;
	cfloor.x = weight * fwall.x - weight * env->player.pos.x;
	cfloor.y = weight * fwall.y - weight * env->player.pos.y;
	tfloor.x = (int)(cfloor.x * 64) % 64;
	tfloor.y = (int)((HEIGHT - cfloor.y) * 64) % 64;
	return (getpixel(line->floor, tfloor.x, tfloor.y));
}

Uint32			line_sky(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = line->sky->w;
	h = line->sky->h;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (2.0 * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x - (1.0 / 3.0 + weight) * env->player.pos.x) * w);
	h = (int)((weight * fwall.y - (1.0 / 3.0 + weight) * env->player.pos.y) * h);
	w = w % line->sky->w;
	h = h % line->sky->h;
	return (getpixel(line->sky, w % 128, h % 128));
}

Uint32			line_floor_under(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = line->floor->w;
	h = line->floor->h;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (env->hratio * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x + (1.0 - weight) * env->player.pos.x) * w);
	h = (int)((weight * fwall.y + (1.0 - weight) * env->player.pos.y) * h);
	if (w % line->floor->w < 20 || h % line->floor->h < 20 )
		return (0xff00ffff);
	else
	{
		if (weight < 0.2)
			return (0xff2010ff);
		else
			return (0xff000000);
	}
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
	w = (int)((weight * fwall.x + (1.0 - weight) * env->player.pos.x) * w);
	h = (int)((weight * fwall.y + (1.0 - weight) * env->player.pos.y) * h);
	return (getpixel(line->floor, w % line->floor->w, h % line->floor->h));
}

Uint32			line_wall_2(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	(void)env;
	x = (int)(line->wall.x * line->text->w);
	x = ft_abs(line->text->w - x - 1);
	delta = line->text->h * (2.0 * y - HEIGHT + line->lineh);
	yy = ft_abs(delta * 0.5 / line->lineh);
	return (getpixel(line->text, (x % line->text->w), (yy % line->text->h)));
}

Uint32			line_wall(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	(void)env;
	x = (int)(line->wall.x * line->text->w);
	x = ft_abs(line->text->w - x - 1);
	delta = line->text->h * (2.0 * y - HEIGHT + line->lineh);
	yy = ft_abs(delta * 0.5 / line->lineh);
	return (getpixel(line->text, (x % line->text->w), (yy % line->text->h)));
}
