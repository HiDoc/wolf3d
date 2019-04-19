/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_w_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 01:05:43 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 19:30:39 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		insert_w_vertex(t_w_vtx *prev, t_vtx *vtx, t_env *env)
{
	t_w_vtx		*new;
	t_w_vtx		*ptr;

	if (!(new = lt_push(ft_memalloc(sizeof(t_w_vtx)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->vtx = vtx;
	new->sector = env->editor.edg_select->sector;

	ptr = prev->sector->w_vtx_start;
	while (ptr)
	{
		if (ptr == prev)
		{
			new->next = ptr->next;
			prev->next = new;
		}
		ptr = ptr->next;
	}
	env->editor.edg_select->sector->nb_w_vtx++;
}

void		create_w_vertex(t_vtx *vtx, t_env *env)
{
	t_w_vtx		*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_w_vtx)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->vtx = vtx;
	new->sector = env->sct_current;
	new->next = 0;

	if (!(env->sct_current->w_vtx_start))
	{
		env->sct_current->w_vtx_current = new;
		env->sct_current->w_vtx_start = new;
	}
	else
	{
		new->next = env->sct_current->w_vtx_start;
		env->sct_current->w_vtx_current = new;
		env->sct_current->w_vtx_start = new;
	}
	env->sct_current->nb_w_vtx++;
	sync_sct_minmax(env);
}
