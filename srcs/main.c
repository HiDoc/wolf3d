/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 10:44:59 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main2(int ac, char **av)
{
	t_env	env;

	/* init env */
	init_env(ac, av, &env); // <- lifetime

	/* load level */
	load_map(&env.engine, &env);

	/* load minimap */
	//init_minimap(&env);

	/* gameloop */
	sdl_loop(&env);

	/* free and exit */
	doom_exit();
	return (0);
}

int		main(int ac, char **av)
{
	main2(ac, av);
	//while (1);
	return (0);
}
