/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/09 15:19:55 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*line_init(t_env *env, t_line *line, int **map, int x)
{
	line->nb_objs = 0;
	line->floor = env->floor;
	line->sky = env->sky;
	line->wdist = -1;
	line->sidew = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
	point_set(&line->map, (int)env->player.pos.x, (int)env->player.pos.y);
	point_set(&line->raydir, env->player.dir.x + env->player.plane.x * env->cam, env->player.dir.y + env->player.plane.y * env->cam);
	point_set(&line->delta, delta(line->raydir.y, line->raydir.x), delta(line->raydir.x, line->raydir.y));
	return (line_step(env, line, map));
}

t_line	*line_step(t_env *env, t_line *line, int **map)
{
	line->step.x = line->raydir.x < 0 ? -1 : 1;
	line->step.y = line->raydir.y < 0 ? -1 : 1;
	point_diff(&line->side, env->player.pos, line->map);
	(line->raydir.x >= 0) ? line->side.x = 1 - line->side.x : 0;
	(line->raydir.y >= 0) ? line->side.y = 1 - line->side.y : 0;
	line->side.x *= line->delta.x;
	line->side.y *= line->delta.y;
	return (line_dda(env, line, map));
}

t_line	*line_dda(t_env *env, t_line *line, int **map)
{
	while ((map[(int)line->map.x][(int)line->map.y] & 0x10) == 0)
	{
		if ((map[(int)line->map.x][(int)line->map.y] & 0x20) == 0x20
			&& line->nb_objs == 0 && obj_init(env, line) != NULL)
				line->nb_objs++;
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
	line->text = (wall_poster(env, line) == 1) ?
	env->wobj.wposters[env->w_map[(int)line->map.x][(int)line->map.y] >> 12]
	: env->walls[env->w_map[(int)line->map.x][(int)line->map.y] & 0xF];
	env->wobj.is_bullet = (check_impact(line, env) != 0) ? 1 : 0;
	if (env->wobj.is_bullet)
		line->text = env->bul_surf[env->wobj.impact];
	line->wdist = ldist(env, line, line->sidew == 0 ? 'x' : 'y');
	return (line_max(env, line));
}

t_line	*line_max(t_env *env, t_line *line)
{
	line->lineh = (int)(HEIGHT / line->wdist);
	line->start_draw = (-line->lineh / 2 + HEIGHT / env->hratio) + env->player.actions.is_up_down;
	line->start_draw < 0 ? line->start_draw = 0 : 0;
	line->end_draw = (line->lineh / 2.0 + (double)HEIGHT / env->hratio) + env->player.actions.is_up_down;
	line->end_draw >= HEIGHT ? line->end_draw = HEIGHT - 1 : 0;
	if (line->sidew == 0)
		line->wall.x = env->player.pos.y + line->wdist * line->raydir.y;
	else
		line->wall.x = env->player.pos.x + line->wdist * line->raydir.x;
	line->wall.x -= floor((line->wall.x));
	return (line);
}
