/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 15:32:00 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			bot_new_kill(int shooting, t_player *p, t_wrap_enmy *enemy)
{
	int	i;

	i = -1;
	if (shooting)
	{
		while (++i < NB_SHOT)
		{
			if (!enemy->shot[i].is_alive)
			{
				new_bullet(&enemy->shot[i], p, BOT_V_SHOT);
				return (1);
			}
		}
	}
	return (1);
}

static void	bot_shoot_cadence(t_env *env, t_wrap_enmy *e, t_player p)
{
	t_player	new_look;

	if (e->frame >= env->world.enemies[e->ref].cadence_shoot)
	{
		(void)p;
		new_look = bot_angle(e->player, p);
		bot_new_kill(e->a.is_shooting, &new_look, e);
		e->player.sound.shootin = 1;
		e->frame = 0;
	}
	else
		e->frame++;
}

int			bullet_hit(t_env *e, t_impact *s, t_wrap_enmy *en, t_sector *sector)
{
	t_player	*p;
	t_vtx		move;

	p = &s->position;
	if (s->is_shooting && dist_vertex((t_vtx){p->origin.x,
		p->origin.y}, (t_vtx){p->where.x, p->where.y}) < en->brain.scop)
	{
		move = bot_orientation(&s->position, p->whereto, BOT_V_SHOT);
		p->velocity.x = p->velocity.x * (1 - BOT_V_SHOT) + move.x * BOT_V_SHOT;
		p->velocity.y = p->velocity.y * (1 - BOT_V_SHOT) + move.y * BOT_V_SHOT;
		if (bot_wall_collision(&s->position, sector))
		{
			s->is_alive = 0;
			s->is_shooting = 0;
		}
		impact_player(e, s, (t_vtx){e->engine.player.where.x,
		e->engine.player.where.y}, en->damage);
		if (s->is_shooting)
		{
			p->where.x += p->velocity.x;
			p->where.y += p->velocity.y;
		}
		return (1);
	}
	return (0);
}

static void	bot_bullet(t_env *env, t_wrap_enmy *e)
{
	int			i;
	int			shot_has_hit;
	t_vtx		move;
	t_sector	*sector;
	t_player	*p;

	i = 0;
	move = (t_vtx){0.f, 0.f};
	sector = &env->engine.sectors[env->engine.player.sector];
	while (i < NB_SHOT)
	{
		p = &e->shot[i].position;
		shot_has_hit = bullet_hit(env, &e->shot[i], e, sector);
		if (shot_has_hit && !e->shot[i].is_shooting)
		{
			e->ref == LOSTSOUL && e->a.is_alive ? e->a.is_dying = 1 : 0;
			ft_bzero(&e->shot[i], sizeof(t_impact));
		}
		else if (!shot_has_hit && e->shot[i].is_shooting)
		{
			e->shot[i].is_shooting = 0;
			e->shot[i].is_alive = 0;
		}
		i++;
	}
}

void		bot_action(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;
	t_vtx		p;

	p = (t_vtx){env->engine.player.where.x, env->engine.player.where.y};
	(void)env;
	enemy = sector->head_enemy;
	while (enemy)
	{
		if (enemy->a.is_alive && !enemy->a.is_dying && !enemy->a.is_shot)
		{
			bot_status(env, p, enemy, env->sdl.keycodes);
			if (enemy->next && enemy->next->a.is_alive)
				bot_check_friend(enemy, enemy->next);
			if (enemy->a.is_shooting)
				bot_shoot_cadence(env, enemy, env->engine.player);
			bot_bullet(env, enemy);
		}
		enemy = enemy->next;
	}
}
