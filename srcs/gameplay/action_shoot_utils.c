/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_shoot_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:59:19 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 13:03:20 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
