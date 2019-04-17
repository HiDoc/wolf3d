/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:13:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 04:14:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_vertex(t_pos pos, t_env *env)
{
	t_vtx	*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_vtx)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->sector = env->sct_current;
	new->next = 0;

	if (!(env->sct_current->vtx_start))
	{
		env->sct_current->vtx_current = new;
		env->sct_current->vtx_start = new;
		env->sct_current->vtx_end = new;
	}
	else
	{
		env->sct_current->vtx_current = new;
		env->sct_current->vtx_end->next = new;
		env->sct_current->vtx_end = new;
	}

	// stock xmin xmax ymin ymax
	(pos.x < env->sct_current->xmin) ? env->sct_current->xmin = pos.x : 0;
	(pos.x > env->sct_current->xmax) ? env->sct_current->xmax = pos.x : 0;
	(pos.y < env->sct_current->ymin) ? env->sct_current->ymin = pos.y : 0;
	(pos.y > env->sct_current->ymax) ? env->sct_current->ymax = pos.y : 0;
	env->nb_vtx++;
}
