/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:20 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/12 14:21:31 by sgalasso         ###   ########.fr       */
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
	// !diff_abs ? diff_abs = 1 : 0;
	coord.ceil = diff_curr * (projct.y2a - projct.y1a) / (diff_abs) + projct.y1a;
	coord.floor = diff_curr * (projct.y2b - projct.y1b)
		/ (diff_abs) + projct.y1b;
	limits.ceil = clamp(coord.ceil, *ytop, *ybottom);
	limits.floor = clamp(coord.floor, *ytop, *ybottom);
	return (limits);
}

void		render_wall(t_env *env, t_raycast ctn, int *ytop, int *ybottom)
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

int			render_perspective(t_env *env, t_raycast *ctn)
{
	t_edge		bot;
	t_edge		top;

	bot = (t_edge){(t_vtx){ctn->x1, 600}, (t_vtx){ctn->x2, 600}};
	const int max = ctn->p.y2b < ctn->p.y1b ? ctn->p.y2b : ctn->p.y1b;
	top = (t_edge){(t_vtx){ctn->x1, max}, (t_vtx){ctn->x2, max}};
	t_vtx horizon = {0, max};
	t_vtx vanish = {W / 2, H / 2 - max / 2};
	draw_perspective(env->sdl.surface, (t_square){top, bot}, horizon, vanish);
	return (1);
}

void		dfs(t_env *env)
{
	t_queue		queue;
	t_engine	*engine;

	engine = &env->engine;
	queue = engine->queue;
	ini_queue(&queue, engine->nsectors);
	SDL_memset(env->sdl.surface->pixels, 0,
		env->sdl.surface->h * env->sdl.surface->pitch);

	/* Begin whole-screen rendering from where the player is. */
	*queue.head = (t_item) {engine->player.sector, 0, W - 1};
	if (++queue.head == queue.queue + MAXQUEUE)
		queue.head = queue.queue;

	display_skybox(env);

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
		render_sector(env, &queue);
		++queue.renderedsectors[queue.now.sectorno];
	}
}
