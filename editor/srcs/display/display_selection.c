/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/11 17:30:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	SDL_Rect	rect;

	// display selection area
	rect = (SDL_Rect){890, 100, 290, 250};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	//dislay hover infos
	rect = (SDL_Rect){env->data->mouse.x, env->data->mouse.y - 40, 250, 30};
	if (env->obj_hover)
		ui_make_string(rect, "object", env->data);
	else if (env->sct_hover)
		ui_make_string(rect, "sector", env->data);
	else if (env->vtx_hover)
		ui_make_string(rect, "vertex", env->data);

	//dislay selected
	rect = (SDL_Rect){910, 110, 250, 30};
	if (env->obj_select)
	{
		ui_make_string(rect, "object [id object]", env->data);
		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
		//rect = (SDL_Rect){1000, 110, 250, 30};
		//ui_make_nbrstring(rect, env->sct_select->id, env->data);
	}
	else if (env->sct_select)
	{
		ui_make_string(rect, "sector", env->data);
		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
		rect = (SDL_Rect){910, 220, 250, 30};
		ui_make_string(rect, "height", env->data);
		ui_make_input(env->data->surface,
		get_element(E_I_SELEC_HEIGHT, env), env->data);
		rect = (SDL_Rect){1000, 110, 250, 30};
		ui_make_nbrstring(rect, env->sct_select->id, env->data);
	}
	else if (env->vtx_select)
	{
		ui_make_string(rect, "vertex [id vertex]", env->data);
		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
		//rect = (SDL_Rect){930, 110, 250, 30};
		//ui_make_nbrstring(rect, env->sct_select->id, env->data);

	}
}
