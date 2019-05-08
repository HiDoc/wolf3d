/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:18:30 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 22:33:10 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		render_loop_sprites(t_env *env, SDL_Surface *sprite,
			t_drawline drawline, t_raycast raycast)
{
	int			start;
	int			end;

	start = fmax(raycast.x1, 0);
	end = fmin(raycast.x2, W);
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

void		render_sprites(t_env *env, SDL_Surface *sprite,
			t_vctr vertex, t_l_float size)
{
	const t_engine	*e = &env->engine;
	const t_player	p = e->player;
	t_drawline		drawline;
	t_raycast		raycast;

	ft_bzero(&drawline, sizeof(t_drawline));
	if (!transform_vertex(&raycast, e->player,
		(t_vtx){vertex.x + p.anglesin, vertex.y - p.anglecos},
		(t_vtx){vertex.x - p.anglesin, vertex.y + p.anglecos}))
		return ;
	raycast.neighbor = -1;
	acquire_limits(&env->engine, &raycast, (t_l_float){size.ceil
		, size.floor});
	render_loop_sprites(env, sprite, drawline, raycast);
}

/*
** Queue logic to render wall and add a new sector if it has a neighbour
*/

int			render_sector_edges(t_env *env, t_queue *q, int s)
{
	t_vtx		*vertex;
	t_engine	*e;
	t_raycast	ctn;
	int			end;
	int			start;

	e = &env->engine;
	vertex = q->sect->vertex;
	if (transform_vertex(&ctn, e->player, vertex[s], vertex[s + 1]) == 0
		|| ctn.x1 >= ctn.x2 || ctn.x2 < q->now.sx1 || ctn.x1 > q->now.sx2)
		return (0);
	ctn.neighbor = q->sect->neighbors[s];
	ctn.sprite = env->world.surfaces.walls[0].sprite;
	acquire_limits(e, &ctn, (t_l_float){q->sect->ceil, q->sect->floor});
	start = (int)fmax(ctn.x1, q->now.sx1);
	end = (int)fmin(ctn.x2, q->now.sx2);
	ctn.x = start;
	ctn.li_sector = (t_l_int){q->sect->ceil, q->sect->floor};
	while (ctn.x <= end)
	{
		render_wall(env, ctn, &q->ytop[ctn.x], &q->ybottom[ctn.x]);
		++ctn.x;
	}
	schedule_queue(q, ctn, start, end);
	return (1);
}

void		render_sector(t_env *env, t_queue *queue)
{
	int	s;

	s = -1;
	while (++s < (int)queue->sect->npoints)
		render_sector_edges(env, queue, s);
	render_object(env, queue);
	render_enemies(env, queue);
	if (env->player.inventory.current->is_full)
		env->player.inventory.current->ref == 3
		? render_bullet(env, env->engine.player, env->player.shot, queue)
		: 0;
}
