/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 14:05:17 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		editor(t_env *env)
{
	SDL_Cursor*		cursor;
	SDL_Rect		rect;

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
	ui_make_rect(env->data->surface,
	get_element(E_B_MENU, env)->rect, get_element(E_B_MENU, env)->color);
	ui_make_string(get_element(E_B_MENU, env)->rect, "MENU", env->data);
	// display save
	ui_make_rect(env->data->surface,
	get_element(E_B_SAVE, env)->rect, get_element(E_B_SAVE, env)->color);
	ui_make_string(get_element(E_B_SAVE, env)->rect, "SAVE", env->data);

	// display map name
	rect = (SDL_Rect){20, 65, 0, 25};
	ui_make_string(rect, env->map_name, env->data);

	// display nb frames
	rect = (SDL_Rect){300, 20, 0, 20};
	ui_make_nbrstring(rect, env->data->nb_frames, env->data);

	// display nb element
	rect = (SDL_Rect){900, 600, 0, 20};
	ui_make_string(rect, "Nb sectors : ", env->data);
	rect = (SDL_Rect){1040, 600, 0, 20};
	ui_make_nbrstring(rect, env->nb_sct, env->data);
	/*rect = (t_rect){900, 630, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb edges : ", env->data);
	rect = (t_rect){1040, 630, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->edg_index + 1, env->data);*/
	rect = (SDL_Rect){900, 660, 0, 20};
	ui_make_string(rect, "Nb vertex : ", env->data);
	rect = (SDL_Rect){1040, 660, 0, 20};
	ui_make_nbrstring(rect, env->nb_vtx, env->data);

	// display mouse mode buttons
	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_SELECT, env)->rect, C_WHITE);
	SDL_BlitScaled(get_element(E_B_MODE_SELECT, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_SELECT, env)->rect);

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_MOVE, env)->rect, C_WHITE);
	SDL_BlitScaled(get_element(E_B_MODE_MOVE, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_MOVE, env)->rect);

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_DRAW, env)->rect, C_WHITE);
	SDL_BlitScaled(get_element(E_B_MODE_DRAW, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_DRAW, env)->rect);

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_ELEM, env)->rect, C_WHITE);
	SDL_BlitScaled(get_element(E_B_MODE_ELEM, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_ELEM, env)->rect);

	// display play
	ui_make_string(get_element(E_B_PLAY, env)->rect, "PLAY", env->data);
	ui_make_rect(env->data->surface, get_element(E_B_PLAY, env)->rect, C_WHITE);	
}
