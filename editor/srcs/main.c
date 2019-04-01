/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:13:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/01 14:14:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;
}

static void		create_element(int id, int type, t_rect rect, t_env *env)
{
	t_elem   *new;

	if (!(new = (t_elem *)ft_memalloc(sizeof(t_elem))))
		ui_error_exit_sdl("Editor: Out of memory", env->data);
	new->id = id;
	new->type = type;
	new->rect = rect;
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

static void		create_btn_obj(int id, int type, char *str, t_rect rect, t_env *env)
{
	t_elem   *new;

	if (!(new = (t_elem *)ft_memalloc(sizeof(t_elem))))
		ui_error_exit_sdl("Editor: create_btn_obj, out of memory", env->data);
	new->id = id;
	new->type = type;
	if (!(new->str = ft_strdup(str)))
		ui_error_exit_sdl("Editor: create_btn_obj, out of memory", env->data);
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

static void		init_elems(t_env *env)
{
	t_rect		rect;

	rect = (t_rect){WIN_W / 2 - 400 + 10, WIN_H / 2 - 225 + 40,
	300, 25, C_WHITE};
	create_element(M_I_NEW, INPUT, rect, env);

	rect = (t_rect){WIN_W / 2 - 400 + 410, WIN_H / 2 - 225 + 400,
	150, 25, C_WHITE};
	create_element(M_B_START, BUTTON, rect, env);

	rect = (t_rect){WIN_W / 2 - 400 + 610, WIN_H / 2 - 225 + 400,
	150, 25, C_WHITE};
	create_element(M_B_CANCEL, BUTTON, rect, env);

	rect = (t_rect){WIN_W / 2 - 400 + 610, WIN_H / 2 - 225 + 400,
	150, 25, C_WHITE};
	create_element(M_B_EXIT, BUTTON, rect, env);

	rect = (t_rect){20, 20, 100, 40, C_WHITE};
	create_element(E_B_NEW, BUTTON, rect, env);

	rect = (t_rect){130, 20, 125, 40, C_WHITE};
	create_element(E_B_UPLOAD, BUTTON, rect, env);

	rect = (t_rect){300, 20, 100, 40, C_WHITE};
	create_element(E_B_SAVE, BUTTON, rect, env);

	rect = (t_rect){WIN_W / 2 - 50, WIN_H / 2 + 20,
	20, 20, C_WHITE};
	create_element(M_B_UP, BUTTON, rect, env);
	
	rect = (t_rect){WIN_W / 2 - 50, WIN_H / 2 +	60,
	20, 20, C_WHITE};
	create_element(M_B_DOWN, BUTTON, rect, env);

	rect = (t_rect){600, 20, 40, 40, 0xFFFFFFFF};
	create_element(E_B_MODE_SELECT, BUTTON, rect, env);

	rect = (t_rect){650, 20, 40, 40, 0xffffffff};
	create_element(E_B_MODE_DRAW, BUTTON, rect, env);

	rect = (t_rect){700, 20, 40, 40, 0xffffffff};
	create_element(E_B_MODE_ELEM, BUTTON, rect, env);

	rect = (t_rect){850, 20, 150, 40, 0xffffffff};
	create_element(E_B_PLAY, BUTTON, rect, env);

	rect = (t_rect){1130, 350, 20, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_UP, BUTTON, rect, env);
	
	rect = (t_rect){1130, 380, 20, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_DOWN, BUTTON, rect, env);

	rect = (t_rect){900, 110, 270, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_OBWL, BUTTON, rect, env);

	rect = (t_rect){900, 140, 270, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_CONS, BUTTON, rect, env);

	rect = (t_rect){900, 170, 270, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_NTTY, BUTTON, rect, env);

	rect = (t_rect){900, 200, 270, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_PRFB, BUTTON, rect, env);

	rect = (t_rect){900, 230, 270, 20, 0xFFFFFFFF};
	create_element(E_B_ELM_SPEC, BUTTON, rect, env);
}

static void		init_objs(t_env *env)
{
	t_rect		rect;
	char		**stock;
	char		*line;
	int			fd;
	int			i;

	// wall_objects
	if ((fd = open("ressources/objects/wall_objects", O_RDONLY)) == -1)
		ui_error_exit_sdl("Editor: init_objs, bad fd", env->data);
	if ((get_next_line(fd, &line)) == -1)
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	if (!(stock = ft_strsplit(line, ' ')))
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	free(line);
	i = 0;
	while (stock[i])
	{
		rect = (t_rect){910, 330 + 40 * (i + env->editor.idx_wall_txtr), 200, 30, C_WHITE};
		create_btn_obj(i, WALL_OBJ, stock[i], rect, env);
		free(stock[i]);
		i++;	
	}
	free(stock);
	close(fd);
	// consumables
	if ((fd = open("ressources/objects/consumables", O_RDONLY)) == -1)
		ui_error_exit_sdl("Editor: init_objs, bad fd", env->data);
	if ((get_next_line(fd, &line)) == -1)
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	if (!(stock = ft_strsplit(line, ' ')))
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	free(line);
	i = 0;
	while (stock[i])
	{
		rect = (t_rect){910, 330 + 40 * (i + env->editor.idx_wall_txtr), 200, 30, C_WHITE};
		create_btn_obj(i, CONSUMABLE, stock[i], rect, env);
		free(stock[i]);
		i++;	
	}
	free(stock);
	close(fd);
	// entities
	if ((fd = open("ressources/objects/entities", O_RDONLY)) == -1)
		ui_error_exit_sdl("Editor: init_objs, bad fd", env->data);
	if ((get_next_line(fd, &line)) == -1)
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	if (!(stock = ft_strsplit(line, ' ')))
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	free(line);
	i = 0;
	while (stock[i])
	{
		rect = (t_rect){910, 330 + 40 * (i + env->editor.idx_wall_txtr), 200, 30, C_WHITE};
		create_btn_obj(i, ENTITY, stock[i], rect, env);
		free(stock[i]);
		i++;	
	}
	free(stock);
	close(fd);
	// prefabs
	if ((fd = open("ressources/objects/prefabs", O_RDONLY)) == -1)
		ui_error_exit_sdl("Editor: init_objs, bad fd", env->data);
	if ((get_next_line(fd, &line)) == -1)
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	if (!(stock = ft_strsplit(line, ' ')))
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	free(line);
	i = 0;
	while (stock[i])
	{
		rect = (t_rect){910, 330 + 40 * (i + env->editor.idx_wall_txtr), 200, 30, C_WHITE};
		create_btn_obj(i, PREFAB, stock[i], rect, env);
		free(stock[i]);
		i++;	
	}
	free(stock);
	close(fd);
	// specials
	if ((fd = open("ressources/objects/specials", O_RDONLY)) == -1)
		ui_error_exit_sdl("Editor: init_objs, bad fd", env->data);
	if ((get_next_line(fd, &line)) == -1)
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	if (!(stock = ft_strsplit(line, ' ')))
		ui_error_exit_sdl("Editor: init_objs, out of memory", env->data);
	free(line);
	i = 0;
	while (stock[i])
	{
		rect = (t_rect){910, 330 + 40 * (i + env->editor.idx_wall_txtr), 200, 30, C_WHITE};
		create_btn_obj(i, SPECIAL, stock[i], rect, env);
		free(stock[i]);
		i++;	
	}
	free(stock);
	close(fd);
}

static void		init_menu(t_env *env)
{
	t_data				*data = env->data;
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	// compteur de nb de maps
	if (!(dr = opendir("maps/")))
		ui_error_exit_sdl("Editor: Unable to open maps/", data);
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
			env->menu.nb_maps++;
	}
	closedir(dr);

	// stockage des maps name
	if (!(env->menu.maps = (char **)ft_memalloc(sizeof(char *)
					* (env->menu.nb_maps + 1))))
		ui_error_exit_sdl("Libui: Out of memory", data);

	if (!(dr = opendir("maps/")))
		ui_error_exit_sdl("Editor: Unable to open maps/", data);
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			if (!(env->menu.maps[i] = ft_strdup(de->d_name)))
				ui_error_exit_sdl("Editor: Out of memory", data);
			i++;
		}
	}
	closedir(dr);
}

