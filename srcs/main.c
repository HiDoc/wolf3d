/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 14:59:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_env	env;

	/* init env */
	init_env(ac, av, &env);

	/* load level */
	load_map(&env.engine, &env); // <- lifetime todo

	/* load minimap */
	//init_minimap(&env); // <- lifetime todo

	/* gameloop */
	sdl_loop(&env); // <- lifetime todo

	/* free and exit */
	doom_exit();
	return (0);
}
