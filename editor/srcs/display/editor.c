/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 15:14:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_mode_btn(t_elem *elem, t_env *env)
{
	ui_make_rect(env->data->surface, elem->rect, elem->color);
	if ((SDL_BlitScaled(elem->image, 0, env->data->surface, &elem->rect)) < 0)
		 ui_error_exit_sdl("Libui: Blit error on editor display");
}

void			editor(t_env *env)
{
	SDL_Rect		rect;

	if (env->menu.state > 0)
	{
		menu(env);
		return ;
	}

	display_interface(env);

	if (env->editor.mouse_mode == 0)
		display_selection(env);
	else if (env->editor.mouse_mode == 1)
		display_drawing(env);
	else if (env->editor.mouse_mode == 2)
		display_element(env);

	display_button(E_B_SAVE, "SAVE", env);

	// display map name
	rect = (SDL_Rect){20, 65, 0, 25};
	ui_make_string(rect, env->map_name, C_WHITE, env->data);

	// display nb frames
	rect = (SDL_Rect){300, 20, 0, 20};
	ui_make_nbrstring(rect, env->data->nb_frames, C_WHITE, env->data);

	// display error_msg
	rect = (SDL_Rect){30, 120, 0, 20};
	if (env->editor.error_msg)
	{
		(time(0) - env->editor.timestamp < 4)
		? ui_make_string(rect, env->editor.error_msg, C_RED, env->data)
		: lt_release((void**)&env->editor.error_msg);
	}

	// display mouse mode buttons
	display_mode_btn(get_element(E_B_MODE_SELECT, env), env);
	display_mode_btn(get_element(E_B_MODE_MOVE, env), env);
	display_mode_btn(get_element(E_B_MODE_DRAW, env), env);
	display_mode_btn(get_element(E_B_MODE_ELEM, env), env);

	// display nb element TO REMOVE
	rect = (SDL_Rect){30, 150, 0, 20};
	ui_make_string(rect, "Nb sectors : ", C_WHITE, env->data);
	rect = (SDL_Rect){170, 150, 0, 20};
	ui_make_nbrstring(rect, env->nb_sct, C_WHITE, env->data);
	rect = (SDL_Rect){30, 180, 0, 20};
	ui_make_string(rect, "Nb vertex : ", C_WHITE, env->data);
	rect = (SDL_Rect){170, 180, 0, 20};
	ui_make_nbrstring(rect, env->nb_vtx, C_WHITE, env->data);
}
