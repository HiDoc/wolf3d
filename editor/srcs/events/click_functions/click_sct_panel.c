/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_sct_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:19:04 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:27:11 by sgalasso         ###   ########.fr       */
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

void		click_sct_hceil(t_env *env)
{
	get_element(E_I_SELEC_HCEIL, env)->clicked = 1;
}

void		click_sct_hfloor(t_env *env)
{
	get_element(E_I_SELEC_HFLOOR, env)->clicked = 1;
}

void		click_sct_gravity(t_env *env)
{
	get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
}

void		click_sct_ceil(t_env *env)
{
	env->editor.sct_select->roof = 1;
	get_element(E_B_SELEC_CEIL, env)->clicked = 1;
	get_element(E_B_SELEC_SKY, env)->clicked = 0;
}

void		click_sct_sky(t_env *env)
{
	env->editor.sct_select->roof = 0;
	get_element(E_B_SELEC_CEIL, env)->clicked = 0;
	get_element(E_B_SELEC_SKY, env)->clicked = 1;
}

void		click_sct_del(t_env *env)
{
	delete_sector(env->editor.sct_select, env);
	env->editor.sct_select = 0;
}
