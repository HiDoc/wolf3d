/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_in_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 22:51:52 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:33:12 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

// TEMPORAIRE ////////////////////////////////////////////
static int		max(int a, int b)
{
	return (a > b ? a : b);
}

static int		min(int a, int b)
{
	return (a < b ? a : b);
}

static int		onsegment(t_pos p, t_pos q, t_pos r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
	&& q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return (1);
	return (0);
}

static int		orientation(t_pos p, t_pos q, t_pos r)
{
	float		val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int				intersect_vrx(t_pos p1, t_pos q1, t_pos p2, t_pos q2)
{
	float	o1;
	float	o2;
	float	o3;
	float	o4;

	o1 = orientation(p1, q1, p2);
	o2 = orientation(p1, q1, q2);
	o3 = orientation(p2, q2, p1);
	o4 = orientation(p2, q2, q1);
	if (o1 != o2 && o3 != o4)
		return (1);
	if (o1 == 0 && onsegment(p1, p2, q1))
		return (1);
	if (o2 == 0 && onsegment(p1, q2, q1))
		return (1);
	if (o3 == 0 && onsegment(p2, p1, q2))
		return (1);
	if (o4 == 0 && onsegment(p2, q1, q2))
		return (1);
	return (0);
}
//////////////////////////////////////////////////////////////

static int		filter_target(t_pos pos, t_sct *sector)
{
	return (pos.x >= sector->xmin && pos.x <= sector->xmax
		&& pos.y >= sector->ymin && pos.y <= sector->ymax);
}

static int		filter_edges(const t_pos pos, t_w_vtx *w_vtx)
{
	const float		a_y = w_vtx->vtx->pos.y;
	const float		b_y = w_vtx->next->vtx->pos.y;

	if (a_y < b_y && (pos.y < a_y || pos.y > b_y))
		return (0);
	else if (a_y > b_y && (pos.y < b_y || pos.y > a_y))
		return (0);
	return (1);
}

int				vertex_in_sector(t_sct *sector, t_pos pos_b)
{
	const t_pos	pos_a = (t_pos){sector->xmin, pos_b.y};
	t_w_vtx		*w_vtx;
	int			intersect;

	intersect = 0;
	if (!(filter_target(pos_b, sector)))
		return (0);
	w_vtx = sector->w_vtx_start;
	while (w_vtx && w_vtx->next)
	{
		if (filter_edges((const t_pos)pos_b, w_vtx))
		{
			if ((intersect_vrx(
			w_vtx->vtx->pos, w_vtx->next->vtx->pos, pos_a, pos_b)))
				intersect++;
		}
		w_vtx = w_vtx->next;
	}
	if ((intersect_vrx(
	w_vtx->vtx->pos, sector->w_vtx_start->vtx->pos, pos_a, pos_b)))
		intersect++;
	return (intersect % 2);
}
