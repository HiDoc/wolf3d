/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/08/29 12:37:50 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	*launch_thread(void *arg)
{
	t_thr	*tmp;

	//fonction de thread
	(void)arg;
	(void)tmp;
	pthread_exit(NULL);
}

void	set_thread(t_env *env)
{
	T_T1.env = env;
	T_T2.env = env;
	T_T3.env = env;
	T_T4.env = env;
	T_T1.nbr = 1;
	T_T2.nbr = 2;
	T_T3.nbr = 3;
	T_T4.nbr = 4;
}

int		init_thread(t_env *env)
{
	set_thread(env);
	if (pthread_create(&T_TH1, NULL, launch_thread, &T_T1))
		return (exit_wolf(env));
	if (pthread_create(&T_TH2, NULL, launch_thread, &T_T2))
		return (exit_wolf(env));
	if (pthread_create(&T_TH3, NULL, launch_thread, &T_T3))
		return (exit_wolf(env));
	if (pthread_create(&T_TH4, NULL, launch_thread, &T_T4))
		return (exit_wolf(env));
	if (pthread_join(T_TH1, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH2, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH3, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH4, NULL))
		return (exit_wolf(env));
	return (0);
}
