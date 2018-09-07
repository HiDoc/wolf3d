/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/07 15:28:47 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_ray	*ray_init(t_env *env, t_ray *ray, int x)
{
	ray->wdist = -1;
	ray->sidew = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
	ray->map.x = (int)env->pos.x;
	ray->map.y = (int)env->pos.y;
	ray->raydir.x = env->dir.x + env->plane.x * env->cam;
	ray->raydir.y = env->dir.y + env->plane.y * env->cam;
	ray->delta.x = sqrt(1 + (ray->raydir.y * ray->raydir.y) /
			(ray->raydir.x * ray->raydir.x));
	ray->delta.y = sqrt(1 + (ray->raydir.x * ray->raydir.x) /
			(ray->raydir.y * ray->raydir.y));

	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (env->pos.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (ray->map.x + 1.0 - env->pos.x) * ray->delta.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (env->pos.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (ray->map.y + 1.0 - env->pos.y) * ray->delta.y;
	}

	int i;

	while ((i = env->w_map[(int)ray->map.x][(int)ray->map.y]) == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->sidew = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->sidew = 1;
		}
	}
	ray->text = env->walls[env->w_map[(int)ray->map.x][(int)ray->map.y]];
	(ray->sidew == 0) ? ray->wdist = (ray->map.x - env->pos.x
			+ (1 - ray->step.x) / 2) / ray->raydir.x : 0;
	(ray->sidew != 0) ? ray->wdist = (ray->map.y - env->pos.y
			+ (1 - ray->step.y) / 2) / ray->raydir.y : 0;

	ray->lineh = (int)(HEIGHT / ray->wdist);
	ray->sdraw = (-ray->lineh / 2 + HEIGHT / 2) + env->is_updn;
	ray->sdraw < 0 ? ray->sdraw = 0 : 0;
	ray->edraw = (ray->lineh / 2 + HEIGHT / 2) + env->is_updn;
	ray->edraw >= HEIGHT ? ray->edraw = HEIGHT - 1 : 0;
	if (ray->sidew == 0)
		ray->wall.x = env->pos.y + ray->wdist * ray->raydir.y;
	else
		ray->wall.x = env->pos.x + ray->wdist * ray->raydir.x;
	ray->wall.x -= floor((ray->wall.x));
	return (ray);
}
