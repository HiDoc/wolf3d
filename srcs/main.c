/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/05 12:11:30 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(int ac, char **av)
{
	t_env			env;

	/* Initialisation */
	ft_bzero(&env, sizeof(t_env));
	if (ac > 1)
		env.god_mod = ft_strcmp(av[1], "god") == 0 ? 1 : 0;
	initialisation(&env);

	/* Load data from map */
	ft_bzero(&env.engine, sizeof(t_engine));
	load_map(&env.engine, &env);

	/* Loop */
	sdl_loop(&env);

	/* Free and exit */
	free_env(&env);
	return (0);
}
