/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/03 22:48:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		editor(t_env *env)
{
	SDL_Cursor* cursor;
	t_rect		rect;

	if (env->menu.state > 0)
	{
		menu(env);
		return ;
	}

	display_interface(env);

	if (env->mouse_mode == 0)
	{
		if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)))
			ui_error_exit_sdl("Libui: error cursor texture", env->data);
		SDL_SetCursor(cursor);
		display_selection(env);
	}
	else if (env->mouse_mode == 1)
	{
		if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR)))
			ui_error_exit_sdl("Libui: error cursor texture", env->data);
		SDL_SetCursor(cursor);
		display_drawing(env);
	}
	else if (env->mouse_mode == 2)
	{
		if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)))
			ui_error_exit_sdl("Libui: error cursor texture", env->data);
		SDL_SetCursor(cursor);
		display_element(env);
	}

	// display menu
	ui_make_rect(env->data->surface, get_element(E_B_MENU, env)->rect);
	ui_make_string(get_element(E_B_MENU, env)->rect, "MENU", env->data);
	// display save
	ui_make_rect(env->data->surface, get_element(E_B_SAVE, env)->rect);
	ui_make_string(get_element(E_B_SAVE, env)->rect, "SAVE", env->data);

	// display map name
	rect = (t_rect){20, 65, 0, 25, 0xffffffff};
	ui_make_string(rect, env->map_name, env->data);

	// display nb frames
	rect = (t_rect){300, 20, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->nb_frames, env->data);

	// display nb element
	rect = (t_rect){900, 600, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb sectors : ", env->data);
	rect = (t_rect){1040, 600, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_sct, env->data);
	/*rect = (t_rect){900, 630, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb edges : ", env->data);
	rect = (t_rect){1040, 630, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->edg_index + 1, env->data);*/
	rect = (t_rect){900, 660, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb vertex : ", env->data);
	rect = (t_rect){1040, 660, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_vtx, env->data);

	// display mouse mode buttons
	ui_make_rect(env->data->surface, get_element(E_B_MODE_SELECT, env)->rect);
	ui_make_rect(env->data->surface, get_element(E_B_MODE_MOVE, env)->rect);
	ui_make_rect(env->data->surface, get_element(E_B_MODE_DRAW, env)->rect);
	ui_make_rect(env->data->surface, get_element(E_B_MODE_ELEM, env)->rect);

	// display play
	ui_make_string(get_element(E_B_PLAY, env)->rect, "PLAY", env->data);
	ui_make_rect(env->data->surface, get_element(E_B_PLAY, env)->rect);	
}
