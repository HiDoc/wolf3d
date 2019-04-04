/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:08:23 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 03:19:38 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		new_bullet(t_impact *new, t_player *p, int i)
{
	new->position.origin = p->where;
	new->position.where = p->where;
	new->position.anglecos = p->anglecos * 1.9f;
	new->position.anglesin = p->anglesin * 1.9f;
	new->position.sprite = p->sprite;
	new->is_shooting = 1;
	new->is_alive = 1;
	new->ref = i;
	return (1);
}

/*
** Collision detection.
** Check if the player is crossing an edge and if this edge has a neighbour
*/
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

	where = (t_vtx){shot->position.where.x, shot->position.where.y};
	if (dist_vertex(where, player) < 1)
	{
		if (env->player.shield)
			env->player.shield -= damage;
		else
			env->player.health -= damage;
		if (env->player.health <= 10)
			env->player.health = 200;
		shot->is_shooting = 0;
		shot->is_alive = 0;
	}
}

void	impact_bot(t_env *env, t_impact *shot, t_sector *sector, int damage)
{
	t_wrap_enmy	*enemy;
	t_vtx		first;
	t_vtx		scd;
	t_weapon	*rwpn;


	enemy = sector->head_enemy;
	rwpn = &env->world.armory[env->player.inventory.current->current->ref];
	while (enemy && shot->is_shooting)
	{
		first = (t_vtx){shot->position.where.x, shot->position.where.y};
		scd = (t_vtx){enemy->player.where.x, enemy->player.where.y};
		if (enemy->is_alive && dist_vertex(first, scd) <= rwpn->ray)
		{
			enemy->health -= damage;
			printf("vie bot : %i\n", enemy->health);
			if (enemy->health < 10)
			{
				enemy->is_alive = 0;
				env->stats.k_enemies++;
				// env->stats.k_wpn[wpn]++;
			}
			enemy->is_shot = 1;
			shot->is_shooting = 0;
			shot->is_alive = rwpn->ray > 1 ? shot->is_alive + 1 : 0;
		}
		enemy = enemy->next;
	}
	shot->is_alive = shot->is_alive > 1 ? 0 : 1;
}

void	player_bullet(t_env *env, t_character *p, int damage)
{
	t_vtx		move;
	int			i;
	t_sector	*sector;
	t_weapon	*rwpn;

	i = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	move = (t_vtx){0.f, 0.f};
	rwpn = &env->world.armory[env->player.inventory.current->current->ref];
	while (i < PLYR_NB_SHOT)
	{
		if (p->shot[i].is_shooting)
		{
			if (dist_vertex((t_vtx){p->shot[i].position.origin.x,
			p->shot[i].position.origin.y}, (t_vtx){p->shot[i].position.where.x,
			p->shot[i].position.where.y}) <= rwpn->scop)
			{
				move = add_vertex(move, (t_vtx){p->shot[i].position.anglecos, p->shot[i].position.anglesin});
				p->shot[i].position.velocity.x = p->shot[i].position.velocity.x * (1 - 1.9f) + move.x * 1.9f;
				p->shot[i].position.velocity.y = p->shot[i].position.velocity.y * (1 - 1.9f) + move.y * 1.9f;
				if (bot_wall_collision(&p->shot[i].position, sector))
				{
					p->shot[i].is_alive = 0;
					p->shot[i].is_shooting = 0;
				}
				impact_bot(env, &p->shot[i], sector, damage);
				if (p->shot[i].is_shooting)
				{
					p->shot[i].position.where.x += p->shot[i].position.velocity.x;
					p->shot[i].position.where.y += p->shot[i].position.velocity.y;
				}
				else
					ft_bzero(&p->shot[i], sizeof(t_impact));
			}
			else
				ft_bzero(&p->shot[i], sizeof(t_impact));
		}
		i++;
	}
}

int		pl_new_kill(int shooting, t_player *p, t_character *player)
{
	int	i;

	i = 0;
	if (shooting)
	{
		while (i < p->nb_shot)
		{
			if (!player->shot[i].is_alive)
			{
				new_bullet(&player->shot[i], p, i);
				return (1);
			}
			i++;
		}
		ft_bzero(&player->shot[0], sizeof(t_impact));
		new_bullet(&player->shot[0], p, 0);
		ft_bzero(&player->shot[1], sizeof(t_impact));
	}
	return (1);
}