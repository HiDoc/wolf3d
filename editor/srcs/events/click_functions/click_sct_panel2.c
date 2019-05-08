/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_sct_panel2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:16:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:16:54 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		click_sct_normal(t_env *env)
{
	get_element(E_B_SELEC_DOOR, env)->clicked = 0;
	get_element(E_B_SELEC_FDOOR, env)->clicked = 0;
	get_element(E_B_SELEC_NORMAL, env)->clicked = 1;
	if (env->editor.sct_select->type == 2)
		env->editor.oneend = 0;
	env->editor.sct_select->type = 0;
}

void		click_sct_door(t_env *env)
{
	get_element(E_B_SELEC_FDOOR, env)->clicked = 0;
	get_element(E_B_SELEC_NORMAL, env)->clicked = 0;
	get_element(E_B_SELEC_DOOR, env)->clicked = 1;
	if (env->editor.sct_select->type == 2)
		env->editor.oneend = 0;
	env->editor.sct_select->type = 1;
}

void		click_sct_fdoor(t_env *env)
{
	get_element(E_B_SELEC_NORMAL, env)->clicked = 0;
	get_element(E_B_SELEC_DOOR, env)->clicked = 0;
	get_element(E_B_SELEC_FDOOR, env)->clicked = 1;
	if (env->editor.oneend == 1)
		display_error_msg("You can not have 2 end system", env);
	else
	{
		env->editor.oneend = 1;
		env->editor.sct_select->type = 2;
	}
}

void		click_sct_del(t_env *env)
{
	delete_sector(env->editor.sct_select, env);
	env->editor.sct_select = 0;
}
