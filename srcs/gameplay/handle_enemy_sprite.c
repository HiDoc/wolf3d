/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:02 by abaille           #+#    #+#             */
/*   Updated: 2019/04/11 02:57:19 by abaille          ###   ########.fr       */
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
		enemy->sprite = e->ref == LOSTSOUL ? e->shoot[0] : e->death[0];
		enemy->is_shooting = 0;
		enemy->is_alerted = 0;
		enemy->has_detected = 0;
		enemy->close_seen = 0;
		enemy->hit_frame++;
	}
	else
	{
		enemy->hit_frame = 0;
		enemy->is_shot = 0;
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

static void	bot_is_dying(t_env *env, t_character *e, t_wrap_enmy *enemy, t_sector *s)
{
	if (enemy->die_frame / FRAME_RATIO < e->time_death)
	{
		enemy->is_shooting = 0;
		enemy->is_shot = 0;
		enemy->walk_frame = 0;
		enemy->sprite = e->death[enemy->die_frame / FRAME_RATIO];
		enemy->die_frame++;
	}
	else
	{
		enemy->is_alive = 0;
		enemy->is_dying = 0;
		env->stats.data[I_KTOGO]--;
		s->nb_enemies--;
	}
}

void	enemies_frames(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;
	t_character	*e;
	(void)env;

	enemy = sector->head_enemy;
	while (enemy)
	{
		e = &env->world.enemies[enemy->ref];
		if (enemy->is_dying)
			bot_is_dying(env, e, enemy, sector);
		else
		{
			if (enemy->is_shooting)
				bot_is_shootin(e, enemy);
			else
				bot_is_moving(e, enemy);
			if (enemy->is_shot)
				bot_is_hit(e, enemy);
		}
		if (!enemy->is_alive && !enemy->is_dying)
			enemy->sprite = e->death[e->time_death - 1];
		enemy = enemy->next;
	}
}