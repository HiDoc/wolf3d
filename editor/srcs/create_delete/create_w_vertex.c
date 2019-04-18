/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_w_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 01:05:43 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/18 04:38:07 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
		env->sct_current->w_vtx_end = new;
	}
	else
	{
		env->sct_current->w_vtx_current = new;
		env->sct_current->w_vtx_end->next = new;
		env->sct_current->w_vtx_end = new;
	}

	// stock xmin xmax ymin ymax
	(new->vtx->pos.x < env->sct_current->xmin) ? env->sct_current->xmin = new->vtx->pos.x : 0;
	(new->vtx->pos.x > env->sct_current->xmax) ? env->sct_current->xmax = new->vtx->pos.x : 0;
	(new->vtx->pos.y < env->sct_current->ymin) ? env->sct_current->ymin = new->vtx->pos.y : 0;
	(new->vtx->pos.y > env->sct_current->ymax) ? env->sct_current->ymax = new->vtx->pos.y : 0;
}
