/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:06:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/16 14:45:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

//
// TO RECODE !!!
//

void	ui_make_circle(t_circ circ, t_data *data)
{
	int x = circ.radius-1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (circ.radius << 1);

	while (x >= y)
	{
		ui_set_pixel(data->surface, circ.x + x, circ.y + y, circ.color);
		ui_set_pixel(data->surface, circ.x + y, circ.y + x, circ.color);
		ui_set_pixel(data->surface, circ.x - y, circ.y + x, circ.color);
		ui_set_pixel(data->surface, circ.x - x, circ.y + y, circ.color);
		ui_set_pixel(data->surface, circ.x - x, circ.y - y, circ.color);
		ui_set_pixel(data->surface, circ.x - y, circ.y - x, circ.color);
		ui_set_pixel(data->surface, circ.x + y, circ.y - x, circ.color);
		ui_set_pixel(data->surface, circ.x + x, circ.y - y, circ.color);

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
			err += dx - (circ.radius << 1);
		}
	}
}
