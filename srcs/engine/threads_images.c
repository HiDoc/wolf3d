/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 00:07:30 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 10:12:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*launch_thread(void *arg)
{
	t_thread	*tmp;

	tmp = (t_thread *)arg;
	thread_current_sprite(tmp->child, tmp->path, tmp->nb, tmp->size);
	pthread_exit(NULL);
}

void	set_thread(t_weapon *mother, t_bloc *child, char *path, int size)
{
	int	i;

	i = 0;
	while (i < NB_THREAD_IMG)
	{
		mother->threads[i].mother = mother;
		mother->threads[i].child = child;
		mother->threads[i].path = path;
		mother->threads[i].size = size;
		mother->threads[i].nb = i;
		i++;
	}
}

int		init_thread(t_weapon *mother, t_bloc *child, char *path, int size)
{
	int	i;

	i = 0;
	set_thread(mother, child, path, size);
	while (i < NB_THREAD_IMG)
	{
		if (pthread_create(&mother->threads[i].th, NULL, launch_thread, &mother->threads[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < NB_THREAD_IMG)
	{
		if (pthread_join(mother->threads[i].th, NULL))
			return (0);
		i++;
	}
	return (1);
}
