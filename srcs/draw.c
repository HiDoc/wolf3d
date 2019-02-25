#include "doom.h"

void	render_wall(t_edge t, t_projec p, t_projec n, int x,
		int x1, int x2, int *ytop, int *ybottom, t_engine *e, int container.neighbor)
{
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	int z = ((x - x1) * (t.v2.y - t.v1.y) / (x2 - x1) + t.v1.y) * 8;
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
	int ya = (x - x1) * (p.y2a - p.y1a) / (x2 - x1) + p.y1a;
	int cya = clamp(ya, *ytop, *ybottom); // top
	int yb = (x - x1) * (p.y2b - p.y1b) / (x2 - x1) + p.y1b;
	int cyb = clamp(yb, *ytop, *ybottom); // bottom

	/* Render ceiling: everything above this sector's ceiling height. */
	vline((t_drawline){x, *ytop, cya - 1, 0x111111 , 0x222222, 0x111111}, e);

	/* Render floor: everything below this sector's floor height. */
	vline((t_drawline){x, cyb + 1, *ybottom, 0x0000FF,0x0000AA,0x0000FF}, e);

	/* Is there another sector behind this edge? */
	if (container.neighbor >= 0)
	{
		/* Same for _their_ floor and ceiling */
		int nya = (x - x1) * (n.y2a - n.y1a) / (x2 - x1) + n.y1a;
		int	cnya = clamp(nya, *ytop,*ybottom);
		int nyb = (x - x1) * (n.y2b-n.y1b) / (x2 - x1) + n.y1b;
		int cnyb = clamp(nyb, *ytop,*ybottom);

		/* If our ceiling is higher than their ceiling, render upper wall */
		unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
		vline((t_drawline){x, cya, cnya-1, 0, x==x1 || x==x2 ? 0 : r1, 0}, e); // Between our and their ceiling
		*ytop = clamp(max(cya, cnya), *ytop, H - 1);   // Shrink the remaining window below these ceilings

		/* If our floor is lower than their floor, render bottom wall */
		vline((t_drawline){x, cnyb + 1, cyb, 0, x==x1 || x==x2 ? 0 : r2, 0}, e); // Between their and our floor
		*ybottom = clamp(min(cyb, cnyb), 0, *ybottom); // Shrink the remaining window above these floors
	}
	else
	{
		/* There's no container.neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		unsigned r = 0x010101 * (255 - z);
		vline((t_drawline){x, cya, cyb, 0, x==x1 || x==x2 ? 0 : r, 0}, e);
	}
}

int		render_sector_edges(t_engine *e, t_queue *q, int s)
{
	t_transf	container;
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	container.v = current_edge(e->player.where, q->sect->vertex[s], q->sect->vertex[s + 1]);

	/* Rotate them around the player's view */
	container.t = rotation_edge(e->player, container.v);

	/* Is the wall at least partially in front of the player? */
	if (container.t.v1.y <= 0 && container.t.v2.y <= 0)
		return (0);

	/* If it's partially behind the player, clip it against player's view frustrum */
	if (container.t.v1.y <= 0 || container.t.v2.y <= 0)
		clip_view(&container.t);

	/* Do perspective transformation */
	container.scale = scale_edge(container.t);
	container.x1 = W/2 - (int)(container.t.v1.x * container.scale.v1.x);
	container.x2 = W/2 - (int)(container.t.v2.x * container.scale.v2.x);

	/* Verify if transformation is visible */
	if (container.x1 >= container.x2 || container.x2 < q->now.sx1 || container.x1 > q->now.sx2)
		return (0);

	/* Check the edge type. neighbor=-1 means wall, other=boundary between two e->sectors. */
	container.neighbor = q->sect->neighbors[s];

	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	container.lf_current = (t_limit_float){q->sect->ceil - e->player.where.z,
		q->sect->floor - e->player.where.z};
	container.lf_next = (t_limit_float){0, 0};
	if (container.neighbor >= 0)
	{
		container.lf_next = (t_limit_float){
			e->sectors[container.neighbor].ceil - e->player.where.z,
			e->sectors[container.neighbor].floor - e->player.where.z
		};
	}
	
	/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
	container.p = calc_projection(e->player.yaw, container.lf_current, container.t, container.scale);
	container.n = calc_projection(e->player.yaw, container.lf_next, container.t, container.scale);

	/* Render the wall. */
	int beginx = max(container.x1, q->now.sx1);
	int endx = min(container.x2, q->now.sx2);
	int x = beginx;
	while (x <= endx)
	{
		render_wall(
			container.t,
			container.p,
			container.n,
			x,
			container.x1,
			container.x2, 
			&q->ytop[x], &q->ybottom[x],
			e, container.neighbor);
		x++;
	}
	/* Schedule the neighboring sector for rendering within the window formed by this wall. */
	if (container.neighbor >= 0 && endx >= beginx && (q->head + MaxQueue + 1 - q->tail) % MaxQueue)
	{
		*q->head = (t_item) { container.neighbor, beginx, endx };
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