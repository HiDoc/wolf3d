/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:24:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:52:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		create_element(int id, int page, SDL_Rect rect, t_env *env)
{
	t_elem		*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->id = id;
	new->rect = rect;
	new->color = C_WHITE;
	new->page = page;
	if (!(env->elements))
	{
		env->elements = new;
		env->elements->next = 0;
	}
	else
	{
		new->next = env->elements;
		env->elements = new;
	}
}

static void		init_menu_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){WIN_W / 2 - 390, WIN_H / 2 - 225 + 40, 300, 25};
	create_element(M_I_NEW, MENU, rect, env);
	rect = (SDL_Rect){WIN_W / 2 - 400 + 410, WIN_H / 2 - 225 + 400, 150, 25};
	create_element(M_B_START, MENU, rect, env);
}

static void		init_editor_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){20, 100, 850, 680};
	create_element(E_R_RECT, EDITOR, rect, env);
	rect = (SDL_Rect){20, 20, 100, 40};
	create_element(E_B_SAVE, EDITOR, rect, env);
	rect = (SDL_Rect){600, 20, 50, 50};
	create_element(E_B_MODE_SELECT, EDITOR, rect, env);
	get_element(E_B_MODE_SELECT, env)->clicked = 1;
	get_element(E_B_MODE_SELECT, env)->image =
		ui_load_image("ressources/images/icons/cursor.png");
	rect = (SDL_Rect){650, 20, 50, 50};
	create_element(E_B_MODE_MOVE, EDITOR, rect, env);
	get_element(E_B_MODE_MOVE, env)->image =
		ui_load_image("ressources/images/icons/move.png");
	rect = (SDL_Rect){700, 20, 50, 50};
	create_element(E_B_MODE_DRAW, EDITOR, rect, env);
	get_element(E_B_MODE_DRAW, env)->image =
		ui_load_image("ressources/images/icons/line.png");
	rect = (SDL_Rect){750, 20, 50, 50};
	create_element(E_B_MODE_ELEM, EDITOR, rect, env);
	get_element(E_B_MODE_ELEM, env)->image =
		ui_load_image("ressources/images/icons/object.png");
}

static void		init_draw_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){1130, 350, 20, 20};
	create_element(E_B_DRW_UP, DRAW, rect, env);
	get_element(E_B_DRW_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");
	rect = (SDL_Rect){1130, 380, 20, 20};
	create_element(E_B_DRW_DOWN, DRAW, rect, env);
	get_element(E_B_DRW_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");
}

static void		init_elm_elems(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){1130, 350, 20, 20};
	create_element(E_B_ELM_UP, ELEM, rect, env);
	get_element(E_B_ELM_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");
	rect = (SDL_Rect){1130, 380, 20, 20};
	create_element(E_B_ELM_DOWN, ELEM, rect, env);
	get_element(E_B_ELM_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");
	rect = (SDL_Rect){900, 110, 270, 20};
	create_element(E_B_ELM_OBWL, ELEM, rect, env);
	env->editor.curr_elem_btn = get_element(E_B_ELM_OBWL, env);
	env->editor.curr_elem_dd = DD_WOBJ;
	env->editor.curr_elem_btn->clicked = 1;
	rect = (SDL_Rect){900, 140, 270, 20};
	create_element(E_B_ELM_CONS, ELEM, rect, env);
	rect = (SDL_Rect){900, 170, 270, 20};
	create_element(E_B_ELM_NTTY, ELEM, rect, env);
	rect = (SDL_Rect){900, 200, 270, 20};
	create_element(E_B_ELM_PRFB, ELEM, rect, env);
	rect = (SDL_Rect){900, 230, 270, 20};
	create_element(E_B_ELM_SPEC, ELEM, rect, env);
}

static void		init_slc_edg_elems(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){910, 150, 250, 30};
	create_element(E_B_SELEC_SPLIT, S_EDG, rect, env);
	get_element(E_B_SELEC_SPLIT, env)->event_fc = click_edg_split;
	rect = (SDL_Rect){910, 720, 250, 30};
	create_element(E_B_SELEC_EDG_DEL, S_EDG, rect, env);
	get_element(E_B_SELEC_EDG_DEL, env)->color = C_RED;
	get_element(E_B_SELEC_EDG_DEL, env)->event_fc = click_edg_del;
}

static void		init_slc_sct_elems2(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){910, 230, 110, 25};
	create_element(E_B_SELEC_CEIL, S_SCT, rect, env);
	get_element(E_B_SELEC_CEIL, env)->clicked = 1;
	get_element(E_B_SELEC_CEIL, env)->event_fc = click_sct_ceil;
	rect = (SDL_Rect){1040, 230, 120, 25};
	create_element(E_B_SELEC_SKY, S_SCT, rect, env);
	get_element(E_B_SELEC_SKY, env)->event_fc = click_sct_sky;
	rect = (SDL_Rect){910, 300, 250, 25};
	create_element(E_I_SELEC_GRAVITY, S_SCT, rect, env);
	get_element(E_I_SELEC_GRAVITY, env)->event_fc = click_sct_gravity;
	rect = (SDL_Rect){910, 720, 250, 30};
	create_element(E_B_SELEC_SCT_DEL, S_SCT, rect, env);
	get_element(E_B_SELEC_SCT_DEL, env)->color = C_RED;
	get_element(E_B_SELEC_SCT_DEL, env)->event_fc = click_sct_del;
}

