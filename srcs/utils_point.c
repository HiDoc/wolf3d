/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 14:06:52 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/02 15:47:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_point	*point_cpy(t_point *a, t_point *b)
{
	a->x = (int)b->x;
	a->y = (int)b->y;
	return (a);
}

t_point	*point_delta(t_point *pdelta, t_point *raydir)
{
	pdelta->x = delta(raydir->x, raydir->y);
	pdelta->y = delta(raydir->y, raydir->x);
	return (pdelta);
}

t_point	*point_ray(t_point *ray, t_point *dir, t_point *plane, double cam)
{
	ray->x = dir->x + plane->x * cam;
	ray->y = dir->y + plane->y * cam;
	return (ray);
}
