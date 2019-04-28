/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 19:01:58 by sgalasso         ###   ########.fr       */
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
	int iprovisoire = 0;
	while (/**env.level*/iprovisoire < 5)
	{
		env.finish = 0;

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

		/*(env.level)++;*/
		iprovisoire++;
	}

	/* free and exit */
	doom_exit();
	return (0);
}
