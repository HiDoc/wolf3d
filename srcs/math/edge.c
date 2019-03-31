/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:44:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/29 20:36:30 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Return if line have an intersection
*/
int		intersec_edge(t_vtx v0, t_vtx v1, t_vtx v2, t_vtx v3)
{
	return (intersect_rect(v0, v1, v2, v3)
	&& fabs(pointside(v2, v0, v1) + pointside(v3, v0, v1)) != 2
	&& fabs(pointside(v0, v2, v3) + pointside(v1, v2, v3)) != 2);
}

/*
** Build an edge with current vectex and next vertex in sector
*/
t_edge  translation_edge(t_vctr player_position, t_vtx v1, t_vtx v2)
{
	t_edge		edge;

	edge.v1 = (t_vtx){v1.x - player_position.x, v1.y - player_position.y};
	edge.v2 = (t_vtx){v2.x - player_position.x, v2.y - player_position.y};
	return (edge);
}

/*
** Build an edge with same rotation as the player
*/
t_edge  rotation_edge(t_edge v, float pcos, float psin)
{
	t_edge		edge;

	edge.v1 = (t_vtx){
		v.v1.x * psin - v.v1.y * pcos,
		v.v1.x * pcos + v.v1.y * psin
	};
	edge.v2 = (t_vtx){
		v.v2.x * psin - v.v2.y * pcos,
		v.v2.x * pcos + v.v2.y * psin
	};
	return (edge);
}

/*
** Build an edge with scale from perspective projection
** using field of view
*/
t_edge  scale_edge(t_edge t)
{
	t_edge		edge;

	edge.v1 = (t_vtx){HFOV / t.v1.y, VFOV / t.v1.y};
	edge.v2 = (t_vtx){HFOV / t.v2.y, VFOV / t.v2.y};
	return (edge);
}

/*
** Clip vertex to window and save scaled texture coordinate
*/
void	clip_view(t_raycast *ctn)
{
	t_edge		*t = &ctn->rot;
	const t_vtx org1 = {t->v1.x, t->v1.y};
	const t_vtx org2 = {t->v2.x, t->v2.y};
	const t_vtx i1 = intersect_vtx(t->v1, t->v2,
		(t_vtx){-NEARSIDE, NEARZ}, (t_vtx){-FARSIDE, FARZ});
	const t_vtx i2 = intersect_vtx(t->v1, t->v2,
		(t_vtx){NEARSIDE, NEARZ}, (t_vtx){FARSIDE, FARZ});

	if (t->v1.y < NEARZ)
	{
		t->v1.x = (i1.y > 0) ? i1.x : i2.x;
		t->v1.y = (i1.y > 0) ? i1.y : i2.y;
	}
	if (t->v2.y < NEARZ)
	{
		t->v2.x = (i1.y > 0) ? i1.x : i2.x;
		t->v2.y = (i1.y > 0) ? i1.y : i2.y;
	}
	if (fabs(t->v2.x - t->v1.x) > fabs(t->v2.y - t->v1.y))
	{
		ctn->li_texture.floor = (t->v1.x - org1.x) * W_TEXT / (org2.x - org1.x);
		ctn->li_texture.ceil = (t->v2.x - org1.x) * W_TEXT / (org2.x - org1.x);
	}
	else
	{
		ctn->li_texture.floor = (t->v1.y - org1.y) * W_TEXT / (org2.y - org1.y);
		ctn->li_texture.ceil = (t->v2.y - org1.y) * W_TEXT / (org2.y - org1.y);
	}
}
