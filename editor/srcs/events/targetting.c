/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:57:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 20:42:49 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_sct       *target_sector(t_pos pos, t_env *env)
{
	t_sct   *sector;

	sector = env->sct_start;
	while (sector && sector->close == 1)
	{
		if (vertex_in_sector(sector, pos))
			return (sector);
		sector = sector->next;
	}
	return (0);
}

static int  filter_edge(const t_pos pos, t_w_vtx *v0, t_w_vtx *v1)
{
	const float     a_y = v0->vtx->pos.y;
	const float     b_y = v1->vtx->pos.y;

	if (a_y < b_y && (pos.y < a_y || pos.y > b_y))
		return (0);
	else if (a_y > b_y && (pos.y < b_y || pos.y > a_y))
		return (0);
	return (1);
}

t_w_vtx		*target_edge(t_pos pos, t_env *env)
{
	t_w_vtx		*w_vtx;
	t_sct		*sct;

	sct = env->sct_start;
	while (sct && sct->close == 1)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx && w_vtx->next)
		{
			if (filter_edge(pos, w_vtx, w_vtx->next))
			{
				if (fabs(pointside(
				pos, w_vtx->vtx->pos, w_vtx->next->vtx->pos)) < 20)
				{
					env->editor.edg_hover = w_vtx;
					return (w_vtx);
				}
			}
			w_vtx = w_vtx->next;
		}
		if (filter_edge(pos, w_vtx, sct->w_vtx_start))
		{
			if (fabs(pointside(
			pos, w_vtx->vtx->pos, sct->w_vtx_start->vtx->pos)) < 20)
			{
				env->editor.edg_hover = w_vtx;
				return (w_vtx);
			}
		}
		sct = sct->next;
	}
	return (0);
}

t_vtx		*target_vertex(t_pos pos, t_env *env)
{
	t_pos	translate;
	t_w_vtx	*w_vtx;
	t_sct	*sct;
	t_pos	calcpos;

	sct = env->sct_start;
	translate.x = 20 + env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = 100 + env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			calcpos.x = (w_vtx->vtx->pos.x * env->pixel_value) + translate.x;
			calcpos.y = (w_vtx->vtx->pos.y * env->pixel_value) + translate.y;
			if (ui_close_to(pos, calcpos, 10))
				return (w_vtx->vtx);
			w_vtx = w_vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_object	*target_object(t_pos pos, t_env *env)
{
	t_pos		translate;
	t_object	*obj;
	t_pos		calcpos;

	obj = env->objects;
	translate.x = 20 + env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = 100 + env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	while (obj)
	{
		calcpos.x = (obj->pos.x * env->pixel_value) + translate.x;
		calcpos.y = (obj->pos.y * env->pixel_value) + translate.y;
		if (ui_close_to(pos, calcpos, 10))
			return (obj);
		obj = obj->next;
	}
	return (0);
}
