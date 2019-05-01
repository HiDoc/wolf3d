/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 17:18:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int				elem_mode(t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	const t_pos		m = env->data->mouse;
	//const int		tab[5] = {
	//E_B_ELM_OBWL, E_B_ELM_CONS, E_B_ELM_NTTY, E_B_ELM_PRFB, E_B_ELM_SPEC};
	const SDL_Event event = env->data->sdl.event;
	//t_elem			*obj_btn;
	//int				i;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(m.x, m.y, get_element(E_B_ELM_UP, env)->rect))
		{
			(env->editor.dropdown[env->editor.elem_mode].idx_element < 0)
				? env->editor.dropdown[env->editor.elem_mode].idx_element++ : 0;
			return (1);
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_ELM_DOWN, env)->rect))
		{
			(env->editor.dropdown[env->editor.elem_mode].idx_element
			> -env->editor.dropdown[env->editor.elem_mode].nb_element + 1)
				? env->editor.dropdown[env->editor.elem_mode].idx_element-- : 0;
			return (1);
		}
		else if (ui_mouseenter(m.x, m.y, rect) && env->editor.elem_mode > -1)
		{
			if (env->editor.spawn_set == 1)
			{
				env->editor.objects->dir = atan(
				(m.y - env->editor.spawn_pos.y)
				/ (m.x - env->editor.spawn_pos.x));
				env->editor.objects->dir = env->editor.objects->dir * 180 / M_PI;
				printf("[%f]\n",  env->editor.objects->dir);
				env->editor.spawn_dir = env->editor.objects->dir;
				env->editor.spawn_set = 0;
				return (1);
			}
			else if (env->editor.dropdown[env->editor.elem_mode].current->type
					== SPECIAL
				&& env->editor.dropdown[env->editor.elem_mode].current->id == 0)
			{
				if (env->editor.onespawn == 0)
				{
					env->editor.spawn_pos = m;
					env->editor.spawn_set = 1;
					env->editor.onespawn = 1;
				}
				else
				{
					display_error_msg("You can not set two spawns", env);
					return (1);
				}
			}
			create_object(env->editor.dropdown[env->editor.elem_mode].current, env);
			return (1);
		}

		/*i = 0;
		while (i < 5)
		{
			if (ui_mouseenter(m.x, m.y, get_element(tab[i], env)->rect))
			{
				get_element(tab[env->editor.obj_mode], env)->clicked = 0;
				get_element(tab[i], env)->clicked = 1;
				env->editor.idx_btn_obj = 0;
				env->editor.obj_mode = i;
				return (1);
			}
			i++;
		}*/

		// click on object button
		/*obj_btn = env->editor.btn_objs;
		while (obj_btn)
		{
			if (ui_mouseenter(m.x, m.y, obj_btn->rect)
			&& obj_btn->type == env->editor.obj_mode)
			{
				env->editor.elem_mode = obj_btn;
			}
			obj_btn = obj_btn->next;
		}*/
		return (1);
	}
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
