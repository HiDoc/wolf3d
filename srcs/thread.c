/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 14:15:25 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	*launch_thread(void *arg)
{
	t_thr	*tmp;

	tmp = (t_thr *)arg;
	wolf(tmp->env, tmp->nbr);
	pthread_exit(NULL);
}

void	set_thread(t_env *env, int nbr)
{
	while (nbr < 8)
	{
		env->thr[nbr].env = env;
		env->thr[nbr].nbr = nbr + 1;
		nbr++;
	}
}

int		init_thread(t_env *env)
{
	int		x;

	x = 0;
	set_thread(env, x);
	while (x < 8)
	{	
		if (pthread_create(&env->thr[x].th, NULL, launch_thread, &env->thr[x]))
		{
			perror("");
			return (sdl_exit_wolf(env, SDL_SCANCODE_ESCAPE));
		}
		x++;
	}
	x = 0;
	while (x < 8)
	{	
		if (pthread_join(env->thr[x].th, NULL))
		{
			perror("");
			return (sdl_exit_wolf(env, SDL_SCANCODE_ESCAPE));
		}
		x++;
	}
	put_gun(env);
	put_health(env);
	return (0);
}
