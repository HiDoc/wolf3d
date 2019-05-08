/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:46:38 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 20:00:39 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		set_circ_pixel(SDL_Surface *surface,
				t_circle circ, int x, int y)
{
	setpixel(surface, circ.x + x, circ.y + y, circ.color);
	setpixel(surface, circ.x + y, circ.y + x, circ.color);
	setpixel(surface, circ.x - y, circ.y + x, circ.color);
	setpixel(surface, circ.x - x, circ.y + y, circ.color);
	setpixel(surface, circ.x - x, circ.y - y, circ.color);
	setpixel(surface, circ.x - y, circ.y - x, circ.color);
	setpixel(surface, circ.x + y, circ.y - x, circ.color);
	setpixel(surface, circ.x + x, circ.y - y, circ.color);
}

void			ui_draw_circle(SDL_Surface *surface, t_circle circ)
{
	float x = circ.radius - 1;
	float y = 0;
	float dx = 1;
	float dy = 1;
	float err = dx - ((int)circ.radius << 1);

	while (x >= y)
	{
		set_circ_pixel(surface, circ, x, y);
		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx - ((int)circ.radius << 1);
		}
	}
}
