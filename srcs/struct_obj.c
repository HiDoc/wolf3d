/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/20 13:26:53 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*objs_init(t_env *env, t_line *line, int x)
{
	line->floor = env->floor;
	line->sky = env->sky;
	line->wdist = -1;
	line->sidew = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
	line->map.x = (int)env->pos.x;
	line->map.y = (int)env->pos.y;
	line->raydir.x = env->dir.x + env->plane.x * env->cam;
	line->raydir.y = env->dir.y + env->plane.y * env->cam;
	line->delta.x = sqrt(1 + (line->raydir.y * line->raydir.y) /
			(line->raydir.x * line->raydir.x));
	line->delta.y = sqrt(1 + (line->raydir.x * line->raydir.x) /
			(line->raydir.y * line->raydir.y));
	return (objs_step(env, line));
}

t_line	*objs_step(t_env *env, t_line *line)
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
	return (objs_dda(env, line));
}

t_line	*objs_dda(t_env *env, t_line *line)
{
	int i;

	while ((i = env->o_map[(int)line->map.x][(int)line->map.y]) == 0)
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
	line->text = env->enemy;
	(line->sidew == 0) ? line->wdist = (line->map.x - env->pos.x
			+ (1 - line->step.x) / 2) / line->raydir.x : 0;
	(line->sidew != 0) ? line->wdist = (line->map.y - env->pos.y
			+ (1 - line->step.y) / 2) / line->raydir.y : 0;
	return (i == 2 ? objs_max(env, line) : NULL);
}

t_line	*objs_max(t_env *env, t_line *line)
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