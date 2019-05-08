/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:40:55 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:54:25 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Schedule the neighboring sector for rendering
*/

void	schedule_queue(t_queue *q, t_raycast container, int start, int end)
{
	if (container.neighbor >= 0 && end >= start
		&& (q->head + MAXQUEUE + 1 - q->tail) % MAXQUEUE)
	{
		*q->head = (t_item){container.neighbor, start, end};
		if (++q->head == q->queue + MAXQUEUE)
			q->head = q->queue;
	}
}

int		ini_queue(t_queue *q, unsigned size)
{
	ft_memset(q->ybottom, (H - 1), sizeof(int) * W);
	ft_bzero(q->ytop, sizeof(int) * W);
	ft_bzero(q->renderedsectors, sizeof(int) * size);
	q->head = q->queue;
	q->tail = q->queue;
	return (1);
}
