/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 22:47:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			elem_mode(t_env *env)
{
	int			i;
	const int	tab[5] = {
		E_B_ELM_OBWL, E_B_ELM_CONS, E_B_ELM_NTTY, E_B_ELM_PRFB, E_B_ELM_SPEC};
	t_elem		*obj_btn;

	i = 0;
	while (i < 5)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
					get_element(tab[i], env)->rect))
		{
			env->obj_mode = i;
			return (1);
		}
		i++;
	}
	// click on object button
	obj_btn = env->btn_objs;
	while (obj_btn)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, obj_btn->rect)
				&& obj_btn->type == env->obj_mode)
			env->obj_type = obj_btn->type; // replace by ref
		obj_btn = obj_btn->next;
	}
	return (0);
}
