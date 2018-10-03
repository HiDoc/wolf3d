/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 16:40:32 by fmadura          ###   ########.fr       */
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

void	set_surface(t_env *env)
{
	env->sdl.surface = SDL_CreateRGBSurface(0, 800, 600, 32,
			0x00FF0000,
			0x0000FF00,
			0x000000FF,
			0xFF000000);
}

int		init_thread(t_env *env)
{
	int		x;

	x = 0;
	set_thread(env, x);
	set_surface(env);
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
<<<<<<< HEAD
=======
	put_health(env);
>>>>>>> 617158c1a15a0aa3a2bc20c89fe9a7f8c8ca4120
	return (0);
}
