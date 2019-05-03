/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 21:07:44 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 16:08:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		bresenham_tab(int *tab, t_pos p1, t_pos p2)
{
	tab[0] = abs((int)p2.x - (int)p1.x);
	tab[1] = (int)p1.x < (int)p2.x ? 1 : -1;
	tab[2] = abs((int)p2.y - (int)p1.y);
	tab[3] = (int)p1.y < (int)p2.y ? 1 : -1;
	tab[4] = (tab[0] > tab[2] ? tab[0] : -tab[2]) / 2;
}

void		ui_make_line(SDL_Surface *surface, t_vec vec, Uint32 color)
{
	int e2;
	int tab[5];

	bresenham_tab(tab, vec.a, vec.b);
	while (!((int)vec.a.x == (int)vec.b.x && (int)vec.a.y == (int)vec.b.y))
	{
		ui_set_pixel(surface, (int)vec.a.x, (int)vec.a.y, color);
		e2 = tab[4];
		if (e2 > -tab[0] && (int)vec.a.x != (int)vec.b.x)
		{
			tab[4] -= tab[2];
			vec.a.x = (int)vec.a.x + tab[1];
		}
		if (e2 < tab[2] && (int)vec.a.y != (int)vec.b.y)
		{
			tab[4] += tab[0];
			vec.a.y = (int)vec.a.y + tab[3];
		}
	}
}
