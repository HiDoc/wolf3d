/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 15:58:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	SDL_Rect	rect;

	// display selection area
	rect = (SDL_Rect){890, 100, 290, 250};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	//dislay hovered
	rect = (SDL_Rect){910, 120, 250, 30};
	if (env->obj_hover)
		ui_make_string(rect, "object", env->data);
	else if (env->sct_hover)
		ui_make_string(rect, "sector", env->data);
	else if (env->vtx_hover)
		ui_make_string(rect, "vertex", env->data);

	//dislay selected
	rect = (SDL_Rect){910, 150, 250, 30};
	if (env->obj_hover)
		ui_make_string(rect, "selected : object", env->data);
	else if (env->sct_hover)
		ui_make_string(rect, "selected : sector", env->data);
	else if (env->vtx_hover)
		ui_make_string(rect, "selected : vertex", env->data);
}
