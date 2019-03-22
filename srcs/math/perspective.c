/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:33:54 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/22 15:39:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	affine(t_perspective *ctn, size_t i)
{
	ctn->from.x = ctn->bot.v1.x + (ctn->bot.v2.x - ctn->bot.v1.x)
		/ ctn->col * i;
	ctn->from.y = ctn->bot.v1.y;
}

void	set_maxima_minima(t_perspective *ctn, size_t i, float a, float b)
{
	if (i == 0)
	{
		ctn->top.v1.x = ctn->horizon.x;
		ctn->a.floor = a;
		ctn->b.floor = b;
	}
	else if (i == ctn->col)
	{
		ctn->top.v2.x = ctn->horizon.x;
		ctn->a.ceil = a;
		ctn->b.ceil = b;
	}
}

void	horizontal(SDL_Surface *surface, t_perspective *ctn)
{
	float		a;
	float		b;
	size_t		i;

	i = 0;
	while (i <= ctn->col)
	{
		affine(ctn, i);
		if (ctn->from.x != ctn->vanish.x)
		{
			a = (ctn->from.y - ctn->vanish.y) / (ctn->from.x - ctn->vanish.x);
			b = ctn->vanish.y - (a * ctn->vanish.x);
			ctn->horizon.x = (ctn->horizon.y - b) / a;
		}
		else
			ctn->horizon.x = ctn->from.x;
		ui_draw_line(surface, (t_edge){ctn->from, ctn->horizon}, 0xffff00ff);
		set_maxima_minima(ctn, i, a, b);
		i++;
	}
}

void	vertical(SDL_Surface *surface, t_perspective ctn)
{
	float	ratio = 0.8;
	size_t	i;

	i = 0;
	ctn.row += 1;
	ctn.height = (ctn.horizon.y - ctn.bot.v1.y) * (ratio - 1)
	/ (pow(ratio, (ctn.row - 1)) - 1);
	ctn.from.y = ctn.bot.v1.y;
	ctn.to.y = ctn.bot.v1.y;
	ctn.to.x = 0;

	while (i < ctn.row)
	{
		ctn.from.x = (ctn.from.y - ctn.b.floor) / ctn.a.floor;
		ctn.to.x = (ctn.to.y - ctn.b.ceil) / ctn.a.ceil;
		ui_draw_line(surface,(t_edge){ctn.from, ctn.to}, 0xffffFF);
		ctn.from.y += ctn.height;
		ctn.to.y += ctn.height;
		ctn.height *= ratio;
		i++;
	}
}

void	draw_perspective(SDL_Surface *surface,
		t_square square, t_vtx horizon, t_vtx vanish)
{
	t_perspective ctn;

	ctn.vanish = vanish;
	ctn.horizon = horizon;

	ctn.bot = square.bot;
	ctn.top = square.top;
	ctn.col = 5;
	ctn.row = 8;
	ctn.height = 40;

	ctn.a.floor = 0;
	ctn.a.ceil = 0;
	ctn.b.floor = 0;
	ctn.b.ceil = 0;
	horizontal(surface, &ctn);
	vertical(surface, ctn);
}