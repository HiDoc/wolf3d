/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 16:35:17 by fmadura          ###   ########.fr       */
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
	return (1);
}

void	set_surface(t_env *env)
{
		SDL_Surface *surface;

		surface = env->sdl.surface;
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
    SDL_UnlockSurface(surface);
}

int		init_thread(t_env *env, int threads)
{
	int		x;

	x = 0;
	while (x < threads)
	{
		if (pthread_create(&env->thr[x].th, NULL, launch_thread, &env->thr[x]))
		{
			perror("Error");
			return (sdl_exit_wolf(env));
		}
		x++;
	}
	x = 0;
	while (x < threads)
	{
		if (pthread_join(env->thr[x].th, NULL))
		{
			perror("Error thread");
			return (sdl_exit_wolf(env));
		}
		x++;
	}
	return (0);
}
