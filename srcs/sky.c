/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 11:05:42 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/19 13:35:12 by fmadura          ###   ########.fr       */
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

static int		line_ceil(t_env *env, t_line *line, int y)
{
	t_point		fwall;
	t_point		csky;
	t_point		tsky;
	double		weight;

	get_fwall(line, &fwall);
	if (line->edraw < 0)
		line->edraw = HEIGHT; 
	weight = (HEIGHT / (2.0 * y - HEIGHT)) / line->wdist;
	csky.x = weight * fwall.x + (1.0 - weight) * env->pos.x;
	csky.y = weight * fwall.y + (1.0 - weight) * env->pos.y;
	tsky.x = (int)(csky.x * 64.0) % 64;
	tsky.y = (int)(csky.y * 64.0) % 64;
	return (tsky.y * 64.0 + tsky.x);
}

int				line_sky(t_env *env, t_line *line, int x, int y)
{
	(void)x;
	return (line_ceil(env, line, y));
}
