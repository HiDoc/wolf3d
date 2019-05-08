/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:52:08 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 22:34:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	render_object(t_env *env, t_queue *queue)
{
	const t_object	*ctn = env->world.objects;
	const int		gem = WORLD_NB_CSMBLE + WORLD_NB_GEMS;
	t_wrap_sect		*object;
	int				ref;
	t_vtx			p;

	p = (t_vtx){env->engine.player.where.x, env->engine.player.where.y};
	object = queue->sect->head_object;
	while (object)
	{
		if (!object->is_picked)
		{
			object->is_pickable = (dist_vertex(p, object->vertex) < 5);
			ref = object->ref + ((object->is_wpn) ? gem : 0);
			render_sprites(env, ctn[ref].sprite,
				(t_vctr){object->vertex.x, object->vertex.y, 0},
				(t_l_float){queue->sect->floor + ctn[ref].size.ceil,
				queue->sect->floor + ctn[ref].size.floor});
			draw_pick_infos(env, object, ref);
		}
		object = object->next;
	}
}

void	render_bullet(t_env *env, t_player p, t_impact *shot, t_queue *q)
{
	int				i;

	i = 0;
	while (i < NB_SHOT)
	{
		render_sprites(env, p.sprite, shot[i].position.where,
			(t_l_float){q->sect->floor + 5, q->sect->floor + 0});
		i++;
	}
}

void	render_enemies(t_env *env, t_queue *q)
{
	t_wrap_enmy		*en;
	t_l_float		size;

	en = q->sect->head_enemy;
	while (en)
	{
		size = (t_l_float){en->brain.size.ceil + q->sect->floor,
			q->sect->floor + en->brain.size.floor};
		render_sprites(env, en->sprite, en->player.where, size);
		en = en->next;
	}
}
