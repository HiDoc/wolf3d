/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:36:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			display_element(t_env *env)
{
	SDL_Rect		rect;
	Uint32			color;

	color = C_WHITE;
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);
	display_button(E_B_ELM_OBWL, "Wall objects", env);
	display_button(E_B_ELM_CONS, "Consumables", env);
	display_button(E_B_ELM_NTTY, "Entities", env);
	display_button(E_B_ELM_PRFB, "Prefabs", env);
	display_button(E_B_ELM_SPEC, "Specials", env);
	display_updown(E_B_ELM_UP, E_B_ELM_DOWN, env);
	rect = (SDL_Rect){900, 280, 200, 470};
	display_editor_dropdown_list(rect, env->editor.curr_elem_dd, env);
}
