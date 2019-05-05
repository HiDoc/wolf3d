/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 15:30:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_object_data(t_env *env)
{
	SDL_Rect		rect;
	char			*category;

	if (env->editor.obj_select->dd == DD_WOBJ)
		category = "Wall_object";
	else if (env->editor.obj_select->dd == DD_CONS)
		category = "Consumable";
	else if (env->editor.obj_select->dd == DD_NTTY)
		category = "Entity";
	else if (env->editor.obj_select->dd == DD_PRFB)
		category = "Prefab";
	else if (env->editor.obj_select->dd == DD_SPEC)
		category = "Special";
	else
		category = 0;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, category, C_WHITE, env->data);

	rect = (SDL_Rect){910, 140, 250, 30};
	ui_make_string(rect, env->editor.obj_select->name, C_WHITE, env->data);

	rect = (SDL_Rect){910, 180, 250, 30};
	if (env->editor.obj_select->sct)
		ui_make_nbrstring(rect, env->editor.obj_select->sct->id, C_WHITE, env->data);
	else
		ui_make_string(rect, "No sector", C_WHITE, env->data);

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_sector_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "sector", C_WHITE, env->data);

	rect = (SDL_Rect){1000, 110, 250, 30};
	ui_make_nbrstring(rect, env->editor.sct_select->id, C_WHITE, env->data);

	display_button(E_B_SELEC_NORMAL, "NORMAL", env);
	display_button(E_B_SELEC_DOOR, "DOOR", env);
	display_button(E_B_SELEC_FDOOR, "FINAL DOOR", env);

	display_labeled_input(E_I_SELEC_GRAVITY, "gravity", env);
	display_labeled_input(E_I_SELEC_HCEIL, "ceil height", env);
	display_labeled_input(E_I_SELEC_HFLOOR, "floor height", env);

	display_button(E_B_SELEC_CEIL, "CEIL", env);
	display_button(E_B_SELEC_SKY, "SKY", env);

	/*env->editor.dropdown[DD_CEILTX].current->clicked = 0;
	env->editor.dropdown[DD_CEILTX].current
		= get_element_by_ref(env->editor.sct_select->ceil, DD_CEILTX, env);
	env->editor.dropdown[DD_CEILTX].current->clicked = 1;*/
	display_button(E_B_SELEC_CEILTX, "CEIL TEXTURE", env);
	display_button(E_B_SELEC_FLOORTX, "FLOOR TEXTURE", env);

	rect = (SDL_Rect){910, 510, 200, 190};
	if (get_element(E_B_SELEC_CEILTX, env)->clicked)
		display_editor_dropdown_list(rect, DD_CEILTX, env);
	else if (get_element(E_B_SELEC_FLOORTX, env)->clicked)
		display_editor_dropdown_list(rect, DD_FLOORTX, env);

	display_updown(E_B_SELEC_TX_UP, E_B_SELEC_TX_DOWN, env);

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_vertex_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "vertex", C_WHITE, env->data);

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_edge_data(t_env *env)
{
	SDL_Rect		rect;

	// title
	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "edge", C_WHITE, env->data);

	// display buttons
	display_button(E_B_SELEC_SPLIT, "SPLIT", env);

	// dropdown title
	rect = (SDL_Rect){910, 210, 250, 30};
	ui_make_string(rect, "Wall texture ", C_WHITE, env->data);

	// dropdown mwalltx
	env->editor.dropdown[DD_MWALLTX].current->clicked = 0;
	env->editor.dropdown[DD_MWALLTX].current
		= get_dd_element(env->editor.edg_select->ref, DD_MWALLTX, env);
	env->editor.dropdown[DD_MWALLTX].current->clicked = 1;
	rect = (SDL_Rect){910, 250, 200, 420};
	display_editor_dropdown_list(rect, DD_MWALLTX, env);
	display_updown(E_B_SELEC_M_WALL_UP, E_B_SELEC_M_WALL_DOWN, env);

	// delete
	display_button(E_B_SELEC_DEL, "DELETE", env);

	/* TO SET IN INTERFACE */
	// display interface size
	rect = (SDL_Rect){190, 750, 0, 20};
	ui_make_string(rect, "size : ", C_WHITE, env->data);
	rect = (SDL_Rect){240, 750, 0, 20};
	ui_make_nbrstring(rect, env->editor.edg_select->size, C_WHITE, env->data);
}

static void		display_misc_data(t_env *env)
{
	SDL_Rect		rect;

	// title
	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "Misc", C_WHITE, env->data);
	// buttons
	display_button(E_B_SELEC_MUSIC, "BACKGROUND MUSIC", env);
	display_button(E_B_SELEC_SBTX, "SKYBOX TEXTURE", env);

	// dropdown skybox / textures
	rect = (SDL_Rect){910, 250, 200, 400};
	(get_element(E_B_SELEC_SBTX, env)->clicked)
	? display_editor_dropdown_list(rect, DD_SBTX, env)
	: display_editor_dropdown_list(rect, DD_BGAUDIO, env);
	display_updown(E_B_SELEC_MISC_UP, E_B_SELEC_MISC_DOWN, env);
}

void			display_selection(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

	rect = (SDL_Rect){env->data->mouse.x, env->data->mouse.y - 40, 250, 30};
	if (env->editor.obj_hover)
		ui_make_string(rect, "object", C_WHITE, env->data);
	else if (env->editor.sct_hover)
		ui_make_string(rect, "sector", C_WHITE, env->data);
	else if (env->editor.vtx_hover)
		ui_make_string(rect, "vertex", C_WHITE, env->data);
	else if (env->editor.edg_hover)
		ui_make_string(rect, "edge", C_WHITE, env->data);

	if (env->editor.obj_select)
		display_object_data(env);
	else if (env->editor.sct_select)
		display_sector_data(env);
	else if (env->editor.vtx_select)
		display_vertex_data(env);
	else if (env->editor.edg_select)
		display_edge_data(env);
	else
		display_misc_data(env);
}
