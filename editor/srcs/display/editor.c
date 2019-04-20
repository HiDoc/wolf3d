/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 23:10:30 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		editor(t_env *env)
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
	rect = (SDL_Rect){30, 150, 0, 20};
	ui_make_string(rect, "Nb sectors : ", env->data);
	rect = (SDL_Rect){170, 150, 0, 20};
	ui_make_nbrstring(rect, env->nb_sct, env->data);
	rect = (SDL_Rect){30, 180, 0, 20};
	ui_make_string(rect, "Nb vertex : ", env->data);
	rect = (SDL_Rect){170, 180, 0, 20};
	ui_make_nbrstring(rect, env->nb_vtx, env->data);

	// display mouse mode buttons
	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_SELECT, env)->rect,
	get_element(E_B_MODE_SELECT, env)->color);
	if ((SDL_BlitScaled(get_element(E_B_MODE_SELECT, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_SELECT, env)->rect)) < 0)
		 ui_error_exit_sdl("Libui: Blit error on editor display");

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_MOVE, env)->rect,
	get_element(E_B_MODE_MOVE, env)->color);
	if ((SDL_BlitScaled(get_element(E_B_MODE_MOVE, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_MOVE, env)->rect)) < 0)
		 ui_error_exit_sdl("Libui: Blit error on editor display");

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_DRAW, env)->rect,
	get_element(E_B_MODE_DRAW, env)->color);
	if ((SDL_BlitScaled(get_element(E_B_MODE_DRAW, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_DRAW, env)->rect)) < 0)
		ui_error_exit_sdl("Libui: Blit error on editor display");

	ui_make_rect(env->data->surface,
	get_element(E_B_MODE_ELEM, env)->rect,
	get_element(E_B_MODE_ELEM, env)->color);
	if ((SDL_BlitScaled(get_element(E_B_MODE_ELEM, env)->image,
	0, env->data->surface, &get_element(E_B_MODE_ELEM, env)->rect)) < 0)
		ui_error_exit_sdl("Libui: Blit error on editor display");

	// display play
	ui_make_string(get_element(E_B_PLAY, env)->rect, "PLAY", env->data);
	ui_make_rect(env->data->surface, get_element(E_B_PLAY, env)->rect, C_WHITE);	
}
