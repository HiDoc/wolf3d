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
			t_vertex v = (t_vertex){
				sect->vertex[s + 0].x - e->player.where.x,
				sect->vertex[s + 0].y - e->player.where.y,
				sect->vertex[s + 1].x - e->player.where.x,
				sect->vertex[s + 1].y - e->player.where.y
			};
			/* Rotate them around the player's view */
			float pcos = e->player.anglecos;
			float psin = e->player.anglesin;
			t_vertex t = (t_vertex){
				v.x1 * psin - v.y1 * pcos,
				v.x1 * pcos + v.y1 * psin,
				v.x2 * psin - v.y2 * pcos,
				v.x2 * pcos + v.y2 * psin
			};
			/* Is the wall at least partially in front of the player? */
			if (t.y1 <= 0 && t.y2 <= 0)
				continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (t.y1 <= 0 || t.y2 <= 0)
			{
				float nearz = 1e-4f;
				float farz = 5;
				float nearside = 1e-5f;
				float farside = 20.f;
				// Find an intersection between the wall and the approximate edges of player's view
				t_xy i1 = Intersect(t.x1,t.y1,t.x2,t.y2, -nearside,nearz, -farside,farz);
				t_xy i2 = Intersect(t.x1,t.y1,t.x2,t.y2,  nearside,nearz,  farside,farz);
				if (t.y1 < nearz) {
					if (i1.y > 0)
					{
						t.x1 = i1.x;
						t.y1 = i1.y;
					}
					else
					{
						t.x1 = i2.x;
						t.y1 = i2.y;
					}
				}
				if (t.y2 < nearz) {
					if (i1.y > 0)
					{
						t.x2 = i1.x;
						t.y2 = i1.y;
					}
					else
					{
						t.x2 = i2.x;
						t.y2 = i2.y;
					}
				}
			}
			/* Do perspective transformation */
			t_vertex scale = (t_vertex){
				hfov / t.y1,
				vfov / t.y1,
				hfov / t.y2,
				vfov / t.y2
			};
			int x1 = W/2 - (int)(t.x1 * scale.x1);
			int x2 = W/2 - (int)(t.x2 * scale.x2);

			/* Verify if transformation is visible */
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
				continue ;

			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			float yceil  = sect->ceil  - e->player.where.z;
			float yfloor = sect->floor - e->player.where.z;

			/* Check the edge type. neighbor=-1 means wall, other=boundary between two e->sectors. */
			int neighbor = sect->neighbors[s];
			float nyceil = 0;
			float nyfloor = 0;

			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil  = e->sectors[neighbor].ceil  - e->player.where.z;
				nyfloor = e->sectors[neighbor].floor - e->player.where.z;
			}

			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
			#define Yaw(y,z) (y + z * e->player.yaw)
			int y1a = H/2 - (int)(Yaw(yceil, t.y1) * scale.y1);
			int y1b = H/2 - (int)(Yaw(yfloor, t.y1) * scale.y1);
			int y2a = H/2 - (int)(Yaw(yceil, t.y2) * scale.y2);
			int y2b = H/2 - (int)(Yaw(yfloor, t.y2) * scale.y2);
			/* The same for the neighboring sector */
			int ny1a = H/2 - (int)(Yaw(nyceil, t.y1) * scale.y1);
			int ny1b = H/2 - (int)(Yaw(nyfloor, t.y1) * scale.y1);
			int ny2a = H/2 - (int)(Yaw(nyceil, t.y2) * scale.y2);
			int ny2b = H/2 - (int)(Yaw(nyfloor, t.y2) * scale.y2);

			/* Render the wall. */
			int beginx = max(x1, now.sx1);
			int endx = min(x2, now.sx2);
			for (int x = beginx; x <= endx; ++x)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				int z = ((x - x1) * (t.y2 - t.y1) / (x2 - x1) + t.y1) * 8;
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int cya = clamp(ya, ytop[x], ybottom[x]); // top
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
				vline((t_line){x, ytop[x], cya - 1, 0x111111 , 0x222222, 0x111111}, e);

				/* Render floor: everything below this sector's floor height. */
				vline((t_line){x, cyb + 1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF}, e);

				/* Is there another sector behind this edge? */
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int	cnya = clamp(nya, ytop[x],ybottom[x]);
					int nyb = (x - x1) * (ny2b-ny1b) / (x2 - x1) + ny1b;
					int cnyb = clamp(nyb, ytop[x],ybottom[x]);

					/* If our ceiling is higher than their ceiling, render upper wall */
					unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
					vline((t_line){x, cya, cnya-1, 0, x==x1 || x==x2 ? 0 : r1, 0}, e); // Between our and their ceiling
					ytop[x] = clamp(max(cya, cnya), ytop[x], H - 1);   // Shrink the remaining window below these ceilings

					/* If our floor is lower than their floor, render bottom wall */
					vline((t_line){x, cnyb + 1, cyb, 0, x==x1 || x==x2 ? 0 : r2, 0}, e); // Between their and our floor
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					unsigned r = 0x010101 * (255 - z);
					vline((t_line){x, cya, cyb, 0, x==x1 || x==x2 ? 0 : r, 0}, e);
				}
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