static void		init_editor(t_env *env)
{
	t_data				*data = env->data;
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	// compteur nb wall textures
	if (!(dr = opendir("ressources/images/wall/")))
		ui_error_exit_sdl("Editor: Unable to open ressources/images/wall/", data);
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
			env->editor.nb_wall_txtr++;
	}
	closedir(dr);

	// stockage des wall textures
	if (!(env->editor.wall_txtr = (char **)ft_memalloc(sizeof(char *)
	* (env->editor.nb_wall_txtr + 1))))
		ui_error_exit_sdl("Libui: Out of memory", data);

	if (!(dr = opendir("ressources/images/wall/")))
		ui_error_exit_sdl("Editor: Unable to open ressources/images/wall/", data);
	while ((de = readdir(dr)))
	{
		if ((de->d_name)[0] != '.')
		{
			if (!(env->editor.wall_txtr[i] = ft_strdup(de->d_name)))
				ui_error_exit_sdl("Editor: Out of memory", data);
			i++;
		}
	}
	closedir(dr);
}

int				main(void)
{
	t_data		data;
	t_env		env;

	ui_init_sdl(&data);

	init_env(&env, &data);
	init_elems(&env);
	init_objs(&env);
	init_editor(&env);
	init_menu(&env);
	env.menu.state = 1;
	env.menu.background = ui_load_image(
	"ressources/images/doom-background.jpg", &env);

	if (!(env.map_name = ft_strdup("new_map")))
		ui_error_exit_sdl("Editor: out of memory", &data);

	ui_make_window("EDITOR", &data);
	ui_load_font("ressources/fonts/Arial.ttf", &data);

	ui_gameloop(&handle_events, &editor, &env);

	return (0);
}
