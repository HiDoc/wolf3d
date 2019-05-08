/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:36:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_mode_btn(t_elem *elem, t_env *env)
{
	elem->color = (elem->clicked) ? C_GREEN : C_WHITE;
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
	display_grid(env);
	display_interface(env);
	display_infos(env);
	(env->editor.display_fc) ? env->editor.display_fc(env) : 0;
	display_button(E_B_SAVE, "SAVE", env);
	rect = (SDL_Rect){20, 65, 0, 25};
	ui_make_string(rect, env->map_name, C_WHITE, env->data);
	rect = (SDL_Rect){30, 120, 0, 20};
	if (env->editor.error_msg)
	{
		(time(0) - env->editor.timestamp < 4)
		? ui_make_string(rect, env->editor.error_msg, C_RED, env->data)
		: lt_release((void**)&env->editor.error_msg);
	}
	display_mode_btn(get_element(E_B_MODE_SELECT, env), env);
	display_mode_btn(get_element(E_B_MODE_MOVE, env), env);
	display_mode_btn(get_element(E_B_MODE_DRAW, env), env);
	display_mode_btn(get_element(E_B_MODE_ELEM, env), env);
}
