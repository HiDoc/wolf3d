/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 17:22:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/22 12:46:46 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ui_draw_line(SDL_Surface *surf, t_edge edg, Uint32 color)
{
	t_vtx d;
	t_vtx s;
	t_vtx e;

	d.x = fabs(edg.v2.x - edg.v1.x);
	d.y = fabs(edg.v2.y - edg.v1.y);
	s.x = edg.v1.x < edg.v2.x ? 1 : -1;
	s.y = edg.v1.y < edg.v2.y ? 1 : -1;
	e.x = (d.x > d.y ? d.x : -d.y) / 2;
	while (abs(dist_vertex(edg.v1, edg.v2) > 1))
	{
		if (edg.v1.x < surf->w && edg.v1.y < surf->h && edg.v1.x >= 0 && edg.v1.y >= 0)
			setpixel(surf, (int)edg.v1.x, (int)edg.v1.y, color);
		e.y = e.x;
		if (e.y >-d.x)
		{
			e.x -= d.y;
			edg.v1.x += s.x;
		}
		if (e.y < d.y)
		{
			e.x += d.x;
			edg.v1.y += s.y;
		}
	}
}