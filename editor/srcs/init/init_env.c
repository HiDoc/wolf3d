/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:24:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 18:36:20 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		create_element(int id, int type, SDL_Rect rect, t_env *env)
{
	t_elem   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->id = id;
	new->type = type;
	new->rect = rect;
	new->color = C_WHITE;
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

static void		init_elems(t_env *env)
{
	SDL_Rect		rect;

	// menu
	rect = (SDL_Rect){WIN_W / 2 - 390, WIN_H / 2 - 225 + 40, 300, 25};
	create_element(M_I_NEW, INPUT, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 400 + 410, WIN_H / 2 - 225 + 400, 150, 25};
	create_element(M_B_START, BUTTON, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 400 + 610, WIN_H / 2 - 225 + 400, 150, 25};
	create_element(M_B_CANCEL, BUTTON, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 60, WIN_H / 2 + 5, 40, 40};
	create_element(M_B_UP, BUTTON, rect, env);
	get_element(M_B_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){WIN_W / 2 - 60, WIN_H / 2 + 55, 40, 40};
	create_element(M_B_DOWN, BUTTON, rect, env);
	get_element(M_B_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");

	// editor
	rect = (SDL_Rect){20, 100, 850, 680};
	create_element(E_R_RECT, RECT, rect, env);

	rect = (SDL_Rect){20, 20, 125, 40};
	create_element(E_B_MENU, BUTTON, rect, env);

	rect = (SDL_Rect){170, 20, 100, 40};
	create_element(E_B_SAVE, BUTTON, rect, env);

	rect = (SDL_Rect){600, 20, 50, 50};
	create_element(E_B_MODE_SELECT, BUTTON, rect, env);
	get_element(E_B_MODE_SELECT, env)->color = C_GREEN;
	get_element(E_B_MODE_SELECT, env)->image =
		ui_load_image("ressources/images/icons/cursor.png");

	rect = (SDL_Rect){650, 20, 50, 50};
	create_element(E_B_MODE_MOVE, BUTTON, rect, env);
	get_element(E_B_MODE_MOVE, env)->image =
		ui_load_image("ressources/images/icons/move.png");

	rect = (SDL_Rect){700, 20, 50, 50};
	create_element(E_B_MODE_DRAW, BUTTON, rect, env);
	get_element(E_B_MODE_DRAW, env)->image =
		ui_load_image("ressources/images/icons/line.png");

	rect = (SDL_Rect){750, 20, 50, 50};
	create_element(E_B_MODE_ELEM, BUTTON, rect, env);
	get_element(E_B_MODE_ELEM, env)->image =
		ui_load_image("ressources/images/icons/object.png");

	rect = (SDL_Rect){1030, 20, 150, 40};
	create_element(E_B_PLAY, BUTTON, rect, env);

	// editor drawing
	rect = (SDL_Rect){1130, 350, 20, 20};
	create_element(E_B_DRW_UP, BUTTON, rect, env);
	get_element(E_B_DRW_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){1130, 380, 20, 20};
	create_element(E_B_DRW_DOWN, BUTTON, rect, env);
	get_element(E_B_DRW_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");

	// editor element
	rect = (SDL_Rect){1130, 350, 20, 20};
	create_element(E_B_ELM_UP, BUTTON, rect, env);
	get_element(E_B_ELM_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){1130, 380, 20, 20};
	create_element(E_B_ELM_DOWN, BUTTON, rect, env);
	get_element(E_B_ELM_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");

	rect = (SDL_Rect){900, 110, 270, 20};
	create_element(E_B_ELM_OBWL, BUTTON, rect, env);
	env->editor.curr_elem_btn = get_element(E_B_ELM_OBWL, env);
	env->editor.curr_elem_dd = DD_WOBJ;
	env->editor.curr_elem_btn->clicked = 1;;

	rect = (SDL_Rect){900, 140, 270, 20};
	create_element(E_B_ELM_CONS, BUTTON, rect, env);

	rect = (SDL_Rect){900, 170, 270, 20};
	create_element(E_B_ELM_NTTY, BUTTON, rect, env);

	rect = (SDL_Rect){900, 200, 270, 20};
	create_element(E_B_ELM_PRFB, BUTTON, rect, env);

	rect = (SDL_Rect){900, 230, 270, 20};
	create_element(E_B_ELM_SPEC, BUTTON, rect, env);

	// editor selection
	rect = (SDL_Rect){910, 720, 250, 30};
	create_element(E_B_SELEC_DEL, BUTTON, rect, env);
	get_element(E_B_SELEC_DEL, env)->color = C_RED;

	// editor selection edge
	rect = (SDL_Rect){910, 150, 250, 30};
	create_element(E_B_SELEC_SPLIT, BUTTON, rect, env);

	rect = (SDL_Rect){1130, 540, 20, 20};
	create_element(E_B_SELEC_M_WALL_UP, BUTTON, rect, env);
	get_element(E_B_SELEC_M_WALL_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){1130, 570, 20, 20};
	create_element(E_B_SELEC_M_WALL_DOWN, BUTTON, rect, env);
	get_element(E_B_SELEC_M_WALL_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");

	// editor selection sector
	rect = (SDL_Rect){910, 370, 120, 25};
	create_element(E_I_SELEC_HFLOOR, INPUT, rect, env);
	get_element(E_I_SELEC_HFLOOR, env)->event_fc = click_sct_hfloor;
	rect = (SDL_Rect){1040, 370, 120, 25};
	create_element(E_I_SELEC_HCEIL, INPUT, rect, env);
	get_element(E_I_SELEC_HCEIL, env)->event_fc = click_sct_hceil;

	rect = (SDL_Rect){910, 150, 250, 25};
	create_element(E_B_SELEC_NORMAL, BUTTON, rect, env);
	get_element(E_B_SELEC_NORMAL, env)->event_fc = click_sct_normal;
	rect = (SDL_Rect){910, 190, 80, 25};
	create_element(E_B_SELEC_DOOR, BUTTON, rect, env);
	get_element(E_B_SELEC_DOOR, env)->event_fc = click_sct_door;
	rect = (SDL_Rect){1010, 190, 150, 25};
	create_element(E_B_SELEC_FDOOR, BUTTON, rect, env);
	get_element(E_B_SELEC_FDOOR, env)->event_fc = click_sct_fdoor;

	rect = (SDL_Rect){910, 230, 110, 25};
	create_element(E_B_SELEC_CEIL, BUTTON, rect, env);
	get_element(E_B_SELEC_CEIL, env)->clicked = 1;
	get_element(E_B_SELEC_CEIL, env)->event_fc = click_sct_ceil;
	rect = (SDL_Rect){1040, 230, 120, 25};
	create_element(E_B_SELEC_SKY, BUTTON, rect, env);
	get_element(E_B_SELEC_SKY, env)->event_fc = click_sct_sky;

	rect = (SDL_Rect){910, 300, 250, 25};
	create_element(E_I_SELEC_GRAVITY, INPUT, rect, env);
	get_element(E_I_SELEC_GRAVITY, env)->event_fc = click_sct_gravity;
	
	rect = (SDL_Rect){910, 420, 250, 25};
	create_element(E_B_SELEC_CEILTX, BUTTON, rect, env);
	get_element(E_B_SELEC_CEILTX, env)->clicked = 1;
	get_element(E_B_SELEC_CEILTX, env)->event_fc = click_sct_ceiltx;
	rect = (SDL_Rect){910, 460, 250, 25};
	create_element(E_B_SELEC_FLOORTX, BUTTON, rect, env);
	get_element(E_B_SELEC_FLOORTX, env)->event_fc = click_sct_floortx;

	rect = (SDL_Rect){1130, 540, 20, 20};
	create_element(E_B_SELEC_TX_UP, BUTTON, rect, env);
	get_element(E_B_SELEC_TX_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");
	get_element(E_B_SELEC_TX_UP, env)->event_fc = click_sct_txup;
	rect = (SDL_Rect){1130, 570, 20, 20};
	create_element(E_B_SELEC_TX_DOWN, BUTTON, rect, env);
	get_element(E_B_SELEC_TX_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");
	get_element(E_B_SELEC_TX_DOWN, env)->event_fc = click_sct_txdown;

	// editor selection misc
	rect = (SDL_Rect){910, 150, 250, 25};
	create_element(E_B_SELEC_MUSIC, BUTTON, rect, env);
	get_element(E_B_SELEC_MUSIC, env)->clicked = 1;

	rect = (SDL_Rect){910, 190, 250, 25};
	create_element(E_B_SELEC_SBTX, BUTTON, rect, env);

	rect = (SDL_Rect){1130, 270, 20, 20};
	create_element(E_B_SELEC_MISC_UP, BUTTON, rect, env);
	get_element(E_B_SELEC_MISC_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){1130, 300, 20, 20};
	create_element(E_B_SELEC_MISC_DOWN, BUTTON, rect, env);
	get_element(E_B_SELEC_MISC_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");
}

/*
**	Return nb of loaded objects
*/

static void		create_btn_map(char *str, t_env *env)
{
	t_elem   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_map, out of memory");
	if (!(new->str = lt_push(ft_strdup(str), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_map, out of memory");
	if (!(env->menu.dropdown.start))
	{
		env->menu.dropdown.start = new;
		env->menu.dropdown.start->next = 0;
	}
	else
	{
		new->next = env->menu.dropdown.start;
		env->menu.dropdown.start = new;
	}
}

static void		init_menu(t_env *env)
{
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	if (!(dr = lt_push(opendir("maps/"), dir_del)))
		ui_error_exit_sdl("Editor: Unable to open maps/");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			create_btn_map(de->d_name, env);
			env->menu.dropdown.nb_element++;
			i++;
		}
	}
	lt_release((void**)&dr);

	env->map_name = "new_map";
	env->menu.state = 1;
	env->menu.background = ui_load_image("ressources/images/doom-background.jpg");
}

static void		create_dd_button(int id, int dd, int ref, char *str, t_env *env)
{
	t_elem   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: create_dd_button, out of memory");
	if (!(new->str = lt_push(ft_strdup(str), ft_memdel)))
		ui_error_exit_sdl("Editor: create_dd_button, out of memory");
	new->ref = ref;
	new->id = id;
	new->dd = dd;
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

static void		load_dd_list(char *path, int dd, t_env *env)
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
			create_dd_button(i, dd, ref, name, env);
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
	lt_release((void **)&dr);
}

static void		init_editor(t_env *env)
{
	load_dd_list("ressources/images/walls/", DD_WALLTX, env);
	load_dd_list("ressources/images/walls/", DD_MWALLTX, env);
	load_dd_list("ressources/skybox/", DD_SBTX, env);
	load_dd_list("ressources/ambiance/", DD_BGAUDIO, env);
	load_dd_list("ressources/images/ceil/", DD_CEILTX, env);
	load_dd_list("ressources/images/floors/", DD_FLOORTX, env);
	load_dd_list("ressources/objects/posters", DD_WOBJ, env);
	load_dd_list("ressources/objects/consumable", DD_CONS, env);
	load_dd_list("ressources/objects/enemies", DD_NTTY, env);
	load_dd_list("ressources/objects/prefabs", DD_PRFB, env);
	load_dd_list("ressources/objects/specials", DD_SPEC, env);

	env->grid_scale = 5;
}

void		init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;

	init_elems(env);
	init_menu(env);
	init_editor(env);

	ui_load_font("ressources/fonts/Arial.ttf", data);

	ui_make_window("EDITOR", data);
}
