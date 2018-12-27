/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:00:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/12/19 19:00:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static inline void	obj_iter(
	t_env *env, t_iline *iter,
	Uint32 (*f)(t_env*, t_line*, int),
	int (*fog)(t_env *, t_line *, Uint32, int))
{
	int		x;
	int		y;
	int		prop;

	x = iter->line.objs->map.x;
	y = iter->line.objs->map.y;
	if (env->w_map[x][y] == 0x60)
	{
		prop = iter->delim - iter->y;
		while (iter->y < iter->delim && iter->y < HEIGHT)
		{
			int new_y = ((prop - (iter->delim - iter->y)) * env->enemies[0].texture->h / prop);
			int new_x = (int)(iter->line.objs->wall.x * env->enemies[0].texture->w);
			iter->color = getpixel(env->enemies[0].texture, 
			new_x % env->enemies[0].texture->w,
			new_y % env->enemies[0].texture->h);
			if (iter->color & 0xff000000)
				setpixel(env->sdl.surface, iter->x, iter->y, iter->color);
			++(iter->y);
		}
	}
	else
	{
		while (iter->y < iter->delim && iter->y < HEIGHT)
		{
			iter->color = f(env, iter->line.objs, iter->y - env->is_updn);
			setpixel(env->sdl.surface, iter->x, iter->y,
			fog(env, iter->line.objs, iter->color, iter->y));
			++(iter->y);

		}
	}
}

static inline void	line_iter(
	t_env *env, t_iline *iter,
	Uint32 (*f)(t_env*, t_line*, int),
	int (*fog)(t_env *, t_line *, Uint32, int))
{
	while (iter->y < iter->delim && iter->y < HEIGHT)
	{
		iter->color = f(env, &iter->line, iter->y - env->is_updn);
		setpixel(env->sdl.surface, iter->x, iter->y,
		fog(env, &iter->line, iter->color, iter->y));
		++(iter->y);
	}
}

int					tron(t_env *env, int col)
{
	t_iline	*iter;
	t_line	objs;

	iter = &env->rays[col - 1];
	iter->x = col - 1;
	iter->line.objs = &objs;
	while (iter->x < WIDTH)
	{
		iter->y = 0;
		line_init(env, &iter->line, env->w_map, iter->x);
		iter->delim = iter->line.start_draw - (iter->line.end_draw - iter->line.start_draw);
		line_iter(env, iter, &line_tron_floor, &sky_fog);
		iter->delim = iter->line.start_draw;
		line_iter(env, iter, &line_tron_wall, &wall_fog);
		iter->delim = iter->line.end_draw;
		line_iter(env, iter, &line_tron_wall, &wall_fog);
		iter->delim = HEIGHT;
		line_iter(env, iter, &line_tron_ceil, &floor_fog);
		if (iter->line.nb_objs > 0)
		{
			iter->y = iter->line.objs->start_draw;
			iter->delim = iter->line.objs->end_draw;
			obj_iter(env, iter, &line_tron_wall, &wall_fog);
		}
		iter->x += 8;
	}
	return (0);
}

int					wolf(t_env *env, int col)
{
	t_iline	iter;

	iter.x = col - 1;
	while (iter.x < WIDTH)
	{
		iter.y = 0;
		line_init(env, &iter.line, env->w_map, iter.x);
		iter.delim = iter.line.start_draw - (iter.line.end_draw - iter.line.start_draw);
		line_iter(env, &iter, &line_sky, &sky_fog);
		iter.delim = iter.line.start_draw;
		line_iter(env, &iter, &line_wall, &wall_fog);
		iter.delim = iter.line.end_draw;
		line_iter(env, &iter, &line_wall, &wall_fog);
		iter.delim = HEIGHT;
		line_iter(env, &iter, &line_floor_under, &floor_fog);
		iter.x += 8;
	}
	return (0);
}
