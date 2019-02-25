#include "wolf.h"

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void				vline(t_line l, t_engine *e)
{
	int		*pix;
	int		y;

	pix	= (int *)e->surface->pixels;
	l.y1 = clamp(l.y1, 0, H - 1);
	l.y2 = clamp(l.y2, 0, H - 1);
	if (l.y2 == l.y1)
		pix[l.y1 * W + l.x] = l.middle;
	else if (l.y2 > l.y1)
	{
		pix[l.y1 * W + l.x] = l.top;
		y = l.y1 + 1;
		while (y < l.y2)
		{
			pix[y * W + l.x] = l.middle;
			y++;
		}
		pix[l.y2 * W + l.x] = l.bottom;
	}
}

void	render_wall(t_edge t, t_projec p, t_projec n, int x,
		int x1, int x2, int *ytop, int *ybottom, t_engine *e, int neighbor)
{
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	int z = ((x - x1) * (t.y2 - t.y1) / (x2 - x1) + t.y1) * 8;
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
	int ya = (x - x1) * (p.y2a - p.y1a) / (x2 - x1) + p.y1a;
	int cya = clamp(ya, *ytop, *ybottom); // top
	int yb = (x - x1) * (p.y2b - p.y1b) / (x2 - x1) + p.y1b;
	int cyb = clamp(yb, *ytop, *ybottom); // bottom

	/* Render ceiling: everything above this sector's ceiling height. */
	vline((t_line){x, *ytop, cya - 1, 0x111111 , 0x222222, 0x111111}, e);

	/* Render floor: everything below this sector's floor height. */
	vline((t_line){x, cyb + 1, *ybottom, 0x0000FF,0x0000AA,0x0000FF}, e);

	/* Is there another sector behind this edge? */
	if (neighbor >= 0)
	{
		/* Same for _their_ floor and ceiling */
		int nya = (x - x1) * (n.y2a - n.y1a) / (x2 - x1) + n.y1a;
		int	cnya = clamp(nya, *ytop,*ybottom);
		int nyb = (x - x1) * (n.y2b-n.y1b) / (x2 - x1) + n.y1b;
		int cnyb = clamp(nyb, *ytop,*ybottom);

		/* If our ceiling is higher than their ceiling, render upper wall */
		unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
		vline((t_line){x, cya, cnya-1, 0, x==x1 || x==x2 ? 0 : r1, 0}, e); // Between our and their ceiling
		*ytop = clamp(max(cya, cnya), *ytop, H - 1);   // Shrink the remaining window below these ceilings

		/* If our floor is lower than their floor, render bottom wall */
		vline((t_line){x, cnyb + 1, cyb, 0, x==x1 || x==x2 ? 0 : r2, 0}, e); // Between their and our floor
		*ybottom = clamp(min(cyb, cnyb), 0, *ybottom); // Shrink the remaining window above these floors
	}
	else
	{
		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		unsigned r = 0x010101 * (255 - z);
		vline((t_line){x, cya, cyb, 0, x==x1 || x==x2 ? 0 : r, 0}, e);
	}
}

int		render_sector_edges(t_engine *e, t_queue *q, int s)
{
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	t_edge v = current_edge(e, q->sect, s);

	/* Rotate them around the player's view */
	t_edge t = rotation_edge(e, v);

	/* Is the wall at least partially in front of the player? */
	if (t.y1 <= 0 && t.y2 <= 0)
		return (0);

	/* If it's partially behind the player, clip it against player's view frustrum */
	if (t.y1 <= 0 || t.y2 <= 0)
		clip_view(&t);

	/* Do perspective transformation */
	t_edge scale = scale_edge(t);
	int x1 = W/2 - (int)(t.x1 * scale.x1);
	int x2 = W/2 - (int)(t.x2 * scale.x2);

	/* Verify if transformation is visible */
	if (x1 >= x2 || x2 < q->now.sx1 || x1 > q->now.sx2)
		return (0);

	/* Check the edge type. neighbor=-1 means wall, other=boundary between two e->sectors. */
	int neighbor = q->sect->neighbors[s];

	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	t_ylevel levels = get_ylevels(e, q->sect, neighbor);

	/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
	t_projec p = curr_projection(e->player.yaw, levels, t, scale);
	t_projec n = next_projection(e->player.yaw, levels, t, scale);

	/* Render the wall. */
	int beginx = max(x1, q->now.sx1);
	int endx = min(x2, q->now.sx2);
	int x = beginx;
	while (x <= endx)
	{
		render_wall(t, p, n, x, x1, x2, &q->ytop[x], &q->ybottom[x], e, neighbor);
		x++;
	}
	/* Schedule the neighboring sector for rendering within the window formed by this wall. */
	if (neighbor >= 0 && endx >= beginx && (q->head + MaxQueue + 1 - q->tail) % MaxQueue)
	{
		*q->head = (t_item) { neighbor, beginx, endx };
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