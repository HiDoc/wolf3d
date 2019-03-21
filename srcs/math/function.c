/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:29:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/21 19:19:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Rotation surface, relatif a env->engine.player.angle
*/
// fonction a proteger
SDL_Surface		*rotate_surface(SDL_Surface *surface, t_env *env)
{
	SDL_Surface		*dest;
	int		y;
	int		x;
	int		xdst;
	int		ydst;

	y = 0;
	if (!(dest = ui_make_surface(MINIMAP_SIZE + 1, MINIMAP_SIZE + 1)))
	{
		printf("Doom_nukem: minimap: %s\n", SDL_GetError());
		exit(EXIT_FAILURE); // retourner erreur
	}
	while (y < surface->h)
	{
		x = 0;
		while (x < surface->w)
		{
			xdst = x * env->engine.player.anglesin - y
				* env->engine.player.anglecos + MINIMAP_SIZE / 2;
			ydst = x * env->engine.player.anglecos + y
				* env->engine.player.anglesin + MINIMAP_SIZE / 2;
			if (xdst > 0 && xdst < MINIMAP_SIZE + 1
			&& ydst > 0 && ydst < MINIMAP_SIZE + 1)
				setpixel(dest, xdst, ydst, getpixel(surface, x, y));
			x++;
		}
		y++;
	}
	SDL_FreeSurface(surface);
	return (dest);
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
