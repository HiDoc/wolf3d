/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:13:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/07 21:22:22 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	init_env(t_env *env, t_data *data)
{
	ft_bzero(env, sizeof(t_env));
	env->data = data;
}

int		main(void)
{
	t_data		data;
	t_env		env;

	ui_init_sdl(&data);
	init_env(&env, &data);

	env.map_name = "map"; // to remove

	ui_make_window("EDITOR", &data);
	ui_load_font("ressources/fonts/Arial.ttf", &data);

	ui_gameloop(&handle_events, &editor, &env);

	return (0);
}
