/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 00:04:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main2(int ac, char **av)
{
	t_env	env;

	// Init env
	init_env(ac, av, &env);

	// load level
	load_map(&env.engine, &env);
	//init_minimap(&env);

	// Gameloop
	sdl_loop(&env);

	// Free and exit
	doom_exit();
	return (0);
}

int		main(int ac, char **av)
{
	main2(ac, av);
	//while (1);
	return (0);
}
