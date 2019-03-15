/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:13:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 16:25:09 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;
}

static void		init_menu(t_env *env, t_data *data)
{
	struct dirent		*de;
	DIR					*dr;
	int					i;

	i = 0;
	// compteur de nb de maps
	if (!(dr = opendir("maps/")))
		ui_error_exit_sdl("Editor: Unable to open maps/", env->data);
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
	env.draw_cursor = ui_load_image(
	"ressources/images/pen_cursor.png", &env);
	init_menu(&env, &data);
	env.menu.state = 1;
	env.menu.background = ui_load_image(
	"ressources/images/doom-background.jpg", &env);

	env.map_name = "map"; // to remove

	ui_make_window("EDITOR", &data);
	ui_load_font("ressources/fonts/Arial.ttf", &data);

	ui_gameloop(&handle_events, &editor, &env);

	return (0);
}
