/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:24:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 22:50:05 by sgalasso         ###   ########.fr       */
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

static void		create_btn_obj(int id, int ref, int type, char *str, SDL_Rect rect, t_env *env)
{
	t_elem   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_obj, out of memory");
	new->id = id;
	new->ref = ref;
	new->type = type;
	if (!(new->str = lt_push(ft_strdup(str), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_obj, out of memory");
	new->rect = rect;
	if (!(env->btn_objs))
	{
		env->btn_objs = new;
		env->btn_objs->next = 0;
	}
	else
	{
		new->next = env->btn_objs;
		env->btn_objs = new;
	}
}

static void		create_btn_map(char *str, SDL_Rect rect, t_env *env)
{
	t_elem   *new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_elem)), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_map, out of memory");
	// ...
	if (!(new->str = lt_push(ft_strdup(str), ft_memdel)))
		ui_error_exit_sdl("Editor: create_btn_map, out of memory");
	new->rect = rect;
	if (!(env->menu.btn_maps))
	{
		env->menu.btn_maps = new;
		env->menu.btn_maps->next = 0;
	}
	else
	{
		new->next = env->menu.btn_maps;
		env->menu.btn_maps = new;
	}
}

static void		init_elems(t_env *env)
{
	SDL_Rect		rect;

	rect = (SDL_Rect){WIN_W / 2 - 390, WIN_H / 2 - 225 + 40, 300, 25};
	create_element(M_I_NEW, INPUT, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 400 + 410, WIN_H / 2 - 225 + 400, 150, 25};
	create_element(M_B_START, BUTTON, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 400 + 610, WIN_H / 2 - 225 + 400, 150, 25};
	create_element(M_B_CANCEL, BUTTON, rect, env);

	rect = (SDL_Rect){20, 20, 125, 40};
	create_element(E_B_MENU, BUTTON, rect, env);

	rect = (SDL_Rect){170, 20, 100, 40};
	create_element(E_B_SAVE, BUTTON, rect, env);

	rect = (SDL_Rect){WIN_W / 2 - 60, WIN_H / 2 + 5, 40, 40};
	create_element(M_B_UP, BUTTON, rect, env);
	get_element(M_B_UP, env)->image =
		ui_load_image("ressources/images/icons/arrowup.png");

	rect = (SDL_Rect){WIN_W / 2 - 60, WIN_H / 2 + 55, 40, 40};
	create_element(M_B_DOWN, BUTTON, rect, env);
	get_element(M_B_DOWN, env)->image =
		ui_load_image("ressources/images/icons/arrowdown.png");

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

	rect = (SDL_Rect){1130, 350, 20, 20};
	create_element(E_B_ELM_UP, BUTTON, rect, env);

	rect = (SDL_Rect){1130, 380, 20, 20};
	create_element(E_B_ELM_DOWN, BUTTON, rect, env);

	rect = (SDL_Rect){900, 110, 270, 20};
	create_element(E_B_ELM_OBWL, BUTTON, rect, env);

	rect = (SDL_Rect){900, 140, 270, 20};
	create_element(E_B_ELM_CONS, BUTTON, rect, env);

	rect = (SDL_Rect){900, 170, 270, 20};
	create_element(E_B_ELM_NTTY, BUTTON, rect, env);

	rect = (SDL_Rect){900, 200, 270, 20};
	create_element(E_B_ELM_PRFB, BUTTON, rect, env);

	rect = (SDL_Rect){900, 230, 270, 20};
	create_element(E_B_ELM_SPEC, BUTTON, rect, env);

	rect = (SDL_Rect){910, 300, 250, 30};
	create_element(E_B_SELEC_DEL, BUTTON, rect, env);

	rect = (SDL_Rect){910, 250, 250, 30};
	create_element(E_I_SELEC_HEIGHT, INPUT, rect, env);

	rect = (SDL_Rect){910, 180, 250, 30};
	create_element(E_I_SELEC_GRAVITY, INPUT, rect, env);
}

static void		load_obj(char *path, int type, t_env *env)
{
	SDL_Rect	rect;
	struct dirent       *de;
	DIR                 *dr;
	char				*name;
	int					ref;
	int					i;

	i = 0;
	if (!(dr = lt_push(opendir(path), dir_del)))
		ui_error_exit_sdl("Editor: Unable to open ressources");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.' && ft_strchr(de->d_name, '+'))
		{
			rect = (SDL_Rect){910, 330 + 40 * (i /*+ var arrow */), 200, 30};
			name = ft_strncpy(name, de->d_name, ft_strchri(de->d_name, '+'));
			ref = ft_atoi(ft_strchr(de->d_name, '+'));
			create_btn_obj(i, ref, type, name, rect, env);
			i++;
		}
	}
	lt_release(dr);
}

static void		load_specials(int type, t_env *env)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){910, 330, 200, 30};
	create_btn_obj(0, 0, type, "Spawn", rect, env);
	rect = (SDL_Rect){910, 330 + 40, 200, 30};
	create_btn_obj(1, 0, type, "Interest", rect, env);
}

static void		init_objs(t_env *env)
{
	// wall_objects
	load_obj("ressources/objects/wall_objects", WALL_OBJ, env);
	// consumables
	load_obj("ressources/objects/consumables", CONSUMABLE, env);
	// entities
	load_obj("ressources/objects/entities", ENTITY, env);
	// specials
	load_specials(SPECIAL, env);
}

static void		init_menu(t_env *env)
{
	SDL_Rect			rect;
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	// compteur de nb de maps
	if (!(dr = lt_push(opendir("maps/"), dir_del)))
		ui_error_exit_sdl("Editor: Unable to open maps/");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			rect = (SDL_Rect){220, 310 + (40 * i), 300, 25};
			env->menu.nb_maps++;
			create_btn_map(de->d_name, rect, env);
			i++;
		}
	}
	lt_release(dr);
	env->map_name = "new_map";
	env->menu.state = 1;
	env->menu.background = ui_load_image("ressources/images/doom-background.jpg");
}

static void		init_editor(t_env *env)
{
	struct dirent		*de;
	DIR					*dr;
	int					i;

	//env->grid_translate = (t_pos){-(870 * 2), -(780 * 2)};
	//env->pixel_value = 5;

	env->grid_translate = (t_pos){0, 0};
	env->pixel_value = 5;

	i = 0;
	// compteur nb wall textures
	if (!(dr = lt_push(opendir("ressources/images/wall/"), dir_del)))
		ui_error_exit_sdl("Editor: Unable to open ressources/images/wall/");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
			env->editor.nb_wall_txtr++;
	}
	lt_release(dr);

	// stockage des wall textures
	if (!(env->editor.wall_txtr = lt_push(
	ft_memalloc(sizeof(char *) * (env->editor.nb_wall_txtr + 1)), ft_memdel)))
		ui_error_exit_sdl("Libui: Out of memory");

	if (!(dr = lt_push(opendir("ressources/images/wall/"), dir_del)))
		ui_error_exit_sdl("Editor: Unable to open ressources/images/wall/");
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			if (!(env->editor.wall_txtr[i] =
			lt_push(ft_strdup(de->d_name), ft_memdel)))
				ui_error_exit_sdl("Editor: Out of memory");
			i++;
		}
	}
	lt_release(dr);
}

void		init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;
	init_elems(env);
	init_objs(env);
	init_menu(env);
	init_editor(env);
	ui_make_window("EDITOR", data);
	ui_load_font("ressources/fonts/Arial.ttf", data);
}
