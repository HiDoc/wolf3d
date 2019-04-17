/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:57:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 01:52:47 by sgalasso         ###   ########.fr       */
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
		sector->color = C_WHITE;
		if (!(env->vtx_hover) && vertex_in_sector(sector, pos))
			target = sector;
		sector = sector->next;
	}
	return (target);
}

t_vtx		*target_vertex(t_env *env)
{
	t_pos	translate;
	t_sct	*sct;
	t_vtx	*vtx;
	t_pos	pos;

	env->vtx_hover = 0;
	sct = env->sct_start;
	translate.x = 20 + env->grid_translate.x + env->grid_mouse_var.x;
	translate.y = 100 + env->grid_translate.y + env->grid_mouse_var.y;
	while (sct)
	{
		vtx = sct->vtx_start;
		while (vtx)
		{
			pos.x = (vtx->pos.x * env->pixel_value) + translate.x;
			pos.y = (vtx->pos.y * env->pixel_value) + translate.y;
			if (ui_close_to(env->data->mouse, pos, 10))
			{
				env->vtx_hover = vtx;
				return (vtx);
			}
			vtx = vtx->next;
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

	env->obj_hover = 0;
	obj = env->objects;
	translate.x = 20 + env->grid_translate.x + env->grid_mouse_var.x;
	translate.y = 100 + env->grid_translate.y + env->grid_mouse_var.y;
	while (obj)
	{
		calcpos.x = (obj->pos.x * env->pixel_value) + translate.x;
		calcpos.y = (obj->pos.y * env->pixel_value) + translate.y;
		if (ui_close_to(pos, calcpos, 10))
		{
			env->obj_hover = obj;
			return (obj);
		}
		obj = obj->next;
	}
	return (0);
}