static void		init_slc_sct_elems(t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){910, 370, 120, 25};
	create_element(E_I_SELEC_HFLOOR, S_SCT, rect, env);
	get_element(E_I_SELEC_HFLOOR, env)->event_fc = click_sct_hfloor;
	rect = (SDL_Rect){1040, 370, 120, 25};
	create_element(E_I_SELEC_HCEIL, S_SCT, rect, env);
	get_element(E_I_SELEC_HCEIL, env)->event_fc = click_sct_hceil;
	rect = (SDL_Rect){910, 150, 250, 25};
	create_element(E_B_SELEC_NORMAL, S_SCT, rect, env);
	get_element(E_B_SELEC_NORMAL, env)->event_fc = click_sct_normal;
	rect = (SDL_Rect){910, 190, 80, 25};
	create_element(E_B_SELEC_DOOR, S_SCT, rect, env);
	get_element(E_B_SELEC_DOOR, env)->event_fc = click_sct_door;
	rect = (SDL_Rect){1010, 190, 150, 25};
	create_element(E_B_SELEC_FDOOR, S_SCT, rect, env);
	get_element(E_B_SELEC_FDOOR, env)->event_fc = click_sct_fdoor;
	init_slc_sct_elems2(env);
}

static void		init_slc_vtx_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 720, 250, 30};
	create_element(E_B_SELEC_VTX_DEL, S_VTX, rect, env);
	get_element(E_B_SELEC_VTX_DEL, env)->color = C_RED;
	get_element(E_B_SELEC_VTX_DEL, env)->event_fc = click_vtx_del;
}

static void		init_slc_obj_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 720, 250, 30};
	create_element(E_B_SELEC_OBJ_DEL, S_OBJ, rect, env);
	get_element(E_B_SELEC_OBJ_DEL, env)->color = C_RED;
	get_element(E_B_SELEC_OBJ_DEL, env)->event_fc = click_obj_del;
}

