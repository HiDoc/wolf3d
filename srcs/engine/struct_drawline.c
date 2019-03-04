/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_drawline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:51:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/04 18:28:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Draw a vertical line on screen
*/
void				vline(t_drawline l, t_env *env)
{
	int		*pixels;
	int		x;
	int		iter;

	x = ((t_transf *)l.container)->x;
	pixels	= (int *)env->engine.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + x] = l.middle;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = l.top;
		iter = l.from + 1;
		int y = 0;
		while (iter < l.to)
		{
			pixels[iter * W + x] = l.middle;
			y++;
			iter++;
		}
		pixels[l.to * W + x] = l.bottom;
	}
}

void				render_cwall(t_drawline l, t_env *env)
{
	t_transf	*ctn;
	int			*pixels;
	SDL_Surface	*sprite;
	int			iter;
	float		height;
	int			x;

	ctn = ((t_transf *)l.container);

	pixels	= (int *)env->engine.surface->pixels;
	sprite = env->world.surfaces.walls[0].sprite;

	height = l.to - l.from;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + ctn->x] = 0xffffffff;
	else if (ctn->x == ctn->x1 || ctn->x == ctn->x2)
	{
		iter = l.from + 1;
		while (iter < l.to)
		{
			pixels[iter * W + ctn->x] = 0xffffffff;
			iter++;
		}
	}
	else if (l.to > l.from)
	{
		pixels[l.from * W + ctn->x] = 0xffffffff;
		iter = l.from + 1;
		float y = 0;

		// float a = ctn->x2 - ctn->x1;
		float b = (ctn->x - ctn->x1);
		float c = ctn->p.y1b - ctn->p.y1a;
		float d = ctn->p.y2b - ctn->p.y2a;
		float min = fmin(c, d);

		x = (int)b % (int)min % sprite->w;
		while (iter < l.to)
		{
			const int pos = y / height * sprite->h;
			pixels[iter * W + ctn->x] = getpixel(sprite, x % sprite->w, pos % sprite->h);
			y++;
			iter++;
		}
		pixels[l.to * W + ctn->x] = 0xffffffff;
	}
}

void				render_ceil(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_floor(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_nfloor(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_nceil(t_drawline l, t_env *env)
{
	vline(l, env);
}

void				render_nwall(t_drawline l, t_env *env)
{
	vline(l, env);
}
