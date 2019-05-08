/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_obj_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:18:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:25:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		click_obj_del(t_env *env)
{
	delete_object(env->editor.obj_select, env);
	env->editor.obj_select = 0;
}
