/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:57:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/18 22:45:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_sct       *target_sector(t_pos pos, t_env *env)
{
	t_sct   *sector;
	t_sct   *target;

	target = 0;
	sector = env->sct_start;
	while (sector && sector->close == 1)
	{
		if (!(env->editor.vtx_hover) && vertex_in_sector(sector, pos))
			target = sector;
		sector = sector->next;
	}
	return (target);
}

t_w_vtx		*target_edge(t_pos pos, t_env *env)
{
	t_w_vtx	*w_vtx;
	t_sct	*sct;

	env->editor.edg_hover = 0;
	sct = env->sct_start;
	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx && w_vtx->next) // peut faire bugger le code
		{
			if (fabs(pointside(
			pos, w_vtx->vtx->pos, w_vtx->next->vtx->pos)) < 10)
			{
				env->editor.edg_hover = w_vtx;
				return (w_vtx);
			}
			w_vtx = w_vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_vtx		*target_vertex(t_env *env)
{
	t_pos	translate;
	t_w_vtx	*w_vtx;
	t_sct	*sct;
	t_pos	pos;

	env->editor.vtx_hover = 0;
	sct = env->sct_start;
	translate.x = 20 + env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = 100 + env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			pos.x = (w_vtx->vtx->pos.x * env->pixel_value) + translate.x;
			pos.y = (w_vtx->vtx->pos.y * env->pixel_value) + translate.y;
			if (ui_close_to(env->data->mouse, pos, 10))
			{
				env->editor.vtx_hover = w_vtx->vtx;
				return (w_vtx->vtx);
			}
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

	env->editor.obj_hover = 0;
	obj = env->objects;
	translate.x = 20 + env->editor.grid_translate.x + env->editor.grid_mouse_var.x;
	translate.y = 100 + env->editor.grid_translate.y + env->editor.grid_mouse_var.y;
	while (obj)
	{
		calcpos.x = (obj->pos.x * env->pixel_value) + translate.x;
		calcpos.y = (obj->pos.y * env->pixel_value) + translate.y;
		if (ui_close_to(pos, calcpos, 10))
		{
			env->editor.obj_hover = obj;
			return (obj);
		}
		obj = obj->next;
	}
	return (0);
}
