/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:47:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/15 14:01:36 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Check where the hole is and whether we're bumping into a wall.
*/
int		is_bumping(t_engine *e, t_vision *v, const t_sector *curr, unsigned s)
{
	float		hole_low;
	float		hole_high;
	t_sector	neighbour;

	if (curr->neighbors[s] < 0)
		return (1);
	neighbour = e->sectors[curr->neighbors[s]];
	hole_low = fmax(curr->floor, neighbour.floor);
	hole_high = fmin(curr->ceil, neighbour.ceil);
	return (hole_high < e->player.where.z + HEADMARGIN
		|| hole_low > e->player.where.z - v->eyeheight + KNEEHEIGHT);
}

int		is_crossing(const t_vtx player, t_vtx dest, t_edge wall)
{
	const t_vtx	add = add_vertex(player, dest);

	return (intersect_rect(player, add, wall.v1, wall.v2)
		&& pointside(add, wall.v1, wall.v2) < 0);
}
