/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:08:34 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 21:44:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	acquire_limits(t_engine *e, t_raycast *ctn, t_l_float limit)
{
	float z;

	z = e->player.where.z;
	ctn->lf_current = (t_l_float){limit.ceil - z, limit.floor - z};
	ctn->lf_next = (t_l_float){0, 0};
	if (ctn->neighbor >= 0 && ctn->neighbor < (int)e->nsectors)
	{
		ctn->lf_next = (t_l_float){
			e->sectors[ctn->neighbor].ceil - z,
			e->sectors[ctn->neighbor].floor - z
		};
	}
	ctn->p = calc_projec(e->player.yaw, ctn->lf_current, ctn->rot, ctn->scale);
	ctn->n = calc_projec(e->player.yaw, ctn->lf_next, ctn->rot, ctn->scale);
}

int		transform_vertex(t_raycast *ctn, t_player player, t_vtx v1, t_vtx v2)
{
	ctn->trsl = translation_edge(player.where, v1, v2);
	ctn->rot = rotation_edge(ctn->trsl, player.anglecos, player.anglesin);
	if (ctn->rot.v1.y <= 0 && ctn->rot.v2.y <= 0)
		return (0);
	ctn->li_texture.floor = 0;
	ctn->li_texture.ceil = W_TEXT;
	if (ctn->rot.v1.y <= 0 || ctn->rot.v2.y <= 0)
		clip_view(ctn);
	ctn->scale = scale_edge(ctn->rot);
	ctn->x1 = W / 2 - (int)(ctn->rot.v1.x * ctn->scale.v1.x);
	ctn->x2 = W / 2 - (int)(ctn->rot.v2.x * ctn->scale.v2.x);
	return (1);
}
