/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:29:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 19:56:44 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Rotation surface, relatif a env->engine.player.angle
*/
// fonction a proteger
SDL_Surface		*rotate_surface(SDL_Rect src_rect, SDL_Surface *src,
				SDL_Surface *dst, t_vtx origin, t_env *env)
{
	const t_player	plr = env->engine.player;
	const t_vtx		c = {src_rect.w / 2, src_rect.h / 2};
	t_vtx			dest;
	float			y;
	float			x;
	Uint32			color;
	const float		angle = -plr.angle;

	y = 0;
	while (y < src_rect.h)
	{
		x = 0;
		while (x < src_rect.w)
		{
			dest = (t_vtx){
			c.x + (x - c.x) * sin(angle) - (y - c.y) * cos(angle),
			c.y + (x - c.x) * cos(angle) + (y - c.y) * sin(angle)};
			if ((color = getpixel(src, src_rect.x + dest.x, src_rect.y + dest.y)))
				setpixel(dst, origin.x + x, origin.y + y, color);
			x++;
		}
		y++;
	}
	return (dst);
}

/*
** e.v1 is the start point
** e.v2 is the end point
** c_point is the control point
** time is the parameter, from 0 to 1
*/
t_vtx			bezier_curve(t_edge e, t_vtx c_point, float t)
{
	t_vtx           res;
	const float		l = 1 - t;

	res.x = l * l * e.v1.x + 2 * l * t * c_point.x + t * t * e.v2.x;
	res.y = l * l * e.v1.y + 2 * l * t * c_point.y + t * t * e.v2.y;
	return (res);
}

/*
** Verify if two edge share the same line using affine function
** y = ax + b
*/
int				edge_parallel(t_edge e1, t_edge e2)
{
	const float scale = e1.v2.x - e1.v1.x;
	const float dist = e1.v2.y - e1.v1.y;
	float a;
	float b;

	if (scale == 0)
		return (e2.v2.x - e2.v1.x == 0);
	if (dist == 0)
		return (e2.v2.y - e2.v1.y == 0);
	a = dist / scale;
	b = (cross_product(e1.v2, e1.v1)) / (scale);
	return (e2.v1.y == a * e2.v1.x + b
		&& e2.v2.y == a * e2.v2.x + b);
}
