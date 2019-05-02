/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/02 14:55:34 by sgalasso         ###   ########.fr       */
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

	rect = get_element(E_B_SELEC_DEL, env)->rect;
	ui_make_rect(env->data->surface, rect, C_RED);
	ui_make_string(rect, "DELETE", env->data);
}

static void		display_sector_data(t_env *env)
{
	Uint32			color;
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "sector", env->data);

	rect = (SDL_Rect){1000, 110, 250, 30};
	ui_make_nbrstring(rect, env->editor.sct_select->id, env->data);

	rect = (SDL_Rect){910, 145, 250, 30};
	ui_make_string(rect, "gravity", env->data);
	ui_make_input(env->data->surface,
	get_element(E_I_SELEC_GRAVITY, env), env->data);

	rect = (SDL_Rect){910, 215, 250, 30};
	ui_make_string(rect, "ceil height", env->data);
	ui_make_input(env->data->surface,
	get_element(E_I_SELEC_HCEIL, env), env->data);

	rect = (SDL_Rect){910, 285, 250, 30};
	ui_make_string(rect, "floor height", env->data);
	ui_make_input(env->data->surface,
	get_element(E_I_SELEC_HFLOOR, env), env->data);

	rect = get_element(E_B_SELEC_CEIL, env)->rect;
	color = (env->editor.sct_select->roof) ? C_WHITE : C_GREEN;
	ui_make_string(rect, "CEIL", env->data);
	ui_make_rect(env->data->surface, rect, color);

	rect = get_element(E_B_SELEC_SKY, env)->rect;
	color = (env->editor.sct_select->roof) ? C_GREEN : C_WHITE;
	ui_make_string(rect, "SKY", env->data);
	ui_make_rect(env->data->surface, rect, color);

	rect = get_element(E_B_SELEC_CEILTX, env)->rect;
	color = (get_element(E_B_SELEC_CEILTX, env)->clicked) ? C_GREEN : C_WHITE;
	ui_make_string(rect, "CEIL TEXTURE", env->data);
	ui_make_rect(env->data->surface, rect, color);

	rect = get_element(E_B_SELEC_FLOORTX, env)->rect;
	color = (get_element(E_B_SELEC_FLOORTX, env)->clicked) ? C_GREEN : C_WHITE;
	ui_make_string(rect, "FLOOR TEXTURE", env->data);
	ui_make_rect(env->data->surface, rect, color);

	rect = (SDL_Rect){910, 510, 200, 190};
	if (get_element(E_B_SELEC_CEILTX, env)->clicked)
	{
		// display skybox textures
		display_editor_dropdown_list(rect, DD_CEILTX, env);
	}
	else if (get_element(E_B_SELEC_FLOORTX, env)->clicked)
	{
		// display background audio
		display_editor_dropdown_list(rect, DD_FLOORTX, env);
	}

	// up
	if ((SDL_BlitScaled(get_element(E_B_SELEC_TX_UP, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_TX_UP, env)->rect)))
		ui_error_exit_sdl("Editor: blit error in display selection");
	// down
	if ((SDL_BlitScaled(get_element(E_B_SELEC_TX_DOWN, env)->image,
	0, env->data->surface, &get_element(E_B_SELEC_TX_DOWN, env)->rect)) < 0)
		ui_error_exit_sdl("Editor: blit error in display selection");

	rect = get_element(E_B_SELEC_DEL, env)->rect;
	ui_make_rect(env->data->surface, rect, C_RED);
	ui_make_string(rect, "DELETE", env->data);
}

static void		display_vertex_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "vertex", env->data);

	rect = get_element(E_B_SELEC_DEL, env)->rect;
	ui_make_rect(env->data->surface, rect, C_RED);
	ui_make_string(rect, "DELETE", env->data);
}

static void		display_edge_data(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "edge", env->data);

	rect = get_element(E_B_SELEC_FDOOR, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "FINAL DOOR", env->data);

	rect = get_element(E_B_SELEC_DOOR, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "DOOR", env->data);

	rect = get_element(E_B_SELEC_SPLIT, env)->rect;
	ui_make_rect(env->data->surface, rect, C_WHITE);
	ui_make_string(rect, "SPLIT", env->data);

	rect = (SDL_Rect){910, 310, 250, 30};
	ui_make_string(rect, "Wall texture ", env->data);

	// display_size
	rect = (SDL_Rect){190, 750, 0, 20};
	ui_make_string(rect, "size : ", env->data);
	rect = (SDL_Rect){240, 750, 0, 20};
	ui_make_nbrstring(rect, env->editor.edg_select->size,
		env->data);

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

	rect =  get_element(E_B_SELEC_DEL, env)->rect;
	ui_make_rect(env->data->surface, rect, C_RED);
	ui_make_string(rect, "DELETE", env->data);
}

static void		display_misc_data(t_env *env)
{
	Uint32			color;
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 110, 250, 30};
	ui_make_string(rect, "Misc", env->data);

	rect = get_element(E_B_SELEC_MUSIC, env)->rect;
	color = (get_element(E_B_SELEC_MUSIC, env)->clicked) ? C_GREEN : C_WHITE;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "BACKGROUND MUSIC", env->data);

	rect = get_element(E_B_SELEC_SBTX, env)->rect;
	color = (get_element(E_B_SELEC_SBTX, env)->clicked) ? C_GREEN : C_WHITE;
	ui_make_rect(env->data->surface, rect, color);
	ui_make_string(rect, "SKYBOX TEXTURE", env->data);

	// display skybox textures
	if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
	{
		rect = (SDL_Rect){910, 250, 200, 400};
		display_editor_dropdown_list(rect, DD_SBTX, env);
	}
	else if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
	{
		// display background audio
		rect = (SDL_Rect){910, 250, 200, 400};
		display_editor_dropdown_list(rect, DD_BGAUDIO, env);
	}

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
