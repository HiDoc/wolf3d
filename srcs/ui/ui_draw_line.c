/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 17:22:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/19 18:43:59 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		bresenham_tab(int *tab, t_vtx v1, t_vtx v2)
{
	tab[0]	 = abs((int)v2.x - (int)v1.x);
	tab[1] = (int)v1.x < (int)v2.x ? 1 : -1;
	tab[2] = abs((int)v2.y - (int)v1.y);
	tab[3] = (int)v1.y < (int)v2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void		ui_draw_line(SDL_Surface *surface, t_edge edge, Uint32 color)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, edge.v1, edge.v2);
	while (!((int)edge.v1.x == (int)edge.v2.x && (int)edge.v1.y == (int)edge.v2.y))
	{
		setpixel(surface, (int)edge.v1.x, (int)edge.v1.y, color);
		e2 = tab[4];
		if (e2 > -tab[0] && (int)edge.v1.x != (int)edge.v2.x)
		{
			tab[4] -= tab[2];
			edge.v1.x = (int)edge.v1.x + tab[1];
		}
		if (e2 < tab[2] && (int)edge.v1.y != (int)edge.v2.y)
		{
			tab[4] += tab[0];
			edge.v1.y = (int)edge.v1.y + tab[3];
		}
	}
}
