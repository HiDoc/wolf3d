/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:13:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 13:22:08 by sgalasso         ###   ########.fr       */
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
		env->elements->next = new;
		new->next = 0;
	}
}

static void		init_elems(t_env *env)
{
	t_rect		rect;

	rect = (t_rect){WIN_W / 2 - 400 + 10, WIN_H / 2 - 225 + 40,
	300, 25, C_WHITE};
	create_element(MENU_INPUT_NEW, INPUT, rect, env);

	rect = (t_rect){WIN_W / 2 - 400 + 410, WIN_H / 2 - 225 + 400,
	150, 25, C_WHITE};
	create_element(MENU_BUTTON_START, BUTTON, rect, env);
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

int				main(void)
{
	t_data		data;
	t_env		env;

	ui_init_sdl(&data);

	init_env(&env, &data);
	init_elems(&env);
	init_menu(&env);
	env.menu.state = 1;
	env.menu.background = ui_load_image(
			"ressources/images/doom-background.jpg", &env);

	env.map_name = "map"; // to remove

	ui_make_window("EDITOR", &data);
	ui_load_font("ressources/fonts/Arial.ttf", &data);

	ui_gameloop(&handle_events, &editor, &env);

	return (0);
}
