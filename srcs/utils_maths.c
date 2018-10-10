/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:46:01 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/02 14:06:36 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double		delta(double x, double y)
{
	return (sqrt(1 + (x * x) / (y * y)));
}

double		dist(double map, double pos, double step, double ray)
{
	return ((map - pos + (1 - step) / 2) / ray);
}

double		ldist(t_env *e, t_line *l, char side)
{
	double ret;

	ret = 0;
	if (side == 'x')
		ret = dist(l->map.x, e->pos.x, l->step.x, l->raydir.x);
	else
		ret = dist(l->map.y, e->pos.y, l->step.y, l->raydir.y);
	return (ret);
}

t_point	point_rotate(t_point v, int ang)
{
	float	radian;
	t_point	r;

	radian = ang / 180.0 * 3.141;
	r.x = v.x * cos(radian) - v.y * sin(radian);
	r.y = v.x * sin(radian) + v.y * cos(radian);
	return (r);
}
