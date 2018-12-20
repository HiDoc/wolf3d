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

int					wolf(t_env *env, int col)
{
	t_iline	iter;

	iter.x = col - 1;
	while (iter.x < WIDTH)
	{
		iter.y = 0;
		line_init(env, &iter.line, iter.x);
		iter.delim = iter.line.sdraw - (iter.line.edraw - iter.line.sdraw);
		line_iter(env, &iter, &line_tron_floor, &sky_fog);
		iter.delim = iter.line.sdraw;
		line_iter(env, &iter, &line_tron_wall, &wall_fog);
		iter.delim = iter.line.edraw;
		line_iter(env, &iter, &line_tron_wall, &wall_fog);
		iter.delim = HEIGHT;
		line_iter(env, &iter, &line_tron_floor, &floor_fog);
		iter.x += 8;
	}
	return (0);
}
