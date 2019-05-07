/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/07 20:33:22 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_env	env;

	init_env(ac, av, &env);
	set_msc_menu(&env, &env.menu.status);
	load_worlds(&env);
	mainmenu_loop(&env);
	while (env.curr_lvl < env.nb_levels)
	{
		env.finish = 0;
		mainmenu_loop(&env);
		env.menu.status.inter = 1;
		load_map(&env.engine, &env);
		init_minimap(&env);
		loop_intro(&env, env.curr_lvl);
		sdl_loop(&env);
		action_endlevel(&env, env.curr_lvl);
		free_map(&env);
		lt_release((void**)&env.engine.minimap.surface);
		lt_release((void**)&env.engine.minimap.background);
		env.curr_lvl++;
	}
	doom_exit();
	return (0);
}
