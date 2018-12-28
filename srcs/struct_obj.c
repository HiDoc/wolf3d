/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/04 12:41:36 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*obj_init(t_env *env, t_line *previous)
{
	t_line	*line;

	line = previous->objs;
	line->wdist = -1;
	line->sidew = -1;
	line->wdist = ldist(env, previous, previous->sidew == 0 ? 'x' : 'y');
	line->lineh = (int)(HEIGHT / line->wdist);
	line->start_draw = (-line->lineh / 2 + HEIGHT / env->hratio) + env->is_updn;
	line->start_draw < 0 ? line->start_draw = 0 : 0;
	line->end_draw = (line->lineh / 2.0 + (double)HEIGHT / env->hratio) + env->is_updn;
	line->end_draw >= HEIGHT ? line->end_draw = HEIGHT - 1 : 0;
	line->map.x = previous->map.x;
	line->map.y = previous->map.y;
	if (line->sidew == 0)
		line->wall.x = env->pos.y + line->wdist * previous->raydir.y;
	else
		line->wall.x = env->pos.x + line->wdist * previous->raydir.x;
	line->wall.x -= floor((line->wall.x));
	return (line);
}