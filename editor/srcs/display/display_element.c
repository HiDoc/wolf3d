/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:20:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 17:25:47 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			display_element(t_env *env)
{
	SDL_Rect		rect;
	Uint32			color;

	color = C_WHITE;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);	

	color = (get_element(E_B_ELM_OBWL, env)->clicked == 1) ? C_GREEN : C_WHITE;
	rect = get_element(E_B_ELM_OBWL, env)->rect;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "Wall objects", env->data);

	color = (get_element(E_B_ELM_CONS, env)->clicked == 1) ? C_GREEN : C_WHITE;
	rect = get_element(E_B_ELM_CONS, env)->rect;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "Consumables", env->data);

	color = (get_element(E_B_ELM_NTTY, env)->clicked == 1) ? C_GREEN : C_WHITE;
	rect = get_element(E_B_ELM_NTTY, env)->rect;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "Entities", env->data);

	color = (get_element(E_B_ELM_PRFB, env)->clicked == 1) ? C_GREEN : C_WHITE;
	rect = get_element(E_B_ELM_PRFB, env)->rect;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "Prefabs", env->data);

	color = (get_element(E_B_ELM_SPEC, env)->clicked == 1) ? C_GREEN : C_WHITE;
	rect = get_element(E_B_ELM_SPEC, env)->rect;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "Specials", env->data);

	// up
	if ((SDL_BlitScaled(get_element(E_B_ELM_UP, env)->image,
	0, env->data->surface, &get_element(E_B_ELM_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display element");
	// down
	if ((SDL_BlitScaled(get_element(E_B_ELM_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_ELM_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display element");

	// display buttons
	// + rapport a position debut elem list dans enum DD
	rect = (SDL_Rect){900, 280, 200, 470};
	display_editor_dropdown_list(rect, env->editor.elem_mode + 6, env);
}
