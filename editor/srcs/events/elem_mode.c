/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 22:13:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			elem_mode(t_env *env)
{
	const t_pos		m = env->data->mouse;
	const int		tab[5] = {
	E_B_ELM_OBWL, E_B_ELM_CONS, E_B_ELM_NTTY, E_B_ELM_PRFB, E_B_ELM_SPEC};
	const SDL_Event event = env->data->sdl.event;
	t_elem			*obj_btn;
	int				i;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(m.x, m.y, get_element(E_R_RECT, env)->rect) && env->obj_elem)
		{ // si click sur interface et object selectionne
			if (env->editor.sct_hover)
			{
				if (env->spawn_set == 1)
				{
					env->objects->dir = atan(
					(env->data->mouse.y - env->objects->pos.y) /
					(env->data->mouse.x - env->objects->pos.x));
					env->spawn_set = 0;
					return (1);
				}
				else if (env->obj_elem->type == SPECIAL && env->obj_elem->id == 0)
				{ // if spawn
					env->spawn_set = 1;
				}
				create_object(env->obj_elem, env);
			}
			return (1);
		}

		i = 0;
		while (i < 5)
		{
			if (ui_mouseenter(m.x, m.y, get_element(tab[i], env)->rect))
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
			if (ui_mouseenter(m.x, m.y, obj_btn->rect)
			&& obj_btn->type == env->obj_mode)
				env->obj_elem = obj_btn;
			obj_btn = obj_btn->next;
		}
	}
	if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
