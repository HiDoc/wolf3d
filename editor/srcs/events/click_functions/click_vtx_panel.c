/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_vtx_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:18:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:25:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		click_vtx_del(t_env *env)
{
	delete_vertex(env->editor.vtx_select, env);
	env->editor.vtx_select = 0;
}
