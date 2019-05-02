/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/02 16:15:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		display_object_data(t_env *env)
{
	char        *obj_tab[5] = {
	"Wall_object", "Consumable", "Entity", "Prefab", "Special"};
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, obj_tab[env->editor.obj_select->category], env->data);

	rect = (SDL_Rect){910, 140, 250, 30};
	ui_make_string(rect, env->editor.obj_select->name, env->data);

	rect = (SDL_Rect){910, 180, 250, 30};
	if (env->editor.obj_select->sct)
		ui_make_nbrstring(rect, env->editor.obj_select->sct->id, env->data);
	else
		ui_make_string(rect, "No sector", env->data);

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_sector_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "sector", env->data);

	rect = (SDL_Rect){1000, 110, 250, 30};
	ui_make_nbrstring(rect, env->editor.sct_select->id, env->data);
	
	display_labeled_input(E_I_SELEC_GRAVITY, "gravity", env);
	display_labeled_input(E_I_SELEC_HCEIL, "ceil height", env);
	display_labeled_input(E_I_SELEC_HFLOOR, "floor height", env);
	display_button(E_B_SELEC_CEIL, "CEIL", env);
	display_button(E_B_SELEC_SKY, "SKY", env);
	display_button(E_B_SELEC_CEILTX, "CEIL TEXTURE", env);
	display_button(E_B_SELEC_FLOORTX, "FLOOR TEXTURE", env);

	rect = (SDL_Rect){910, 510, 200, 190};
	if (get_element(E_B_SELEC_CEILTX, env)->clicked)
		display_editor_dropdown_list(rect, DD_CEILTX, env);
	else if (get_element(E_B_SELEC_FLOORTX, env)->clicked)
		display_editor_dropdown_list(rect, DD_FLOORTX, env);

	// up
	if ((SDL_BlitScaled(get_element(E_B_SELEC_TX_UP, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_TX_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display selection");
	// down
	if ((SDL_BlitScaled(get_element(E_B_SELEC_TX_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_TX_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display selection");

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_vertex_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "vertex", env->data);

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_edge_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "edge", env->data);

	// display buttons
	display_button(E_B_SELEC_FDOOR, "FINAL DOOR", env);
	display_button(E_B_SELEC_DOOR, "DOOR", env);
	display_button(E_B_SELEC_SPLIT, "SPLIT", env);

	rect = (SDL_Rect){910, 310, 250, 30};
	ui_make_string(rect, "Wall texture ", env->data);

	// display_size
	rect = (SDL_Rect){190, 750, 0, 20};
	ui_make_string(rect, "size : ", env->data);
	rect = (SDL_Rect){240, 750, 0, 20};
	ui_make_nbrstring(rect, env->editor.edg_select->size, env->data);

	// display modif wall txtr
	rect = (SDL_Rect){910, 350, 200, 350};
	display_editor_dropdown_list(rect, DD_MWALLTX, env);

	// up
	if ((SDL_BlitScaled(get_element(E_B_SELEC_M_WALL_UP, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_M_WALL_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display selection");
	 // down
	if ((SDL_BlitScaled(get_element(E_B_SELEC_M_WALL_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_M_WALL_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display selection");

	display_button(E_B_SELEC_DEL, "DELETE", env);
}

static void		display_misc_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "Misc", env->data);

	display_button(E_B_SELEC_MUSIC, "BACKGROUND MUSIC", env);
	display_button(E_B_SELEC_SBTX, "SKYBOX TEXTURE", env);

	// display skybox textures
	rect = (SDL_Rect){910, 250, 200, 400};
	if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
		display_editor_dropdown_list(rect, DD_SBTX, env);
	else if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
		display_editor_dropdown_list(rect, DD_BGAUDIO, env);

	// up
	if ((SDL_BlitScaled(get_element(E_B_SELEC_MISC_UP, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_MISC_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display selection");
	// down
	if ((SDL_BlitScaled(get_element(E_B_SELEC_MISC_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_MISC_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display selection");
}

void			display_selection(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){890, 100, 290, 680};
	ui_make_rect(env->data->surface, rect, C_WHITE);

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
