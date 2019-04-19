/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/19 16:57:52 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_env	env;

	/* init env */
	init_env(ac, av, &env);

	/* load level */
	load_map(&env.engine, &env); // <- lifetime todo;

	/* load minimap */
	//init_minimap(&env); // <- lifetime todo
	!env.god_mod ? set_msc_menu(&env, &env.menu.status) : 0;
	/* gameloop */
	sdl_loop(&env);

	/* free and exit */
	doom_exit();
	return (0);
}
