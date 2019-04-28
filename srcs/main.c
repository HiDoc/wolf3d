/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 18:45:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_env	env;

	/* init env */
	init_env(ac, av, &env);
	set_msc_menu(&env, &env.menu.status);
	load_worlds(&env);

	/* mainmenu loop */
	mainmenu_loop(&env);

	/* world loop */
	while (env.curr_lvl < env.nb_levels)
	{
		env.finish = 0;
		env.menu.status.inter = 1;

		// display text start
		loop_intro(&env, env.curr_lvl);

		/* load level */
		load_map(&env.engine, &env);
		init_minimap(&env);

		/* gameloop */
		if (sdl_loop(&env))
			return (0);

		/* free level */
		free_map(&env);
		lt_release(env.engine.minimap.surface);
		lt_release(env.engine.minimap.background);

		env.curr_lvl++;
	}

	/* free and exit */
	doom_exit();
	return (0);
}
