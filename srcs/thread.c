/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 14:50:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	*launch_thread(void *arg)
{
	t_thr	*tmp;

	tmp = (t_thr *)arg;
	tron(tmp->env, tmp->nbr);
	pthread_exit(NULL);
}

int		set_thread(t_env *env, int threads)
{
	int nbr;

	nbr = 0;
	while (nbr < threads && nbr < THREAD_NBR)
	{
		env->thr[nbr].env = env;
		env->thr[nbr].nbr = nbr + 1;
		nbr++;
	}
	return (0);
}

void	set_surface(t_env *env)
{
	SDL_FreeSurface(env->sdl.surface);
	env->sdl.surface = SDL_CreateRGBSurface(0, env->sdl.width, env->sdl.height, 32,
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000);
}

int		init_thread(t_env *env, int threads)
{
	int		x;

	x = set_thread(env, threads);
	set_surface(env);
	while (x < threads)
	{
		if (pthread_create(&env->thr[x].th, NULL, launch_thread, &env->thr[x]))
		{
			perror("Error");
			return (sdl_exit_wolf(env, SDL_SCANCODE_ESCAPE));
		}
		x++;
	}
	x = 0;
	while (x < threads)
	{
		if (pthread_join(env->thr[x].th, NULL))
		{
			perror("Error thread");
			return (sdl_exit_wolf(env, SDL_SCANCODE_ESCAPE));
		}
		x++;
	}
	put_health(env);
	return (0);
}
