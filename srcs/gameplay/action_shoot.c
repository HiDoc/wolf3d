/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:08:23 by abaille           #+#    #+#             */
/*   Updated: 2019/04/02 01:28:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		new_bullet(t_impact *new, t_player *p, int i)
{
	new->position.origin = p->where;
	new->position.where = p->where;
	new->position.anglecos = p->anglecos * 0.7f;
	new->position.anglesin = p->anglesin * 0.7f;
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
void	impact_collision(t_impact *shot, t_sector *sect)
{
	const t_vtx		impact = {shot->position.where.x, shot->position.where.y};
	const t_vtx		*vert = sect->vertex;
	t_vtx			dest;
	t_edge			wall;
	int				s;

	s = -1;
	dest = (t_vtx){shot->position.velocity.x, shot->position.velocity.y};
	while (++s < (int)sect->npoints)
	{
		wall = (t_edge){vert[s], vert[s + 1]};
		if (is_crossing(impact, dest, vert, s))
		{
			if (sector_collision(impact, &dest, wall))
			{
				shot->is_shooting = 0;
				shot->is_alive = 0;
				printf("wall hit\n");
			}
		}
	}
}

void	impact_player(t_env *env, t_impact *shot, t_vtx player, int damage)
{
	t_vtx	where;

	where = (t_vtx){shot->position.where.x, shot->position.where.y};
	if (dist_vertex(where, player) < 1)
	{
		printf("shoot player\n");
		if (env->player.shield)
			env->player.shield -= damage;
		else
			env->player.health -= damage;
		if (env->player.health <= 10)
			env->player.health = 200;
		shot->is_shooting = 0;
	}
}

void	impact_bot(t_impact *shot, t_sector *sector, int damage)
{
	t_wrap_enmy	*enemy;
	t_vtx		first;
	t_vtx		scd;

	enemy = sector->head_enemy;
	while (enemy && shot->is_shooting)
	{
		first = (t_vtx){shot->position.where.x, shot->position.where.y};
		scd = (t_vtx){enemy->player.where.x, enemy->player.where.y};
		if (enemy->is_alive && dist_vertex(first, scd) < 1)
		{
			enemy->health -= damage;
			printf("vie bot : %i\n", enemy->health);
			if (enemy->health < 10)
				enemy->is_alive = 0;
			shot->is_shooting = 0;
			shot->is_alive = 0;
		}
		enemy = enemy->next;
	}
}

void	handle_bullets(t_env *env, t_impact **shot, int damage)
{
	t_vtx		move;
	int			i;
	t_sector	*sector;

	i = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	move = (t_vtx){0.f, 0.f};
	while (i < 12)
	{
		if (shot[i] && shot[i]->is_shooting)
		{
			move = add_vertex(move, (t_vtx){shot[i]->position.anglecos, shot[i]->position.anglesin});
			shot[i]->position.velocity.x = shot[i]->position.velocity.x * (1 - 0.7f) + move.x * 0.7f;
			shot[i]->position.velocity.y = shot[i]->position.velocity.y * (1 - 0.7f) + move.y * 0.7f;
			impact_collision(shot[i], sector);
			if (p == 'p')
				impact_bot(shot[i], sector, damage);
			else
				impact_player(env, shot[i], (t_vtx){env->engine.player.where.x,
				env->engine.player.where.y}, damage);
			if (shot[i]->is_shooting)
			{
				shot[i]->position.where.x += shot[i]->position.velocity.x;
				shot[i]->position.where.y += shot[i]->position.velocity.y;
			}
			else
				ft_bzero(shot[i], sizeof(t_impact));
		}
		i++;
	}
}

int		action_kill(int shooting, t_player *p, t_character *player)
{
	int			i;

	i = 0;
	if (shooting)
	{
		while (i < 12)
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