/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:00:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/26 16:48:04 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	obj_iter(t_env *env, t_iline *iter,
Uint32 (*f)(t_env*, t_line*, int), int (*fog)(t_env *, t_line *, Uint32, int))
{
	int			x;
	int			y;
	int			prop;
	SDL_Surface	*sprite;

	x = iter->line.objs->map.x;
	y = iter->line.objs->map.y;
	if (env->w_map[x][y] == 0x60)
	{
		sprite = env->enemies[0].sprite;
		prop = iter->delim - iter->y;
		while (iter->y < iter->delim && iter->y < HEIGHT)
		{
			iter->color = getpixel(sprite, ((prop - (iter->delim - iter->y))
			* sprite->h / prop) % sprite->w, (int)(iter->line.objs->wall.x
			* sprite->w) % sprite->h);
			if (iter->color & 0xff000000)
				setpixel(env->sdl.surface, iter->x, iter->y, iter->color);
			++(iter->y);
		}
	}
	else
	{
		while (iter->y < iter->delim && iter->y < HEIGHT)
		{
			iter->color = f(env, iter->line.objs, iter->y - env->player.actions.is_up_down);
			setpixel(env->sdl.surface, iter->x, iter->y,
			fog(env, iter->line.objs, iter->color, iter->y));
			++(iter->y);
		}
	}
}

static void	line_iter(t_env *env, t_iline *iter,
Uint32 (*f)(t_env*, t_line*, int), int (*fog)(t_env *, t_line *, Uint32, int))
{
	if (iter->delim < 0)
		return;
	while (iter->y < iter->delim && iter->y < HEIGHT)
	{	
		iter->color = 
		f(
			env, 
			&iter->line,
			iter->y - env->player.actions.is_up_down - (int)(env->jumpmod / (iter->line.wdist / 4))
		);
		setpixel(
			env->sdl.surface,
			iter->x,
			iter->y, //+ (int)(env->jumpmod / (iter->line.wdist / 4)),
			fog(env, &iter->line, iter->color, iter->y)
		);
		++(iter->y);
	}
}

static inline void	put_objs(t_env *env, t_iline *iter)
{
	if (iter->line.nb_objs > 0)
	{
		iter->y = iter->line.objs->start_draw;
		iter->delim = iter->line.objs->end_draw;
		obj_iter(env, iter, &line_tron_objs, &wall_fog);
	}
}

int					tron(t_env *env, int col)
{
	t_iline	*iter;
	t_line	objs;
	int		x;

	x = col - 1;
	while (x < WIDTH)
	{
		iter = &env->rays[x];
		iter->line.objs = &objs;
		iter->x = x;
		iter->y = 0;
		line_init(env, &iter->line, env->w_map, iter->x);
		iter->delim = iter->line.start_draw - (iter->line.end_draw - iter->line.start_draw)
		+ (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_tron_floor, &sky_fog);
		iter->delim = iter->line.start_draw + (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_tron_wall, &wall_fog);
		iter->delim = iter->line.end_draw + (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_tron_wall, &wall_fog);
		iter->delim = HEIGHT;
		line_iter(env, iter, &line_tron_ceil, &floor_fog);
		put_objs(env, iter);
		x += 8;
	}
	return (0);
}

int					wolf(t_env *env, int col)
{
	t_iline	*iter;
	t_line	objs;
	int		x;

	x = col - 1;
	while (x < WIDTH)
	{
		iter = &env->rays[x];
		iter->line.objs = &objs;
		iter->x = x;
		iter->y = 0;
		line_init(env, &iter->line, env->w_map, iter->x);
		iter->delim = iter->line.start_draw
		- (iter->line.end_draw - iter->line.start_draw)
		+ (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_sky, &sky_fog);
		iter->delim = iter->line.start_draw
		+ (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_wall, &wall_fog);
		iter->delim = iter->line.end_draw
		+ (int)(env->jumpmod / (iter->line.wdist / 4));
		line_iter(env, iter, &line_wall, &wall_fog);
		iter->delim = HEIGHT;
		line_iter(env, iter, &line_floor, &floor_fog);
		put_objs(env, iter);
		x += 8;
	}
	return (0);
}
