/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/22 16:46:52 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_l_int	wonder_wall(t_raycast container, t_projec projct,
		int *ytop, int *ybottom)
{
	t_l_int		limits;
	t_l_int		coord;
	int			diff_abs;
	const int	diff_curr = container.x - container.x1;

	/* Acquire the Y coordinates for our ceiling
	& floor for this X coordinate. Clamp them. */
	diff_abs = container.x2 - container.x1;
	!diff_abs ? diff_abs = 1 : 0;
	coord.ceil = diff_curr * (projct.y2a - projct.y1a)
		/ (diff_abs) + projct.y1a;
	coord.floor = diff_curr * (projct.y2b - projct.y1b)
		/ (diff_abs) + projct.y1b;
	limits.ceil = clamp(coord.ceil, *ytop, *ybottom);
	limits.floor = clamp(coord.floor, *ytop, *ybottom);
	return (limits);
}

void	render_wall(t_env *env, t_raycast container, int *ytop, int *ybottom)
{
	t_l_int 	y_coord_curr;
	t_l_int 	y_coord_next;
	const int	equal = container.x == container.x1 || container.x == container.x2;

	unsigned r1 = 0xFF00FF;
	unsigned r2 = 0xBB4EFF;
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
	y_coord_curr = wonder_wall(container, container.p, ytop, ybottom);

	/* Render ceiling: everything above this sector's ceiling height. */
	render_ceil((t_drawline){(void *)&container, *ytop, y_coord_curr.ceil - 1,
		0x111111 , 0x222222, 0x111111}, env);

	/* Render floor: everything below this sector's floor height. */
	render_floor((t_drawline){(void *)&container, y_coord_curr.floor + 1, *ybottom,
		0x0000FF, 0x0000AA, 0x0000FF}, env);

	/* Is there another sector behind this edge? */
	if (container.neighbor >= 0)
	{
		/* Same for _their_ floor and ceiling */
		y_coord_next = wonder_wall(container, container.n, ytop, ybottom);

		/* If our ceiling is higher than their ceiling, render upper wall */
		render_nfloor((t_drawline){(void *)&container, y_coord_curr.ceil,
			y_coord_next.ceil - 1, 0, equal ? 0 : r1, 0}, env); // Between our and their ceiling

		/* Shrink the remaining window below these ceilings */
		*ytop = (int)clamp(fmax(y_coord_curr.ceil,
			y_coord_next.ceil), *ytop, H - 1);

		/* If our floor is lower than their floor, render bottom wall */
		render_nwall((t_drawline){(void *)&container, y_coord_next.floor + 1,
			y_coord_curr.floor, 0, equal ? 0 : r2, 0}, env); // Between their and our floor

		/* Shrink the remaining window above these floors */
		*ybottom = (int)clamp(fmin(y_coord_curr.floor,
			y_coord_next.floor), 0, *ybottom);
	}
	else
	{
		/* There's no container.neighbor. Render wall from top to bottom  */
		render_cwall((t_drawline){(void *)&container, y_coord_curr.ceil,
			y_coord_curr.floor, 0, 0, 0}, env);
	}
}

/*
** Queue logic to render wall and add a new sector if it has a neighbour
*/
int		render_sector_edges(t_env *env, t_queue *q, int s)
{
	t_engine	*e;
	t_raycast	container;
	int			start;
	int			end;

	e = &env->engine;
	if (transform_vertex(e, q, &container, s) == 0)
		return (0);

	/* Get limits of ceil and floor of current sector */
	acquire_limits(e, q, &container, s);

	/* Render the wall. */
	end = (int)fmin(container.x2, q->now.sx2);
	start = (int)fmax(container.x1, q->now.sx1);

	/*Initialise scaler*/
	t_scaler ya_int = scaler_init(container.x1, start, container.x2, container.p.y1a, container.p.y2a);
	t_scaler yb_int = scaler_init(container.x1, start, container.x2, container.p.y1b, container.p.y2b);
	// t_scaler nya_int = scaler_init(container.x1, start, container.x2, container.n.y1a, container.n.y2a);
	// t_scaler nyb_int = scaler_init(container.x1, start, container.x2, container.n.y1b, container.n.y2b);

	container.x = start;
	container.li_sector = (t_l_int){env->engine.sectors[q->now.sectorno].ceil,
		env->engine.sectors[q->now.sectorno].floor};
	while (container.x <= end)
	{
		int ya = scaler_next(&ya_int);
    	int yb = scaler_next(&yb_int);
		(void)ya;
		(void)yb;
		render_wall(env, container, &q->ytop[container.x], &q->ybottom[container.x]);
		++container.x;
	}
	// ici
	schedule_queue(q, container, start, end);
	return (1);
}

static void		render_sprites(t_env *env, t_wrap_sect *obj)
{
	const t_engine *e = &env->engine;
	t_drawline		drawline;
	t_raycast		raycast;
	t_edge			edge;
	t_vtx player = {e->player.where.x, e->player.where.y};

	ft_bzero(&drawline, sizeof(t_drawline));
	// if distance < value && obj not already picked, object is pickable
	obj->is_pickable = (dist_vertex(player, obj->vertex) < 5 && !obj->is_picked);
	edge = (t_edge){
	(t_vtx){obj->vertex.x - 1, obj->vertex.y},
	(t_vtx){obj->vertex.x + 1, obj->vertex.y}};

	// translation
	edge = translation_edge(env->engine.player.where, edge.v1, edge.v2);
	raycast.trsl = edge;

	// rotation
	edge = rotation_edge(env->engine.player, edge);
	raycast.rot = edge;

	// scale
	edge = scale_edge(edge);
	raycast.scale = edge;

	raycast.x2 = W/2 - (int)(raycast.rot.v1.x * raycast.scale.v1.x);
	raycast.x1 = W/2 - (int)(raycast.rot.v2.x * raycast.scale.v2.x);
	raycast.li_sector.ceil = 15;
	raycast.li_sector.floor = 0;
	raycast.lf_current = (t_l_float){15 - e->player.where.z, 0 - e->player.where.z};
	raycast.p = calc_projection(e->player.yaw, raycast.lf_current, raycast.rot, raycast.scale);
	if (raycast.x1 > 0 && raycast.x2 < W)
	{

		raycast.x = raycast.x1;
		drawline.container = (void *)&raycast;
		int x = 0, y = 0;
		raycast.li_sector = wonder_wall(raycast, raycast.p, &x, &y);
		drawline.from = 0;
		drawline.to = 400;
		drawline.bottom = 0xFFFFFFFF;
		drawline.middle = 0xFFFFFFFF;
		drawline.top = 0xFFFFFFFF;
		while (raycast.x < raycast.x2)
		{
			vline(drawline, env);
			raycast.x++;
		}
	}
}

void	dfs(t_env *env)
{
	t_queue		queue;
	t_engine	*engine;
	int			s;

	engine = &env->engine;
	ini_queue(engine, &queue);
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
				if (!current_obj->is_picked)
					render_sprites(env, current_obj);
				current_obj = current_obj->next;
			}
		} // for s in sector's edges
		++queue.renderedsectors[queue.now.sectorno];
	}
	free(queue.renderedsectors);
}