/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_edge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:47:39 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 13:57:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			delete_edge(t_w_vtx *w_vtx, t_env *env)
{
	(w_vtx && w_vtx->next) ? delete_vertex(w_vtx->next->vtx, env) : 0;
	(w_vtx) ? delete_vertex(w_vtx->vtx, env) : 0;
}
