/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:13:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 16:28:51 by sgalasso         ###   ########.fr       */
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
	new->next = 0;

	if (!(env->editor.vertex))
	{
		env->editor.vertex = new;
	}
	else
	{
		new->next = env->editor.vertex;
		env->editor.vertex = new;;
	}
	env->nb_vtx++;
}
