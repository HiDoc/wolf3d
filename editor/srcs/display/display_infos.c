/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:05:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:06:41 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_infos(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){30, 750, 0, 20};
	ui_make_string(rect, "x : ", C_WHITE, env->data);
	rect = (SDL_Rect){60, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.x, C_WHITE, env->data);
	rect = (SDL_Rect){110, 750, 0, 20};
	ui_make_string(rect, "y : ", C_WHITE, env->data);
	rect = (SDL_Rect){140, 750, 0, 20};
	ui_make_nbrstring(rect, env->mouse.y, C_WHITE, env->data);
	if (env->editor.sct_current)
	{
		rect = (SDL_Rect){190, 750, 0, 20};
		ui_make_string(rect, "size : ", C_WHITE, env->data);
		rect = (SDL_Rect){240, 750, 0, 20};
		ui_make_nbrstring(rect,
			env->editor.sct_current->w_vtx_current->size, C_WHITE, env->data);
	}
}
