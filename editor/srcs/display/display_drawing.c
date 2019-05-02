/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:36:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/02 16:17:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void        display_drawing(t_env *env)
{
	SDL_Rect	rect;

	// display area rect
	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display title
	rect = (SDL_Rect){910, 110, 0, 20};
	ui_make_string(rect, "Wall texture", env->data);

	// up
	if ((SDL_BlitScaled(get_element(E_B_DRW_UP, env)->image,
	0, env->data->surface, &get_element(E_B_DRW_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display drawing");
	// down
	if ((SDL_BlitScaled(get_element(E_B_DRW_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_DRW_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display drawing");

	// display preview
	rect = (SDL_Rect){910, 150, 250, 150};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	// display wall textures
	rect = (SDL_Rect){910, 320, 200, 400};
	display_editor_dropdown_list(rect, DD_WALLTX, env);
}
