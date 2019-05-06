/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 21:53:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int					elem_mode(t_env *env)
{
	const SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_dropdown		*dropdown = env->editor.dropdown;
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;
	t_elem			*button;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(m.x, m.y, get_element(E_B_ELM_UP, env)->rect))
		{
			if (dropdown[env->editor.curr_elem_dd].idx_element < 0)
				dropdown[env->editor.curr_elem_dd].idx_element++;
			return (1);
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_ELM_DOWN, env)->rect))
		{
			if (dropdown[env->editor.curr_elem_dd].idx_element
			> -dropdown[env->editor.curr_elem_dd].nb_element + 1)
				dropdown[env->editor.curr_elem_dd].idx_element--;
			return (1);
		}
		else if (ui_mouseenter(m.x, m.y, rect))
		{
			if (env->editor.spawn_set == 1)
			{
				float		angle;
				t_pos b = (t_pos){m.x, m.y};
				t_pos a = (t_pos){env->editor.spawn_pos.x,
						env->editor.spawn_pos.y};
				angle = 0;
				if (a.x < b.x)
				{
					if (a.y > b.y)
						angle = atan((a.y - b.y) / (b.x - a.x));
					else
						angle = 2 * M_PI - atan((b.y - a.y) / (b.x - a.x));
				}
				else if (a.x > b.x)
				{
					if (a.y > b.y)
						angle = M_PI / 2 + atan((a.x - b.x) / (a.y - b.y));	
					else
						angle = (M_PI + M_PI / 2) - atan((a.x - b.x) / (b.y - a.y));	
				}
				env->editor.objects->dir = angle;
				env->editor.spawn_dir = env->editor.objects->dir;
				env->editor.spawn_set = 2;
				return (1);
			}
			else if (dropdown[env->editor.curr_elem_dd].current->dd == DD_SPEC
				&& dropdown[env->editor.curr_elem_dd].current->id == 0)
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
			create_object(dropdown[env->editor.curr_elem_dd].current, env);
			return (1);
		}

		int		tab[5] = {
		E_B_ELM_OBWL, E_B_ELM_CONS, E_B_ELM_NTTY, E_B_ELM_PRFB, E_B_ELM_SPEC};
		int		ddtab[5] = {
		DD_WOBJ, DD_CONS, DD_NTTY, DD_PRFB, DD_SPEC};

		int i = 0;
		while (i < 5)
		{
			if (ui_mouseenter(m.x, m.y, get_element(tab[i], env)->rect))
			{
				if (env->editor.curr_elem_btn)
					env->editor.curr_elem_btn->clicked = 0;
				dropdown[env->editor.curr_elem_dd].idx_element = 0;
				get_element(tab[i], env)->clicked = 1;
				env->editor.curr_elem_dd = ddtab[i];
				env->editor.curr_elem_btn = get_element(tab[i], env);
				return (1);
			}
			i++;
		}

		// click on object button
		button = dropdown[env->editor.curr_elem_dd].start;
		while (button)
		{
			if (ui_mouseenter(m.x, m.y, button->rect))
			{
				dropdown[env->editor.curr_elem_dd].current->clicked = 0;
				dropdown[env->editor.curr_elem_dd].current = button;
				dropdown[env->editor.curr_elem_dd].current->clicked = 1;
			}
			button = button->next;
		}
		return (1);
	}
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
