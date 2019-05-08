/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:36:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:36:31 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_drawing(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);
	rect = (SDL_Rect){910, 110, 0, 20};
	ui_make_string(rect, "Wall texture", C_WHITE, env->data);
	display_updown(E_B_DRW_UP, E_B_DRW_DOWN, env);
	rect = (SDL_Rect){910, 150, 250, 150};
	ui_make_rect(env->data->surface, rect, C_WHITE);
	rect = (SDL_Rect){910, 320, 200, 400};
	display_editor_dropdown_list(rect, DD_WALLTX, env);
}
