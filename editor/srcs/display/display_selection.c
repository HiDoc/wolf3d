/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/29 14:39:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	char		*obj_tab[5] = {
	"Wall_object", "Consumable", "Entity", "Prefab", "Special"};
	SDL_Rect	rect;

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

	if (env->editor.obj_select)
	{
		rect = (SDL_Rect){890, 100, 290, 680};
		ui_make_rect(env->data->surface, rect, C_WHITE);
		
		rect = (SDL_Rect){910, 110, 250, 30};
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
		rect = (SDL_Rect){890, 100, 290, 680};
		ui_make_rect(env->data->surface, rect, C_WHITE);

		rect = (SDL_Rect){910, 110, 250, 30};
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

		get_element(E_B_SELEC_CEIL, env)->color = (
			env->editor.sct_select->roof == 0) ? C_GREEN : C_WHITE;
		ui_make_string(get_element(E_B_SELEC_CEIL, env)->rect,
			"CEIL", env->data);
		ui_make_input(env->data->surface,
		get_element(E_B_SELEC_CEIL, env), env->data);

		get_element(E_B_SELEC_SKY, env)->color = (
			env->editor.sct_select->roof == 1) ? C_GREEN : C_WHITE;
		ui_make_string(get_element(E_B_SELEC_SKY, env)->rect,
			"SKY", env->data);
		ui_make_input(env->data->surface,
		get_element(E_B_SELEC_SKY, env), env->data);
	}
	else if (env->editor.vtx_select)
	{
		rect = (SDL_Rect){890, 100, 290, 680};
		ui_make_rect(env->data->surface, rect, C_WHITE);

		rect = (SDL_Rect){910, 110, 250, 30};
		ui_make_string(rect, "vertex [id vertex]", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else if (env->editor.edg_select)
	{
		rect = (SDL_Rect){890, 100, 290, 680};
		ui_make_rect(env->data->surface, rect, C_WHITE);

		rect = (SDL_Rect){910, 110, 250, 30};
		ui_make_string(rect, "edge [id vertex]", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_FDOOR, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_FDOOR, env)->rect, "FINAL DOOR", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DOOR, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DOOR, env)->rect, "DOOR", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_SPLIT, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_SPLIT, env)->rect, "SPLIT", env->data);

		rect = (SDL_Rect){910, 310, 250, 30};
		ui_make_rect(env->data->surface, rect, C_WHITE);
		ui_make_string(rect, "Wall texture ", env->data);
		rect = (SDL_Rect){1100, 310, 250, 30};
		ui_make_nbrstring(rect, env->editor.edg_select->ref, env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_DEL, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_DEL, env)->rect, "DELETE", env->data);
	}
	else
	{
		rect = (SDL_Rect){890, 100, 290, 680};
		ui_make_rect(env->data->surface, rect, C_WHITE);

		rect = (SDL_Rect){910, 110, 250, 30};
		ui_make_string(rect, "Misc", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_MUSIC, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_MUSIC, env)->rect, "BACKGROUND MUSIC", env->data);

		ui_make_rect(env->data->surface,
		get_element(E_B_SELEC_SBTX, env)->rect, C_WHITE);
		ui_make_string(
		get_element(E_B_SELEC_SBTX, env)->rect, "SKYBOX TEXTURE", env->data);
	}
}
