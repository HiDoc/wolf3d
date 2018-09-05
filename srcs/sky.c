/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 17:41:42 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/05 13:00:24 by fmadura          ###   ########.fr       */
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
	tsky.x = (int)(csky.x * 800.0) % 800;
	tsky.y = (int)(csky.y * 600.0) % 600;
	return (tsky.y * 800.0 + tsky.x);
}

int				line_sky(t_env *env, t_line *line, int x, int y)
{
	(void)line_ceil;
	(void)line;
	(void)env;
	int pos;
	double dpos;

	dpos = env->pang * 800.0 / 360.0;
	if (dpos + x > 800)
	{
		x = -x;
	}
	pos = (y * WIDTH + x);
	return (pos);
}
