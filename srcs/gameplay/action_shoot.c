/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:08:23 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 13:01:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		bot_wall_collision(t_player *bot, t_sector *sect)
{
	const t_vtx		vertex = {bot->where.x, bot->where.y};
	const t_vtx		*vert = sect->vertex;
	t_vtx			dest;
	t_edge			wall;
	int				s;

	s = -1;
	dest = (t_vtx){bot->velocity.x, bot->velocity.y};
	while (++s < (int)sect->npoints)
	{
		wall = (t_edge){vert[s], vert[s + 1]};
		if (is_crossing(vertex, dest, vert, s))
			return (1);
		if (sect->neighbors[s] >= 0 && is_crossing(vertex, dest, vert, s))
			return (1);
	}
	return (0);
}

void	impact_player(t_env *env, t_impact *shot, t_vtx player, int damage)
{
	t_vtx	where;
	int		health;

	where = (t_vtx){shot->position.where.x, shot->position.where.y};
	if (dist_vertex(where, player) < 5)
	{
		health = env->player.health;
		env->player.shield = (env->player.shield > 0)
			? env->player.shield -= damage : 0;
		!env->player.shield ? env->player.health -= damage : 0;
		if (env->player.health <= 0)
			gameover(env);
		else if (env->player.health <= 50 && health > env->player.health
		&& !env->engine.player.sound.lowlife)
			env->engine.player.sound.lowlife = 1;
		else
			env->engine.player.sound.hit++;
		shot->is_shooting = 0;
		shot->is_alive = 0;
	}
}

void	impact_bot(t_env *e, t_impact *shot, t_sector *sector, int damage)
{
	t_wrap_enmy	*en;
	t_vtx		f;
	t_vtx		scd;
	t_weapon	*rwpn;
	int			wpn;

	en = sector->head_enemy;
	wpn = e->player.inventory.current->ref;
	rwpn = &e->world.armory[wpn];
	while (en && shot->is_shooting)
	{
		f = (t_vtx){shot->position.where.x, shot->position.where.y};
		scd = (t_vtx){en->player.where.x, en->player.where.y};
		if (en->a.is_alive && dist_vertex(f, scd) <= rwpn->ray)
		{
			bot_life(e, en, damage, wpn);
			shot->is_shooting = rwpn->ray > 1 ? shot->is_shooting + 1 : 0;
			shot->is_alive = rwpn->ray > 1 ? shot->is_alive + 1 : 0;
		}
		en = en->next;
	}
	shot->is_alive = shot->is_alive > 1 ? 0 : 1;
	shot->is_shooting = shot->is_shooting > 1 ? 0 : 1;
}

void	player_bullet(t_env *env, t_character *p, int damage)
{
	int			i;
	t_weapon	*rwpn;

	i = 0;
	rwpn = &env->world.armory[env->player.inventory.current->ref];
	while (i < NB_SHOT)
	{
		if (p->shot[i].is_shooting)
		{
			if (dist_vertex((t_vtx){p->shot[i].position.origin.x,
			p->shot[i].position.origin.y}, (t_vtx){p->shot[i].position.where.x,
			p->shot[i].position.where.y}) <= rwpn->scop)
				check_isimpact(env, &p->shot[i], rwpn->velocity, damage);
			else
				ft_bzero(&p->shot[i], sizeof(t_impact));
		}
		i++;
	}
}

void	pl_new_kill(t_env *env, t_player *p, t_character *player)
{
	int			i;
	t_weapon	*rwpn;

	i = 0;
	rwpn = &env->world.armory[player->inventory.current->ref];
	if (player->actions.is_shooting)
	{
		while (i < NB_SHOT)
		{
			if (!player->shot[i].is_alive)
			{
				new_bullet(&player->shot[i], p, rwpn->velocity);
				break ;
			}
			i++;
		}
	}
}
