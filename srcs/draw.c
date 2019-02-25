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

/* If it's partially behind the player, clip it against player's view frustrum */
void	clip_view(t_edge *t)
{
	const float nearz = 1e-4f;
	const float farz = 5;
	const float nearside = 1e-5f;
	const float farside = 20.f;
	// Find an intersection between the wall and the approximate edges of player's view
	t_xy i1 = Intersect(t->x1,t->y1,t->x2,t->y2, -nearside,nearz, -farside,farz);
	t_xy i2 = Intersect(t->x1,t->y1,t->x2,t->y2,  nearside,nearz,  farside,farz);
	if (t->y1 < nearz)
	{
		if (i1.y > 0)
		{
			t->x1 = i1.x;
			t->y1 = i1.y;
		}
		else
		{
			t->x1 = i2.x;
			t->y1 = i2.y;
		}
	}
	if (t->y2 < nearz)
	{
		if (i1.y > 0)
		{
			t->x2 = i1.x;
			t->y2 = i1.y;
		}
		else
		{
			t->x2 = i2.x;
			t->y2 = i2.y;
		}
	}
}

void	render_wall(t_edge t, t_projec p, t_projec n, int x, int x1, int x2, int *ytop, int *ybottom, t_engine *e, int neighbor)
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

void    DrawScreen(t_engine *e)
{
	enum { MaxQueue = 32 };  // maximum number of pending portal renders
	t_item		queue[MaxQueue];
	t_item		*head;
	t_item		*tail;
	int			ytop[W];
	int			ybottom[W];
	int			renderedsectors[e->NumSectors];
	t_item		now;
	t_sector	*sect;

	ft_memset(ybottom, (H - 1), sizeof(int) * W);
	ft_bzero(ytop, sizeof(int) * W);
	ft_bzero(renderedsectors, sizeof(int) * e->NumSectors);
	head = queue;
	tail = queue;

	/* Begin whole-screen rendering from where the player is. */
	*head = (t_item) {e->player.sector, 0, W - 1};
	if (++head == queue + MaxQueue)
		head = queue;

	while (head != tail)
	{
		/* Pick a sector & slice from the queue to draw */
		now = *tail;
		if (++tail == queue + MaxQueue)
			tail = queue;

		if (renderedsectors[now.sectorno] & 0x21)
			continue ; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];
		sect = &e->sectors[now.sectorno];
		/* Render each wall of this sector that is facing towards player. */
		int s = -1;
		while (++s < (int)sect->npoints)
		{
			/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
			t_edge v = current_edge(e, sect, s);

			/* Rotate them around the player's view */
			t_edge t = rotation_edge(e, v);

			/* Is the wall at least partially in front of the player? */
			if (t.y1 <= 0 && t.y2 <= 0)
				continue ;

			/* If it's partially behind the player, clip it against player's view frustrum */
			if (t.y1 <= 0 || t.y2 <= 0)
				clip_view(&t);

			/* Do perspective transformation */
			t_edge scale = scale_edge(t);
			int x1 = W/2 - (int)(t.x1 * scale.x1);
			int x2 = W/2 - (int)(t.x2 * scale.x2);

			/* Verify if transformation is visible */
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
				continue ;

			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			float yceil  = sect->ceil  - e->player.where.z;
			float yfloor = sect->floor - e->player.where.z;
			float nyceil = 0;
			float nyfloor = 0;

			/* Check the edge type. neighbor=-1 means wall, other=boundary between two e->sectors. */
			int neighbor = sect->neighbors[s];

			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil  = e->sectors[neighbor].ceil  - e->player.where.z;
				nyfloor = e->sectors[neighbor].floor - e->player.where.z;
			}

			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
			t_projec p = curr_projection(e->player.yaw, yceil, yfloor, t, scale);
			t_projec n = next_projection(e->player.yaw, nyceil, nyfloor, t, scale);
			/* Render the wall. */
			int beginx = max(x1, now.sx1);
			int endx = min(x2, now.sx2);
			int x = beginx;
			while (x <= endx)
			{
				render_wall(t, p, n, x, x1, x2, &ytop[x], &ybottom[x], e, neighbor);
				x++;
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if (neighbor >= 0 && endx >= beginx && (head+MaxQueue + 1 - tail) % MaxQueue)
			{
				*head = (t_item) { neighbor, beginx, endx };
				if(++head == queue+MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
	}
}