/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:11:36 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 21:18:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Verify is player is not in a wall
*/

int		sector_collision(t_vtx player, t_vtx *dest, t_edge wall)
{
	t_vtx		b;
	float		scale;

	b = (t_vtx)diff_vertex(wall.v2, wall.v1);
	scale = (dest->x * b.x + b.y * dest->y) / (b.x * b.x + b.y * b.y);
	dest->x = b.x * scale;
	dest->y = b.y * scale;
	return (pointside(add_vertex(player, *dest), wall.v1, wall.v2) < 0.3);
}

void	set_new_sector(t_engine *e, t_edge dest, t_sector *sect, int s)
{
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0
			&& is_crossing(dest.v1, dest.v2, sect->vertex, s))
		{
			e->player.sector = sect->neighbors[s];
			break ;
		}
	}
}

/*
** Collision detection.
** Check if the player is crossing an edge and if this edge has a neighbour
*/

void	collision(t_vision *v, t_engine *e, t_sector *sect)
{
	t_vtx		player;
	t_vtx		*vert;
	t_vtx		dest;
	t_edge		wall;
	int			s;

	s = -1;
	vert = sect->vertex;
	player = (t_vtx){e->player.where.x, e->player.where.y};
	dest = (t_vtx){e->player.velocity.x, e->player.velocity.y};
	while (++s < (int)sect->npoints)
	{
		wall = (t_edge){vert[s], vert[s + 1]};
		if (is_crossing(player, dest, vert, s) && is_bumping(sect, v, s, e)
			&& sector_collision(player, &dest, wall))
			v->moving = 0;
	}
	s = -1;
	set_new_sector(e, (t_edge){player, dest}, sect, s);
	e->player.where.x += dest.x;
	e->player.where.y += dest.y;
	v->falling = 1;
}
