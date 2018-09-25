/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 17:41:42 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/24 17:13:59 by fmadura          ###   ########.fr       */
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

int	line_floor(t_env *env, t_line *line, int y)
{
	t_point		fwall;
	t_point		cfloor;
	t_point		tfloor;
	double		weight;

	get_fwall(line, &fwall);
	weight = (HEIGHT / (2.0 * y - HEIGHT)) / line->wdist;
	cfloor.x = weight * fwall.x + (1.0 - weight) * env->pos.x;
	cfloor.y = weight * fwall.y + (1.0 - weight) * env->pos.y;
	tfloor.x = (int)(cfloor.x * 64) % 64;
	tfloor.y = (int)(cfloor.y * 64) % 64;
	return (line->floor->data[(int)(tfloor.y * 64 + tfloor.x)]);
}
