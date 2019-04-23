/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:57:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/23 16:20:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_sct       *target_sector(t_pos pos, t_env *env)
{
	t_sct   *sector;

	sector = env->sct_start;
	while (sector)
	{
		if (sector->close == 1)
		{
			if (vertex_in_sector(sector, pos))
				return (sector);
		}
		sector = sector->next;
	}
	return (0);
}

/*static*/ int  filter_edge(const t_pos pos, t_pos p0, t_pos p1, t_env *env)
{
	p0 = vtx_transform(p0, env);
	p1 = vtx_transform(p1, env);

	if (p0.y < p1.y && (pos.y < p0.y || pos.y > p1.y))
		return (0);
	else if (p0.y > p1.y && (pos.y < p1.y || pos.y > p0.y))
		return (0);
	return (1);
}

t_w_vtx		*target_edge(t_pos pos, t_env *env)
{
	t_w_vtx		*w_vtx;
	t_sct		*sct;
	int i;

	sct = env->sct_start;
	while (sct && sct->close == 1)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx && w_vtx->next)
		{
			//if (filter_edge(pos, w_vtx->vtx->pos, w_vtx->next->vtx->pos, env))
			//{
				i = fabs(pointside(pos, vtx_transform(w_vtx->vtx->pos, env),
				vtx_transform(w_vtx->next->vtx->pos, env)));
				printf("%d\n", i);
				if (i < (50 * env->grid_scale))
				{
					env->editor.edg_hover = w_vtx;
					return (w_vtx);
				}
			//}
			w_vtx = w_vtx->next;
		}
		//if (filter_edge(pos, w_vtx->vtx->pos, sct->w_vtx_start->vtx->pos, env))
		//{
			i = fabs(pointside(pos, vtx_transform(w_vtx->vtx->pos, env),
			vtx_transform(sct->w_vtx_start->vtx->pos, env)));
			printf("%d\n", i);
			if (i < (50 * env->grid_scale))
			{
				env->editor.edg_hover = w_vtx;
				return (w_vtx);
			}
		//}
		sct = sct->next;
	}
	return (0);
}

t_vtx		*target_vertex(t_pos pos, t_env *env)
{
	t_w_vtx			*w_vtx;
	t_sct			*sct;

	sct = env->sct_start;
	while (sct)
	{
		w_vtx = sct->w_vtx_start;
		while (w_vtx)
		{
			if (ui_close_to(pos, vtx_transform(w_vtx->vtx->pos, env), 10))
				return (w_vtx->vtx);
			w_vtx = w_vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_object	*target_object(t_pos pos, t_env *env)
{
	t_object		*obj;

	obj = env->objects;
	while (obj)
	{
		if (ui_close_to(pos, vtx_transform(obj->pos, env), 10))
			return (obj);
		obj = obj->next;
	}
	return (0);
}
