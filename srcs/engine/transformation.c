/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:08:34 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/22 13:04:18 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	acquire_limits(t_engine *e, t_queue *q, t_raycast *ctn, int s)
{
	/* Check the edge type. neighbor=-1 means wall,
	** other=boundary between two e->sectors. */
	ctn->neighbor = q->sect->neighbors[s];

	/* Acquire the floor and ceiling heights,
	** relative to where the player's view is */
	ctn->lf_current = (t_l_float){q->sect->ceil - e->player.where.z,
		q->sect->floor - e->player.where.z};
	ctn->lf_next = (t_l_float){0, 0};
	if (ctn->neighbor >= 0)
	{
		ctn->lf_next = (t_l_float){
			e->sectors[ctn->neighbor].ceil - e->player.where.z,
			e->sectors[ctn->neighbor].floor - e->player.where.z
		};
	}

	/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
	ctn->p = calc_projec(e->player.yaw, ctn->lf_current, ctn->rot, ctn->scale);
	ctn->n = calc_projec(e->player.yaw, ctn->lf_next, ctn->rot, ctn->scale);
}

int		transform_vertex(t_engine *e, t_queue *q, t_raycast *ctn, int s)
{
	/* Acquire the x,y coordinates of the two endpoints
	** (vertices) of this edge of the sector */
	ctn->trsl = translation_edge(e->player.where,
		q->sect->vertex[s], q->sect->vertex[s + 1]);

	/* Rotate them around the player's view */
	ctn->rot = rotation_edge(e->player, ctn->trsl);

	/* Is the wall at least partially in front of the player? */
	if (ctn->rot.v1.y <= 0 && ctn->rot.v2.y <= 0)
		return (0);

	/* If it's partially behind the player,
	** clip it against player's view frustrum */

	ctn->li_texture.floor = 0;
	ctn->li_texture.ceil = W_TEXTURE;
	if (ctn->rot.v1.y <= 0 || ctn->rot.v2.y <= 0)
		clip_view(ctn);

	/* Do perspective transformation */
	ctn->scale = scale_edge(ctn->rot);
	ctn->x1 = W/2 - (int)(ctn->rot.v1.x * ctn->scale.v1.x);
	ctn->x2 = W/2 - (int)(ctn->rot.v2.x * ctn->scale.v2.x);

	/* Verify if transformation is visible */
	if (ctn->x1 >= ctn->x2 || ctn->x2 < q->now.sx1 || ctn->x1 > q->now.sx2)
		return (0);
	return (1);
}