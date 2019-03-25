/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 20:16:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_l_int		wonder_wall(t_raycast ctn, t_projec projct, int *ytop, int *ybottom)
{
	t_l_int		limits;
	t_l_int		coord;
	const int	diff_abs = ctn.x2 - ctn.x1;
	const int	diff_curr = ctn.x - ctn.x1;

	/* Acquire the Y coordinates for our ceiling
	& floor for this X coordinate. Clamp them. */
	coord.ceil = diff_curr * (projct.y2a - projct.y1a)
		/ (diff_abs) + projct.y1a;
	coord.floor = diff_curr * (projct.y2b - projct.y1b)
		/ (diff_abs) + projct.y1b;
	limits.ceil = clamp(coord.ceil, *ytop, *ybottom);
	limits.floor = clamp(coord.floor, *ytop, *ybottom);
	return (limits);
}

void	render_wall(t_env *env, t_raycast ctn, int *ytop, int *ybottom)
{
	t_l_int 	y_coord_curr;
	t_l_int 	y_coord_next;
	const int	equal = ctn.x == ctn.x1 || ctn.x == ctn.x2;

	unsigned r1 = 0xFF00FF;
	unsigned r2 = 0xBB4EFF;
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
	y_coord_curr = wonder_wall(ctn, ctn.p, ytop, ybottom);

	/* Render ceiling: everything above this sector's ceiling height. */
	render_ceil((t_drawline){(void *)&ctn, *ytop, y_coord_curr.ceil - 1,
		0x111111 , 0x222222, 0x111111}, env);

	/* Render floor: everything below this sector's floor height. */
	render_floor((t_drawline){(void *)&ctn, y_coord_curr.floor + 1, *ybottom,
		0x0000FF, 0x0000AA, 0x0000FF}, env);

	/* Is there another sector behind this edge? */
	if (ctn.neighbor >= 0)
	{
		/* Same for _their_ floor and ceiling */
		y_coord_next = wonder_wall(ctn, ctn.n, ytop, ybottom);

		/* If our ceiling is higher than their ceiling, render upper wall */
		render_nfloor((t_drawline){(void *)&ctn, y_coord_curr.ceil,
			y_coord_next.ceil - 1, 0, equal ? 0 : r1, 0}, env); // Between our and their ceiling

		/* Shrink the remaining window below these ceilings */
		*ytop = (int)clamp(fmax(y_coord_curr.ceil,
			y_coord_next.ceil), *ytop, H - 1);

		/* If our floor is lower than their floor, render bottom wall */
		render_nwall((t_drawline){(void *)&ctn, y_coord_next.floor + 1,
			y_coord_curr.floor, 0, equal ? 0 : r2, 0}, env); // Between their and our floor

		/* Shrink the remaining window above these floors */
		*ybottom = (int)clamp(fmin(y_coord_curr.floor,
			y_coord_next.floor), 0, *ybottom);
	}
	else
	{
		/* There's no ctn.neighbor. Render wall from top to bottom  */
		render_cwall((t_drawline){(void *)&ctn, y_coord_curr.ceil,
			y_coord_curr.floor, 0, 0, 0}, env);
	}
}

int		render_perspective(t_env *env, t_raycast *ctn)
{
	t_edge		bot;
	t_edge		top;

	//bot
	bot = (t_edge){(t_vtx){ctn->x1, 600}, (t_vtx){ctn->x2, 600}};
	//top
	const int max = ctn->p.y2b < ctn->p.y1b ? ctn->p.y2b : ctn->p.y1b;
	top = (t_edge){(t_vtx){ctn->x1, max}, (t_vtx){ctn->x2, max}};
	t_vtx horizon = {0, max};
	t_vtx vanish = {W / 2, H - max};
	draw_perspective(env->sdl.surface, (t_square){top, bot}, horizon, vanish);
	return (1);
}

void				oline(t_drawline l, t_env *env)
{
	SDL_Surface *sprite = env->world.enemies[0].sprite;
	const t_raycast *ctn = (t_raycast *)l.container;
	int		*pixels;
	int		x;
	int		iter;

	x = ctn->x;
	pixels	= (int *)env->sdl.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	const float height = l.to - l.from;
	const float widht = ctn->x2 - ctn->x1;
	printf("%f\n", height);
	if (l.from == l.to)
		pixels[l.from * W + x] = 0x00;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = 0x00;
		iter = l.from + 1;
		float y = 0;
		while (iter < l.to)
		{
			const int pix = getpixel(sprite, (int)(x / widht * sprite->w) % sprite->w,
				(int)(y / height * sprite->h) % sprite->h);
			if (pix & 0xff)
				pixels[iter * W + x] = pix;
			y++;
			iter++;
		}
		pixels[l.to * W + x] = 0x00;
	}
}