static void		init_slc_msc_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){910, 150, 250, 25};
	create_element(E_B_SELEC_MUSIC, S_MSC, rect, env);
	get_element(E_B_SELEC_MUSIC, env)->clicked = 1;
	get_element(E_B_SELEC_MUSIC, env)->event_fc = click_msc_music;
	rect = (SDL_Rect){910, 190, 250, 25};
	create_element(E_B_SELEC_SBTX, S_MSC, rect, env);
	get_element(E_B_SELEC_SBTX, env)->event_fc = click_msc_sbtx;
	rect = (SDL_Rect){1130, 270, 20, 20};
	create_element(E_B_SELEC_MISC_UP, S_MSC, rect, env);
	get_element(E_B_SELEC_MISC_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");
	get_element(E_B_SELEC_MISC_UP, env)->event_fc = click_msc_miscup;
	rect = (SDL_Rect){1130, 300, 20, 20};
	create_element(E_B_SELEC_MISC_DOWN, S_MSC, rect, env);
	get_element(E_B_SELEC_MISC_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");
	get_element(E_B_SELEC_MISC_DOWN, env)->event_fc = click_msc_miscdown;
}

static void		init_menu(t_env *env)
{
	env->map_name = "new_map";
	env->menu.state = 1;
	env->menu.background =
		ui_load_image("ressources/images/doom-background.jpg");
}

static void		create_dd_button(int id, int dd,
		int ref, char *str, void (*event_fc)(t_env *), t_env *env)
{
	t_elem		*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: create_dd_button, out of memory");
	if (!(new->str = lt_push(ft_strdup(str), ft_memdel)))
		ui_error_exit_sdl("Editor: create_dd_button, out of memory");
	new->ref = ref;
	new->id = id;
	new->dd = dd;
	new->event_fc = event_fc;
	if (!(env->editor.dropdown[dd].start))
	{
		env->editor.dropdown[dd].start = new;
		env->editor.dropdown[dd].start->next = 0;
	}
	else
	{
		new->next = env->editor.dropdown[dd].start;
		env->editor.dropdown[dd].start = new;
	}
}

static void		load_dd_list(char *path, int dd,
		void (*event_fc)(t_env *), t_env *env)
{
	char				*name;
	char				*str;
	int					ref;
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	if (!(dr = lt_push(opendir(path), dir_del)))
		ui_error_exit_sdl("Editor: Load_dd_list, unable to open path");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			if (!(name = lt_push(ft_strsub(
			de->d_name, 0, ft_strchri(de->d_name, '+')), ft_memdel)))
				ui_error_exit_sdl("Editor: Out of memory in load_dd_list");
			ref = ft_atoi(ft_strchr(de->d_name, '+'));
			create_dd_button(i, dd, ref, name, event_fc, env);
			if (dd == DD_BGAUDIO)
			{
				if (!(str = lt_push(ft_strjoin(path, de->d_name), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory in load_dd_list");
				if (!(env->editor.dropdown[dd].start->audio =
							lt_push(Mix_LoadMUS(str), msc_del)))
					ui_error_exit_sdl("Editor error on Mix_LoadMUS");
				lt_release((void**)&str);
			}
			lt_release((void**)&name);
			env->editor.dropdown[dd].nb_element++;
			i++;
		}
	}
	if (env->editor.dropdown[dd].start)
	{
		env->editor.dropdown[dd].current = env->editor.dropdown[dd].start;
		env->editor.dropdown[dd].current->clicked = 1;
	}
	lt_release((void**)&dr);
}

static void		init_editor(t_env *env)
{
	load_dd_list("ressources/images/walls/", DD_WALLTX, 0, env);
	load_dd_list("ressources/skybox/", DD_SBTX, click_msc_sbtx_btn, env);
	load_dd_list("ressources/ambiance/", DD_BGAUDIO, click_msc_music_btn, env);
	load_dd_list("ressources/objects/posters", DD_WOBJ, 0, env);
	load_dd_list("ressources/objects/consumable", DD_CONS, 0, env);
	load_dd_list("ressources/objects/enemies", DD_NTTY, 0, env);
	load_dd_list("ressources/objects/prefabs", DD_PRFB, 0, env);
	load_dd_list("ressources/objects/specials", DD_SPEC, 0, env);
	env->editor.grid_scale = 5;
	env->editor.mode = select_mode;
	env->editor.display_fc = display_selection;
}

void			init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;
	init_menu_elems(env);
	init_editor_elems(env);
	init_draw_elems(env);
	init_elm_elems(env);
	init_slc_edg_elems(env);
	init_slc_sct_elems(env);
	init_slc_vtx_elems(env);
	init_slc_obj_elems(env);
	init_slc_msc_elems(env);
	init_menu(env);
	init_editor(env);
	ui_load_font("ressources/fonts/Arial.ttf", data);
	ui_make_window("EDITOR", data);
}
