/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:02 by abaille           #+#    #+#             */
/*   Updated: 2019/05/02 13:43:23 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	bot_is_moving(t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->walk_frame / FRAME_RATIO < e->time_walk && !enemy->hit_frame)
	{
		enemy->sprite = e->walk[enemy->walk_frame / FRAME_RATIO];
		enemy->walk_frame++;
	}
	else
		enemy->walk_frame = 0;
}

static void	bot_is_hit(t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->hit_frame / FRAME_RATIO < 10)
	{
		enemy->sprite = (e->ref == LOSTSOUL) ? e->shoot[0] : e->death[0];
		enemy->a.is_shooting = 0;
		enemy->a.is_alerted = 0;
		enemy->a.has_detected = 0;
		enemy->a.close_seen = 0;
		enemy->hit_frame++;
	}
	else
	{
		enemy->hit_frame = 0;
		enemy->a.is_shot = 0;
	}
}

static void	bot_is_shootin(t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->shoot_frame / FRAME_RATIO < e->time_shoot)
	{
		enemy->sprite = e->shoot[enemy->shoot_frame / FRAME_RATIO];
		enemy->shoot_frame++;
	}
	else
		enemy->shoot_frame = 0;
}

static void	bot_is_dying(t_env *env, t_character *e,
	t_wrap_enmy *enemy, t_sector *s)
{
	int	temp;

	if (enemy->die_frame / FRAME_RATIO < e->time_death)
	{
		enemy->a.is_shooting = 0;
		enemy->a.is_shot = 0;
		enemy->walk_frame = 0;
		enemy->die_frame++;
	}
	else
	{
		temp = env->stats.data[I_KTOGO];
		enemy->a.is_alive = 0;
		enemy->a.is_dying = 0;
		(enemy->ref != BOSS) ? env->stats.data[I_KTOGO]-- : 0;
		(temp && !env->stats.data[I_KTOGO])
			? env->engine.player.sound.end_level = 1 : 0;
		s->nb_enemies--;
	}
}


void	set_bossmidlife(t_env *e, t_wrap_enmy *en)
{
	t_character	*renemy;


	renemy = &e->world.enemies[BOSS_MIDL];
	en->ref = renemy->type;
	en->brain = renemy->brain;
	en->a.is_alive = 1;
	en->damage = renemy->damage;
	en->frame = renemy->cadence_shoot;
}


void	enemies_frames(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;
	t_character	*e;
	t_vtx		p;

	p = (t_vtx){env->engine.player.where.x, env->engine.player.where.y};
	enemy = sector->head_enemy;
	while (enemy)
	{
		e = &env->world.enemies[enemy->ref];
		if (!enemy->a.is_alive && !enemy->a.is_dying)
			enemy->sprite = e->death[e->time_death - 1];
		else if (enemy->a.is_dying)
			bot_is_dying(env, e, enemy, sector);
		else if (enemy->a.is_shooting)
			bot_is_shootin(e, enemy);
		else
			bot_is_moving(e, enemy);
		if (enemy->a.is_shot)
			bot_is_hit(e, enemy);
		if (enemy->ref == BOSS && !enemy->a.is_alive && !enemy->a.is_dying)
			set_bossmidlife(env, enemy);
		sound_enemies(env, enemy, p);
		enemy = enemy->next;
	}
}