static void		render_sprites(t_env *env, t_queue *q, t_wrap_sect *obj)
{
	const t_engine *e = &env->engine;
	t_drawline		drawline;
	t_raycast		raycast;
	t_edge			edge;

	ft_bzero(&drawline, sizeof(t_drawline));
	edge = (t_edge){
		(t_vtx){obj->vertex.x - 1, obj->vertex.y},
		(t_vtx){obj->vertex.x + 1, obj->vertex.y}
	};
	if (!transform_vertex(&raycast, e->player, edge.v2, edge.v1))
		return ;
	raycast.neighbor = -1;
	acquire_limits(&env->engine, &e->sectors[q->now.sectorno], &raycast);
	raycast.li_sector = (t_l_int){e->sectors[q->now.sectorno].ceil,
		e->sectors[q->now.sectorno].floor};
	if (raycast.x1 > 0 && raycast.x2 < W)
	{
		raycast.x = raycast.x1;
		drawline.container = (void *)&raycast;
		drawline.from = raycast.p.y1a;
		drawline.to = raycast.p.y1b;
		drawline.bottom = 0xFF;
		drawline.middle = 0xFF;
		drawline.top = 0xFF;
		while (raycast.x < raycast.x2)
		{
			oline(drawline, env);
			raycast.x++;
		}
	}
}

/*
** Queue logic to render wall and add a new sector if it has a neighbour
*/
int		render_sector_edges(t_env *env, t_queue *q, int s)
{
	const t_vtx	*vertex = q->sect->vertex;
	t_engine	*e;
	t_raycast	ctn;
	int			end;
	int			start;

	e = &env->engine;
	if (transform_vertex(&ctn, e->player, vertex[s], vertex[s + 1]) == 0)
		return (0);
	if (ctn.x1 >= ctn.x2 || ctn.x2 < q->now.sx1 || ctn.x1 > q->now.sx2)
		return (0);

	/* Get limits of ceil and floor of current sector */

	/* Check the edge type. neighbor=-1 means wall,
	** other=boundary between two e->sectors. */
	ctn.neighbor = q->sect->neighbors[s];

	acquire_limits(e, q->sect, &ctn);

	/* Render the wall. */
	end = (int)fmin(ctn.x2, q->now.sx2);
	start = (int)fmax(ctn.x1, q->now.sx1);

	/* Start at x, clamped with screen*/
	ctn.x = start;
	ctn.li_sector = (t_l_int){e->sectors[q->now.sectorno].ceil,
		e->sectors[q->now.sectorno].floor};
	while (ctn.x <= end)
	{
		render_wall(env, ctn, &q->ytop[ctn.x], &q->ybottom[ctn.x]);
		++ctn.x;
	}
	schedule_queue(q, ctn, start, end);
	return (1);
}

void	dfs(t_env *env)
{
	t_queue		queue;
	t_engine	*engine;
	int			s;

	engine = &env->engine;
	ini_queue(engine, &queue);
	SDL_memset(env->sdl.surface->pixels, 0,
		env->sdl.surface->h * env->sdl.surface->pitch);
	/* Begin whole-screen rendering from where the player is. */
	*queue.head = (t_item) {engine->player.sector, 0, W - 1};
	if (++queue.head == queue.queue + MAXQUEUE)
		queue.head = queue.queue;
	while (queue.head != queue.tail)
	{
		/* Pick a sector & slice from the queue to draw */
		queue.now = *queue.tail;
		if (++queue.tail == queue.queue + MAXQUEUE)
			queue.tail = queue.queue;

		if (queue.renderedsectors[queue.now.sectorno] & 0x21)
			continue ;
		++queue.renderedsectors[queue.now.sectorno];
		queue.sect = &engine->sectors[queue.now.sectorno];

		/* Render each wall of this sector that is facing towards player. */
		s = -1;
		while (++s < (int)queue.sect->npoints)
		{
			render_sector_edges(env, &queue, s);
			// Render objects/bots sprites //
			t_wrap_sect *current_obj;
			current_obj = engine->sectors[engine->player.sector].head_object;
			while (current_obj)
			{
				render_sprites(env, &queue, current_obj);
				current_obj = current_obj->next;
			}
		} // for s in sector's edges
		++queue.renderedsectors[queue.now.sectorno];
	}
	free(queue.renderedsectors);
}
