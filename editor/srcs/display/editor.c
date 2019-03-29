/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/29 14:25:09 by sgalasso         ###   ########.fr       */
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

	// display new
	ui_make_rect(env->data->surface, get_element(E_B_NEW, env)->rect);
	rect = (t_rect){45, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "New", env->data);	
	// display upload
	ui_make_rect(env->data->surface, get_element(E_B_UPLOAD, env)->rect);
	rect = (t_rect){155, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "Upload", env->data);
	// display save
	ui_make_rect(env->data->surface, get_element(E_B_SAVE, env)->rect);
	rect = (t_rect){324, 30, 0, 25, 0xffffffff};
	ui_make_string(rect, "save", env->data);

	// display map name
	rect = (t_rect){450, 30, 0, 25, 0xffffffff};
	ui_make_string(rect, env->map_name, env->data);

	// display nb frames
	rect = (t_rect){1100, 20, 0, 20, 0xFFFFFFFF};
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
	ui_make_rect(env->data->surface, get_element(E_B_MODE_DRAW, env)->rect);
	ui_make_rect(env->data->surface, get_element(E_B_MODE_ELEM, env)->rect);
}
