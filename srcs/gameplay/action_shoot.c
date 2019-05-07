/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:08:23 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 23:38:40 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Collision detection.
** Check if the bot is crossing an edge and if this edge has a neighbour
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

void	gameover(t_env *e)
{
	t_inventory	*inv;

	inv = &e->player.inventory;
	e->player.health = 0;
	e->stats.data[I_DEATHS]++;
	e->engine.player.sound.dead = 1;
	e->menu.status.gameover = 1;
	e->stats.data[I_KTOGO] = 0;
	ft_bzero(inv, sizeof(t_inventory));
	inv->weapons[FIST].is_full = 1;
	inv->weapons[FIST].ref = FIST;
	inv->weapons[FIST].ammo[0] = e->world.armory[FIST].ammo_current;
	inv->weapons[FIST].ammo[1] = e->world.armory[FIST].ammo_magazine;
	inv->weapons[FIST].ammo[2] = e->world.armory[FIST].damage;
	set_current_wpn(e, inv, FIST);
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

void	bot_life(t_env *e, t_wrap_enmy *en, int damage, int wpn)
{
	en->brain.health -= damage;
	if (en->brain.health < 1)
	{
		en->a.is_dying = 1;
		en->a.is_alive = 0;
		en->player.sound.dead = 1;
		e->stats.data[I_KILLS]++;
		e->stats.data[I_K_MAGNUM + wpn]++;
	}
	en->a.is_shot = 1;
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

void	check_isimpact(t_env *e, t_impact *b, float vel, int damage)
{
	t_player	*p;
	t_vtx		move;
	t_sector	*sector;

	move = (t_vtx){0.f, 0.f};
	p = &b->position;
	sector = &e->engine.sectors[e->engine.player.sector];
	move = add_vertex(move, (t_vtx){p->anglecos, p->anglesin});
	p->velocity.x = p->velocity.x * (1 - vel) + move.x * vel;
	p->velocity.y = p->velocity.y * (1 - vel) + move.y * vel;
	if (bot_wall_collision(p, sector))
	{
		b->is_alive = 0;
		b->is_shooting = 0;
	}
	impact_bot(e, b, sector, damage);
	if (b->is_shooting)
	{
		p->where.x += p->velocity.x;
		p->where.y += p->velocity.y;
	}
	else
		ft_bzero(b, sizeof(t_impact));
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

void	new_bullet(t_impact *new, t_player *p, float velocity)
{
	ft_bzero(new, sizeof(t_impact));
	new->position.origin = p->where;
	new->position.where = p->where;
	new->position.anglecos = p->anglecos * velocity;
	new->position.anglesin = p->anglesin * velocity;
	new->position.sprite = p->sprite;
	new->is_shooting = 1;
	new->is_alive = 1;
	new->position.whereto = p->whereto;
}

int		pl_new_kill(t_env *env, t_player *p, t_character *player)
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
				return (1);
			}
			i++;
		}
	}
	return (1);
}
