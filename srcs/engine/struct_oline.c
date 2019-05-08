/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_oline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 22:56:25 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 23:13:13 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_oline(t_drawline *l, t_oline *oline, const t_raycast *ctn)
{
	oline->x = ctn->x;
	oline->y = (l->from < 0) ? abs(l->from) : 0;
	oline->height = l->to - l->from;
	l->from = clamp(l->from, 0, H - 1);
	l->to = clamp(l->to, 0, H - 1);
	oline->width = ctn->x2 - ctn->x1;
}

void		oline(t_drawline l, t_env *env, SDL_Surface *s)
{
	const t_raycast	*ctn = (t_raycast *)l.container;
	int				*pixels;
	t_oline			oline;

	pixels = (int *)env->sdl.surface->pixels;
	set_oline(&l, &oline, ctn);
	if (l.from == l.to)
		pixels[l.from * W + oline.x] = 0x00;
	else if (l.to > l.from)
	{
		pixels[l.from * W + oline.x] = 0x00;
		oline.iter = l.from + 1;
		while (oline.iter < l.to)
		{
			oline.color = getpixel(s, (int)((ctn->x - ctn->x1) / oline.width
			* s->w) % s->w, (int)(oline.y / oline.height * s->h) % s->h);
			if (oline.color & 0xff)
				pixels[oline.iter * W + oline.x] = oline.color;
			(oline.y)++;
			oline.iter++;
		}
		pixels[l.to * W + oline.x] = 0xFF00FFFF;
	}
}
