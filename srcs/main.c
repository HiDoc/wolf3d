/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/29 17:27:13 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(void)
{
	t_env			env;

	/* Initialisation */
	ft_bzero(&env, sizeof(t_env));
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
