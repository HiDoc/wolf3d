/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cwall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:37:09 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 23:52:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	cwall_loop(t_cwall cwall, int *pixels, SDL_Surface *sprite,
		t_drawline l)
{
	t_raycast	*ctn;

	ctn = ((t_raycast *)l.container);
	cwall.height += cwall.d;
	cwall.y += cwall.d;
	while (cwall.iter < l.to)
	{
		cwall.pos = (cwall.y / cwall.height * cwall.scaley) * sprite->h;
		pixels[cwall.iter * W + ctn->x] = getpixel(sprite, cwall.x
			% sprite->w, cwall.pos % sprite->h);
		cwall.y++;
		cwall.iter++;
	}
}

void	calc_cwall(t_cwall *cwall, t_drawline l, t_raycast *ctn)
{
	cwall->p = ctn->p;
	cwall->iter = l.from + 1;
	cwall->y = 0;
	cwall->scaley = (ctn->li_sector.ceil - ctn->li_sector.floor) / 20;
	cwall->d = ((cwall->p.y2a - cwall->p.y1a)) * ((ctn->x2 - ctn->x1)
		- (ctn->x - ctn->x1)) / (ctn->x2 - ctn->x1) - cwall->p.y2a;
	cwall->x = (ctn->li_texture.floor * ((ctn->x2 - ctn->x) * ctn->rot.v2.y)
		+ ctn->li_texture.ceil * ((ctn->x - ctn->x1) * ctn->rot.v1.y))
		/ ((ctn->x2 - ctn->x) * ctn->rot.v2.y + (ctn->x - ctn->x1)
		* ctn->rot.v1.y);
}

void	cwall_loop2(t_cwall cwall, int *pixels, SDL_Surface *sprite,
		t_drawline l)
{
	t_raycast	*ctn;

	ctn = ((t_raycast *)l.container);
	while (cwall.iter < l.to)
	{
		cwall.pos = (cwall.y / cwall.height * cwall.scaley) * sprite->h;
		pixels[cwall.iter * W + ctn->x] = getpixel(sprite, cwall.x
			% sprite->w, cwall.pos % sprite->h);
		cwall.y++;
		cwall.iter++;
	}
}

void	cwall_loop1(t_cwall cwall, int *pixels, SDL_Surface *sprite,
		t_drawline l)
{
	t_raycast	*ctn;

	ctn = ((t_raycast *)l.container);
	while (cwall.iter < l.to)
	{
		cwall.pos = (cwall.y / cwall.height * cwall.scaley) * sprite->h;
		pixels[cwall.iter * W + ctn->x] = getpixel(sprite, cwall.x
			% sprite->w, cwall.pos % sprite->h);
		cwall.y++;
		cwall.iter++;
	}
}

void	render_cwall(t_drawline l, t_env *env)
{
	t_raycast	*ctn;
	int			*pixels;
	SDL_Surface	*sprite;
	t_cwall		cwall;

	ctn = ((t_raycast *)l.container);
	pixels = (int *)env->sdl.surface->pixels;
	sprite = ctn->sprite;
	cwall.height = l.to - l.from;
	cwall.iter = 0;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + ctn->x] = 0xffffffff;
	else if (ctn->x == ctn->x1 || ctn->x == ctn->x2)
		cwall_loop1(cwall, pixels, sprite, l);
	else if (l.to > l.from)
	{
		calc_cwall(&cwall, l, ctn);
		if (cwall.p.y1a < 0 && l.from == 0 || cwall.p.y2a < 0 && l.from == 0)
			cwall_loop(cwall, pixels, sprite, l);
		else
			cwall_loop2(cwall, pixels, sprite, l);
	}
}
