/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 00:26:33 by sgalasso         ###   ########.fr       */
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
	if (env->editor.obj_hover)
		ui_make_string(rect, "object", env->data);
	else if (env->editor.sct_hover)
		ui_make_string(rect, "sector", env->data);
	else if (env->editor.vtx_hover)
		ui_make_string(rect, "vertex", env->data);
	else if (env->editor.edg_hover)
		ui_make_string(rect, "edge", env->data);

	//dislay selected
	rect = (SDL_Rect){910, 110, 250, 30};
	if (env->editor.obj_select)
	{
		ui_make_string(rect, obj_tab[env->editor.obj_select->category], env->data);
		rect = (SDL_Rect){910, 140, 250, 30};
		ui_make_string(rect, env->editor.obj_select->name, env->data);
		rect = (SDL_Rect){910, 180, 250, 30};
		ui_make_nbrstring(rect, env->editor.obj_select->dir, env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else if (env->editor.sct_select)
	{
		ui_make_string(rect, "sector", env->data);
		rect = (SDL_Rect){1000, 110, 250, 30};
		ui_make_nbrstring(rect, env->editor.sct_select->id, env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);

		rect = (SDL_Rect){910, 145, 250, 30};
		ui_make_string(rect, "gravity", env->data);
		ui_make_input(env->data->surface,
		get_element(E_I_SELEC_GRAVITY, env), env->data);

		rect = (SDL_Rect){910, 215, 250, 30};
		ui_make_string(rect, "height", env->data);
		ui_make_input(env->data->surface,
		get_element(E_I_SELEC_HEIGHT, env), env->data);
	}
	else if (env->editor.vtx_select)
	{
		ui_make_string(rect, "vertex [id vertex]", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else if (env->editor.edg_select)
	{
		ui_make_string(rect, "edge [id vertex]", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_SPLIT, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_SPLIT, env)->rect, "SPLIT", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
}
