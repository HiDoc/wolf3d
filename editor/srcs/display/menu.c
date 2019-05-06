/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 13:46:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	left_panel(t_pos origin, t_env *env)
{
	SDL_Rect	rect;

	// square
	rect = (SDL_Rect){origin.x, origin.y, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// create new
	display_labeled_input(M_I_NEW, "Create a map", env);
}

static void	right_panel(t_pos origin, t_env *env)
{
	SDL_Rect		rect;

	// square
	rect = (SDL_Rect){origin.x + 400, origin.y, 400, 450};
	ui_make_full_rect(env->data->surface, rect, 0x10000000);
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// preview
	rect = (SDL_Rect){origin.x + 410, origin.y + 10, 380, 350};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// current map
	rect = (SDL_Rect){origin.x + 420, origin.y + 10, 380, 30};
	if (get_element(M_I_NEW, env)->str)
		ui_make_string(rect, get_element(M_I_NEW, env)->str, C_WHITE, env->data);
	else
		ui_make_string(rect, env->map_name, C_WHITE, env->data);

	// start button
	display_button(M_B_START, "Start", env);

	// Cancel button
	if (env->menu.state == 2)
		display_button(M_B_CANCEL, "Cancel", env);
}

void		menu(t_env *env)
{
	SDL_Rect	rect;
	t_pos		origin;

	origin.x = WIN_W / 2 - 400;
	origin.y = WIN_H / 2 - 225;

	// display background
	rect = (SDL_Rect){0, 0, WIN_W, WIN_H};
	if ((SDL_BlitScaled(env->menu.background, 0, env->data->surface, &rect)) < 0)
		ui_error_exit_sdl("Libui: Blit error in menu");

	// display popup
	rect = (SDL_Rect){origin.x + 230, origin.y - 50, 0, 35};
	ui_make_string(rect, "DOOM NUKEM EDITOR", C_WHITE, env->data);

	// display left
	left_panel(origin, env);

	// display right
	right_panel(origin, env);

	// display nb frames
	rect = (SDL_Rect){300, 20, 0, 20};
	ui_make_nbrstring(rect, env->data->nb_frames, C_WHITE, env->data);
}
