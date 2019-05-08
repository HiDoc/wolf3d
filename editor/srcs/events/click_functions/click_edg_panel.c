/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_edg_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:19:16 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:27:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			click_edg_split(t_env *env)
{
	t_pos		pos;

	pos = (env->editor.edg_select->next)
	? env->editor.edg_select->next->vtx->pos
	: env->editor.edg_select->sector->w_vtx_start->vtx->pos;
	if (pythagore(env->editor.edg_select->vtx->pos, pos) > 10)
	{
		create_vertex(
		get_edge_center(env->editor.edg_select->vtx->pos, pos), env);
		insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
	}
	else
		display_error_msg("Edge too small to be split", env);
}

void			click_edg_del(t_env *env)
{
	delete_edge(env->editor.edg_select, env);
	env->editor.edg_select = 0;
}
