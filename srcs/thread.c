/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:46:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 13:12:25 by fmadura          ###   ########.fr       */
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

static int	create_thread(t_env *env, pthread_t *thr, t_thr *arg)
{
	if (pthread_create(thr, NULL, launch_thread, arg))
		return (exit_wolf(env));
	return (1);
}

int		init_thread(t_env *env)
{
	set_thread(env);
	create_thread(env, &T_TH1, &T_T1);
	create_thread(env, &T_TH2, &T_T2);
	create_thread(env, &T_TH3, &T_T3);
	create_thread(env, &T_TH4, &T_T4);
	create_thread(env, &T_TH5, &T_T5);
	create_thread(env, &T_TH6, &T_T6);
	create_thread(env, &T_TH7, &T_T7);
	create_thread(env, &T_TH8, &T_T8);
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
	put_gun(env);
	return (0);
}
