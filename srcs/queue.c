#include "wolf.h"

int		ini_queue(t_engine *e, t_queue *q)
{
	if ((q->renderedsectors = (int *)malloc(e->NumSectors
		* sizeof(int))) == NULL)
		return (0);
	ft_memset(q->ybottom, (H - 1), sizeof(int) * W);
	ft_bzero(q->ytop, sizeof(int) * W);
	ft_bzero(q->renderedsectors, sizeof(int) * e->NumSectors);
	q->head = q->queue;
	q->tail = q->queue;
	return (1);
}