/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:06:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 23:00:33 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	set_circ_pixel(t_circ circ, int x, int y, t_data *data)
{
	ui_set_pixel(data->surface, circ.pos.x + x, circ.pos.y + y, circ.color);
	ui_set_pixel(data->surface, circ.pos.x + y, circ.pos.y + x, circ.color);
	ui_set_pixel(data->surface, circ.pos.x - y, circ.pos.y + x, circ.color);
	ui_set_pixel(data->surface, circ.pos.x - x, circ.pos.y + y, circ.color);
	ui_set_pixel(data->surface, circ.pos.x - x, circ.pos.y - y, circ.color);
	ui_set_pixel(data->surface, circ.pos.x - y, circ.pos.y - x, circ.color);
	ui_set_pixel(data->surface, circ.pos.x + y, circ.pos.y - x, circ.color);
	ui_set_pixel(data->surface, circ.pos.x + x, circ.pos.y - y, circ.color);
}

void		ui_make_circle(t_circ circ, t_data *data)
{
	t_pos	p;
	t_pos	d;
	int		err;

	p.x = circ.radius - 1;
	p.y = 0;
	d.x = 1;
	d.y = 1;
	err = d.x - (circ.radius << 1);
	while (p.x >= p.y)
	{
		set_circ_pixel(circ, (int)p.x, (int)p.y, data);
		if (err <= 0)
		{
			p.y++;
			err += d.y;
			d.y += 2;
		}
		if (err > 0)
		{
			p.x--;
			d.x += 2;
			err += d.x - (circ.radius << 1);
		}
	}
}
