#include "doom.h"

/*
** Schedule the neighboring sector for rendering
*/
void	schedule_queue(t_queue *q, t_raycast container, int start, int end)
{
	if (container.neighbor >= 0 && end >= start
		&& (q->head + MAXQUEUE + 1 - q->tail) % MAXQUEUE)
	{
		*q->head = (t_item) {container.neighbor, start, end};
		if (++q->head == q->queue + MAXQUEUE)
			q->head = q->queue;
	}
}

int		ini_queue(t_engine *e, t_queue *q)
{
	if ((q->renderedsectors = (int *)malloc(e->nsectors
		* sizeof(int))) == NULL)
		return (0);
	ft_memset(q->ybottom, (H - 1), sizeof(int) * W);
	ft_bzero(q->ytop, sizeof(int) * W);
	ft_bzero(q->renderedsectors, sizeof(int) * e->nsectors);
	q->head = q->queue;
	q->tail = q->queue;
	return (1);
}