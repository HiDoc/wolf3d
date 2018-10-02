/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/02 16:19:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*line_init(t_env *env, t_line *line, int x)
{
	line->floor = env->floor;
	line->sky = env->sky;
	line->wdist = -1;
	line->sidew = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
	line->map = *point_cpy(&line->map, &env->pos);
	point_ray(&line->raydir, &env->dir, &env->plane, env->cam);
	point_delta(&line->delta, &line->raydir);
//	line->map.x = (int)env->pos.x;
//	line->map.y = (int)env->pos.y;
	line->raydir.x = env->dir.x + env->plane.x * env->cam;
	line->raydir.y = env->dir.y + env->plane.y * env->cam;
	line->delta.x = delta(line->raydir.y, line->raydir.x);
	line->delta.y = delta(line->raydir.x, line->raydir.y);
	return (line_step(env, line));
}

t_line	*line_step(t_env *env, t_line *line)
{
	if (line->raydir.x < 0)
	{
		line->step.x = -1;
		line->side.x = (env->pos.x - line->map.x) * line->delta.x;
	}
	else
	{
		line->step.x = 1;
		line->side.x = (line->map.x + 1.0 - env->pos.x) * line->delta.x;
	}
	if (line->raydir.y < 0)
	{
		line->step.y = -1;
		line->side.y = (env->pos.y - line->map.y) * line->delta.y;
	}
	else
	{
		line->step.y = 1;
		line->side.y = (line->map.y + 1.0 - env->pos.y) * line->delta.y;
	}
	return (line_dda(env, line));
}

t_line	*line_dda(t_env *env, t_line *line)
{
	int i;

	while ((i = env->w_map[(int)line->map.x][(int)line->map.y]) == 0)
	{
		if (line->side.x < line->side.y)
		{
			line->side.x += line->delta.x;
			line->map.x += line->step.x;
			line->sidew = 0;
		}
		else
		{
			line->side.y += line->delta.y;
			line->map.y += line->step.y;
			line->sidew = 1;
		}
	}
	if (i == 8)
		line->text = env->portal.outimg;
	else if (i == 9)
		line->text = env->portal.inimg;
	else
		line->text = env->walls[env->w_map[(int)line->map.x][(int)line->map.y]];
	line->wdist = ldist(env, line, line->sidew == 0 ? 'x' : 'y');
	return (line_max(env, line));
}

t_line	*line_max(t_env *env, t_line *line)
{
	line->lineh = (int)(HEIGHT / line->wdist);
	line->sdraw = (-line->lineh / 2 + HEIGHT / 2) + env->is_updn;
	line->sdraw < 0 ? line->sdraw = 0 : 0;
	line->edraw = (line->lineh / 2 + HEIGHT / 2) + env->is_updn;
	line->edraw >= HEIGHT ? line->edraw = HEIGHT - 1 : 0;
	if (line->sidew == 0)
		line->wall.x = env->pos.y + line->wdist * line->raydir.y;
	else
		line->wall.x = env->pos.x + line->wdist * line->raydir.x;
	line->wall.x -= floor((line->wall.x));
	return (line);
}
