/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:18:30 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/03 03:28:28 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		render_sprites(t_env *env, t_queue *q,
			SDL_Surface *sprite, t_vctr vertex, t_l_float size)
{
	const t_engine	*e = &env->engine;
	const t_player	p = e->player;
	t_drawline		drawline;
	t_raycast		raycast;
	t_edge			edge;

	ft_bzero(&drawline, sizeof(t_drawline));
	edge = (t_edge){
		(t_vtx){vertex.x - p.anglesin, vertex.y + p.anglecos},
		(t_vtx){vertex.x + p.anglesin, vertex.y - p.anglecos}
	};
	if (!transform_vertex(&raycast, e->player, edge.v2, edge.v1))
		return ;
	raycast.neighbor = -1;
	acquire_limits(&env->engine, &raycast,
		(t_l_float){size.ceil + q->sect->floor, q->sect->floor + size.floor});
	const int start = fmax(raycast.x1, 0);
	const int end = fmin(raycast.x2, W);
	if (fmax(raycast.x1, raycast.x2) > 0 || fmin(raycast.x1, raycast.x2) < W)
	{
		raycast.x = start;
		drawline.container = (void *)&raycast;
		drawline.from = raycast.p.y1a;
		drawline.to = raycast.p.y1b;
		drawline.bottom = 0xFF;
		drawline.middle = 0xFF;
		drawline.top = 0xFF;
		while (raycast.x < end)
		{
			oline(drawline, env, sprite);
			raycast.x++;
		}
	}
}

/*
** Queue logic to render wall and add a new sector if it has a neighbour
*/
int			render_sector_edges(t_env *env, t_queue *q, int s)
{
	const t_vtx	*vertex = q->sect->vertex;
	t_engine	*e;
	t_raycast	ctn;
	int			end;
	int			start;

	e = &env->engine;
	if (transform_vertex(&ctn, e->player, vertex[s], vertex[s + 1]) == 0
		|| ctn.x1 >= ctn.x2 || ctn.x2 < q->now.sx1 || ctn.x1 > q->now.sx2)
		return (0);

	/* get the neighbour of the current vertex if there*/
	ctn.neighbor = q->sect->neighbors[s];

	// ctn.sprite = door_neighbors(e, (t_vtx*)vertex, s)
	// ? env->world.surfaces.doors[1].sprite
	// : env->world.surfaces.walls[0].sprite;
	ctn.sprite = env->world.surfaces.walls[0].sprite;

	/* Get limits of ceil and floor of current sector */
	acquire_limits(e, &ctn, (t_l_float){q->sect->ceil, q->sect->floor});

	/* Render the wall. */
	start = (int)fmax(ctn.x1, q->now.sx1);
	end = (int)fmin(ctn.x2, q->now.sx2);

	/* Start at x, clamped with screen*/
	ctn.x = start;
	ctn.li_sector = (t_l_int){q->sect->ceil, q->sect->floor};
	while (ctn.x <= end)
	{
		render_wall(env, ctn, &q->ytop[ctn.x], &q->ybottom[ctn.x]);
		++ctn.x;
	}
	// render_perspective(env, &ctn);
	schedule_queue(q, ctn, start, end);
	return (1);
}

void		render_object(t_env *env, t_queue *queue)
{
	const t_object	*ctn = env->world.objects;
	const int		gem = WORLD_NB_CSMBLE + WORLD_NB_GEMS;
	t_wrap_sect		*object;
	int				ref;
	t_vtx 			p;

	p = (t_vtx){env->engine.player.where.x, env->engine.player.where.y};
	object = queue->sect->head_object;
	while (object)
	{
		if (!object->is_picked)
		{
			object->is_pickable = (dist_vertex(p, object->vertex) < 5);
			ref = object->ref + ((object->is_wpn) ? gem : 0);
			render_sprites(env, queue, ctn[ref].sprite,
			(t_vctr){object->vertex.x, object->vertex.y, 0}, ctn[ref].size);
			draw_pick_infos(env, object, ref);
		}
		object = object->next;
	}
}

void		render_bullet(t_env *env, t_player p, t_impact *shot, t_queue *queue)
{
	int	i;

	i = 0;
	while (i < NB_SHOT)
	{
		render_sprites(env, queue, p.sprite, shot[i].position.where, (t_l_float){5, 0});
		i++;
	}
}

void		render_enemies(t_env *env, t_queue *queue)
{
	t_wrap_enmy	*en;

	en = queue->sect->head_enemy;
	while (en)
	{
		render_sprites(env, queue, en->sprite, en->player.where, en->brain.size);
		// if (en->a.is_shooting)
		// 	render_bullet(env, env->engine.player, en->shot, queue);
		en = en->next;
	}
}

void		render_sector(t_env *env, t_queue *queue)
{
	int	s;

	s = -1;
	while (++s < (int)queue->sect->npoints)
		render_sector_edges(env, queue, s);
	render_object(env, queue);
	render_enemies(env, queue);
	if (env->player.inventory.current)
		env->player.inventory.current->current->ref == 3
		? render_bullet(env, env->engine.player, env->player.shot, queue)
		: 0;
}
