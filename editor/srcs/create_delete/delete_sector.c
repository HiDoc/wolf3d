/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:18:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 21:49:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		delete_sct_content(t_sct *sector, t_env *env)
{
	t_w_vtx		*tmp;
	t_object	*obj;
	t_object	*tmp_obj;

	while (sector->w_vtx_start)
	{
		tmp = sector->w_vtx_start->next;
		delete_vertex(sector->w_vtx_start->vtx, env);
		sector->w_vtx_start = tmp;
	}

	obj = env->objects;
	while (obj)
	{
		tmp_obj = obj->next;
		if (obj->sct == sector)
			delete_object(obj, env);
		obj = tmp_obj;
	}
}

void			delete_sector(t_sct *sector, t_env *env)
{
	t_sct		*ptr;

	ptr = env->sct_start;
	if (ptr == sector)
	{
		env->sct_start = ptr->next;
		delete_sct_content(sector, env);
		lt_release(sector);
		env->nb_sct--;
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == sector)
		{
			ptr->next = ptr->next->next;
			delete_sct_content(sector, env);
			lt_release(sector);
		}
		ptr = ptr->next;
	}
	env->nb_sct--;
}
