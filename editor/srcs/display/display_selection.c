/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 19:37:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	char		*obj_tab[5] = {
	"Wall_object", "Consumable", "Entity", "Prefab", "Special"};
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
		ui_make_string(rect, obj_tab[env->obj_select->category], env->data);
		rect = (SDL_Rect){910, 140, 250, 30};
		ui_make_string(rect, env->obj_select->name, env->data);
		rect = (SDL_Rect){910, 180, 250, 30};
		ui_make_nbrstring(rect, env->obj_select->dir, env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else if (env->sct_select)
	{
		ui_make_string(rect, "sector", env->data);
		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		rect = (SDL_Rect){1000, 110, 250, 30};
		ui_make_nbrstring(rect, env->sct_select->id, env->data);

		rect = (SDL_Rect){910, 145, 250, 30};
		ui_make_string(rect, "gravity", env->data);
		ui_make_input(env->data->surface,
		get_element(E_I_SELEC_GRAVITY, env), env->data);

		rect = (SDL_Rect){910, 215, 250, 30};
		ui_make_string(rect, "height", env->data);
		ui_make_input(env->data->surface,
		get_element(E_I_SELEC_HEIGHT, env), env->data);

		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else if (env->vtx_select)
	{
		ui_make_string(rect, "vertex [id vertex]", env->data);
	}
}
