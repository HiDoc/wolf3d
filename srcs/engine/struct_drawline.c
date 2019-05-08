/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_drawline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:51:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 23:21:45 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Draw a vertical line on screen
*/

void	vline(t_drawline l, t_env *env)
{
	int		*pixels;
	int		x;
	int		iter;
	int		y;

	x = ((t_raycast *)l.container)->x;
	pixels	= (int *)env->sdl.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + x] = l.middle;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = 0xff00ffff;
		iter = l.from + 1;
		y = 0;
		while (iter < l.to)
		{
			pixels[iter * W + x] = l.middle;
			y++;
			iter++;
		}
		pixels[l.to * W + x] = 0xff00ffff;
	}
}

void	render_cwall_extra(int iter, t_drawline l, int *pixels, t_raycast *ctn)
{
	iter = l.from + 1;
	while (iter < l.to)
	{
		pixels[iter * W + ctn->x] = 0xffffffff;
		iter++;
	}
}

typedef struct s_cwall
{
	int			iter;
	int			x;
	float		height
}t_cwall;

void	render_cwall(t_drawline l, t_env *env)
{
	t_raycast	*ctn;
	int			*pixels;
	SDL_Surface	*sprite;
	int			iter;
	int			x;

	ctn = ((t_raycast *)l.container);
	pixels	= (int *)env->sdl.surface->pixels;
	sprite = ctn->sprite;
	float height = l.to - l.from;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + ctn->x] = 0xffffffff;
	else if (ctn->x == ctn->x1 || ctn->x == ctn->x2)
		render_cwall_extra(iter, l, pixels, ctn);
	else if (l.to > l.from)
	{
		t_projec p = ctn->p;
		pixels[l.from * W + ctn->x] = 0xffffffff;
		iter = l.from + 1;
		float y = 0;
		float scaley = (ctn->li_sector.ceil - ctn->li_sector.floor) / 20;
		float d = ((p.y2a - p.y1a)) * ((ctn->x2 - ctn->x1)
			- (ctn->x - ctn->x1)) / (ctn->x2 - ctn->x1) - p.y2a;
		x = (ctn->li_texture.floor * ((ctn->x2 - ctn->x) * ctn->rot.v2.y)
			+ ctn->li_texture.ceil * ((ctn->x - ctn->x1) * ctn->rot.v1.y))
			/ ((ctn->x2 - ctn->x) * ctn->rot.v2.y + (ctn->x - ctn->x1) * ctn->rot.v1.y);
		int pos;
		if (p.y1a < 0 && l.from == 0)
		{
			height += d;
			y += d;
			while (iter < l.to)
			{
				pos = (y / height * scaley) * sprite->h;
				pixels[iter * W + ctn->x] = getpixel(sprite, x % sprite->w, pos % sprite->h);
				y++;
				iter++;
			}
		}
		else if (p.y2a < 0 && l.from == 0)
		{
			height += d;
			y += d;
			while (iter < l.to)
			{
				pos = (y / height * scaley) * sprite->h;
				pixels[iter * W + ctn->x] = getpixel(sprite, x % sprite->w, pos % sprite->h);
				y++;
				iter++;
			}
		}
		else
		{
			while (iter < l.to)
			{
				pos = (y / height * scaley) * sprite->h;
				pixels[iter * W + ctn->x] = getpixel(sprite, x % sprite->w, pos % sprite->h);
				y++;
				iter++;
			}
		}
		pixels[l.to * W + ctn->x] = 0xffffffff;
	}
}

void	render_ceil(t_drawline l, t_env *env)
{
	(void)env;
	(void)l;
}

void	render_floor(t_drawline l, t_env *env)
{
	t_raycast	*ctn;
	int			*pixels;
	int			iter;
	int			x;

	return ;
	ctn = ((t_raycast *)l.container);
	x = ctn->x;
	pixels = (int *)env->sdl.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + ctn->x] = l.middle;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = 0xff00ffff;
		iter = l.from + 1;
		while (iter < l.to)
		{
			pixels[iter * W + ctn->x] = 0xAAAAAAFF;
			iter++;
		}
		pixels[l.to * W + ctn->x] = 0xff00ffff;
	}
}
