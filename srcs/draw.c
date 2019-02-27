#include "doom.h"

void	render_wall(t_engine *e, t_transf container, int *ytop, int *ybottom)
{
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	int z = ((container.x - container.x1) * (container.t.v2.y - container.t.v1.y)
		/ (container.x2 - container.x1) + container.t.v1.y) * 8;
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
	int ya = (container.x - container.x1) * (container.p.y2a - container.p.y1a)
		/ (container.x2 - container.x1) + container.p.y1a;
	int cya = clamp(ya, *ytop, *ybottom); // top
	int yb = (container.x - container.x1) * (container.p.y2b - container.p.y1b)
		/ (container.x2 - container.x1) + container.p.y1b;
	int cyb = clamp(yb, *ytop, *ybottom); // bottom

	/* Render ceiling: everything above this sector's ceiling height. */
	vline((t_drawline){container.x, *ytop, cya - 1, 0x111111 , 0x222222, 0x111111}, e);

	/* Render floor: everything below this sector's floor height. */
	vline((t_drawline){container.x, cyb + 1, *ybottom, 0x0000FF,0x0000AA,0x0000FF}, e);

	/* Is there another sector behind this edge? */
	if (container.neighbor >= 0)
	{
		/* Same for _their_ floor and ceiling */
		int nya = (container.x - container.x1) * (container.n.y2a - container.n.y1a)
			/ (container.x2 - container.x1) + container.n.y1a;
		int	cnya = clamp(nya, *ytop,*ybottom);
		int nyb = (container.x - container.x1) * (container.n.y2b - container.n.y1b)
			/ (container.x2 - container.x1) + container.n.y1b;
		int cnyb = clamp(nyb, *ytop, *ybottom);

		/* If our ceiling is higher than their ceiling, render upper wall */
		unsigned r1 = 0x010101 * (255 - z);
		unsigned r2 = 0x040007 * (31 - z / 8);
		vline((t_drawline){container.x, cya, cnya-1, 0, container.x==container.x1
			|| container.x==container.x2 ? 0 : r1, 0}, e); // Between our and their ceiling
		*ytop = clamp(max(cya, cnya), *ytop, H - 1);   // Shrink the remaining window below these ceilings

		/* If our floor is lower than their floor, render bottom wall */
		vline((t_drawline){container.x, cnyb + 1, cyb, 0, container.x==container.x1
			|| container.x==container.x2 ? 0 : r2, 0}, e); // Between their and our floor
		*ybottom = clamp(min(cyb, cnyb), 0, *ybottom); // Shrink the remaining window above these floors
	}
	else
	{
		/* There's no container.neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		unsigned r = 0x010101 * (255 - z);
		vline((t_drawline){container.x, cya, cyb, 0, container.x==container.x1
			|| container.x==container.x2 ? 0 : r, 0}, e);
	}
}

int		render_sector_edges(t_engine *e, t_queue *q, int s)
{
	t_transf	container;
	int			start;
	int			end;

	if (transform_vertex(e, q, &container, s) == 0)
		return (0);
	/* Render the wall. */
	end = min(container.x2, q->now.sx2);
	start = max(container.x1, q->now.sx1);
	container.x = start;
	while (container.x <= end)
	{
		render_wall(e, container, &q->ytop[container.x], &q->ybottom[container.x]);
		++container.x;
	}
	/* Schedule the neighboring sector for rendering within the window formed by this wall. */
	if (container.neighbor >= 0 && end >= start && (q->head + MaxQueue + 1 - q->tail) % MaxQueue)
	{
		*q->head = (t_item) {container.neighbor, start, end};
		if (++q->head == q->queue + MaxQueue)
			q->head = q->queue;
	}
	return (1);
}

void    DrawScreen(t_engine *engine)
{
	t_queue		queue;
	int			s;

	ini_queue(engine, &queue);
	/* Begin whole-screen rendering from where the player is. */
	*queue.head = (t_item) {engine->player.sector, 0, W - 1};
	if (++queue.head == queue.queue + MaxQueue)
		queue.head = queue.queue;
	while (queue.head != queue.tail)
	{
		/* Pick a sector & slice from the queue to draw */
		queue.now = *queue.tail;
		if (++queue.tail == queue.queue + MaxQueue)
			queue.tail = queue.queue;

		if (queue.renderedsectors[queue.now.sectorno] & 0x21)
			continue ; // Odd = still rendering, 0x20 = give up
		++queue.renderedsectors[queue.now.sectorno];
		queue.sect = &engine->sectors[queue.now.sectorno];

		/* Render each wall of this sector that is facing towards player. */
		s = -1;
		while (++s < (int)queue.sect->npoints) // for s in sector's edges
			render_sector_edges(engine, &queue, s);
		++queue.renderedsectors[queue.now.sectorno];
	}
	free(queue.renderedsectors);
}