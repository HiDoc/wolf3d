/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_full_circle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:34:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/13 15:53:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_full_circle(SDL_Surface *surface, t_circle circ)
{
	int		y;
	int		x;

	circ.radius *= 2;
	y = circ.y - circ.radius;
	while (y < circ.y + circ.radius)
	{
		x = circ.y - circ.radius;
		while (x < circ.x + circ.radius)
		{
			if (sqrt(pow(x - circ.x, 2) + pow(y - circ.y, 2)) < circ.radius)
				setpixel(surface, x, y, circ.color);
			x++;
		}
		y++;
	}
}
