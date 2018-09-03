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

	tmp = (t_thr *)arg;
	wolf(tmp->env, tmp->nbr);
	pthread_exit(NULL);
}

void	set_thread(t_env *env)
{
	T_T1.env = env;
	T_T2.env = env;
	T_T3.env = env;
	T_T4.env = env;	
	T_T5.env = env;
	T_T6.env = env;
	T_T7.env = env;
	T_T8.env = env;
	T_T1.nbr = 1;
	T_T2.nbr = 2;
	T_T3.nbr = 3;
	T_T4.nbr = 4;	
	T_T5.nbr = 5;
	T_T6.nbr = 6;
	T_T7.nbr = 7;
	T_T8.nbr = 8;
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
	if (pthread_create(&T_TH5, NULL, launch_thread, &T_T5))
		return (exit_wolf(env));
	if (pthread_create(&T_TH6, NULL, launch_thread, &T_T6))
		return (exit_wolf(env));
	if (pthread_create(&T_TH7, NULL, launch_thread, &T_T7))
		return (exit_wolf(env));
	if (pthread_create(&T_TH8, NULL, launch_thread, &T_T8))
		return (exit_wolf(env));
	if (pthread_join(T_TH1, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH2, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH3, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH4, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH5, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH6, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH7, NULL))
		return (exit_wolf(env));
	if (pthread_join(T_TH8, NULL))
		return (exit_wolf(env));
	return (0);
}
