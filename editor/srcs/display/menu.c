/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 23:10:04 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		menu_left_panel(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){WIN_W / 2 - 400, WIN_H / 2 - 225, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);
	display_labeled_input(M_I_NEW, "Create a map", env);
}

static void		menu_right_panel(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){WIN_W / 2, WIN_H / 2 - 225, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);
	rect = (SDL_Rect){WIN_W / 2 + 10, WIN_H / 2 - 215, 380, 350};
	ui_make_rect(env->data->surface, rect, C_WHITE);
	rect = (SDL_Rect){WIN_W / 2 + 20, WIN_H / 2 - 215, 380, 30};
	if (get_element(M_I_NEW, env)->str)
		ui_make_string(rect, get_element(M_I_NEW, env)->str,
		C_WHITE, env->data);
	else
		ui_make_string(rect, env->map_name, C_WHITE, env->data);
	display_button(M_B_START, "Start", env);
}

void			menu(t_env *env)
{
	SDL_Rect	rect;

	if ((SDL_BlitScaled(env->menu.background, 0, env->data->surface, 0)) < 0)
		ui_error_exit_sdl("Libui: Blit error in menu");
	rect = (SDL_Rect){WIN_W / 2 - 170, WIN_H / 2 - 275, 0, 35};
	ui_make_string(rect, "DOOM NUKEM EDITOR", C_WHITE, env->data);
	menu_left_panel(env);
	menu_right_panel(env);
	rect = (SDL_Rect){300, 20, 0, 20};
	ui_make_nbrstring(rect, env->data->nb_frames, C_WHITE, env->data);
}
