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
	line->sdraw = (-line->lineh / 2 + HEIGHT / env->hratio) + env->is_updn;
	line->sdraw < 0 ? line->sdraw = 0 : 0;
	line->edraw = (line->lineh / 2.0 + (double)HEIGHT / env->hratio) + env->is_updn;
	line->edraw >= HEIGHT ? line->edraw = HEIGHT - 1 : 0;
	if (line->sidew == 0)
		line->wall.x = env->pos.y + line->wdist * previous->raydir.y;
	else
		line->wall.x = env->pos.x + line->wdist * previous->raydir.x;
	line->wall.x -= floor((line->wall.x));
	return (line);
}