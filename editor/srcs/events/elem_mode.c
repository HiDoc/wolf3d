/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/30 16:36:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			elem_mode(t_env *env)
{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_ELM_OBWL, env)->rect))
		{ // button select mode
			env->obj_mode = 0;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_ELM_CONS, env)->rect))
		{ // button select mode
			env->obj_mode = 1;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_ELM_NTTY, env)->rect))
		{ // button select mode
			env->obj_mode = 2;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_ELM_PRFB, env)->rect))
		{ // button select mode
			env->obj_mode = 3;
		}
		else if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
		get_element(E_B_ELM_SPEC, env)->rect))
		{ // button select mode
			env->obj_mode = 4;
		}
		return (1);
}
