/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:02 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 03:59:53 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	bot_is_moving(t_env *env, t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->walk_frame / FRAME_RATIO < e->time_walk && !enemy->hit_frame)
	{
		// enemy->walk_frame == 0
		// ? Mix_PlayChannel(-1, env->sound.e_voice[enemy->ref], 0) : 0;
		enemy->sprite = e->walk[enemy->walk_frame / FRAME_RATIO];
		enemy->walk_frame++;
	}
	else
		enemy->walk_frame = 0;
}

static void	bot_is_hit(t_env *env, t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->hit_frame / FRAME_RATIO < 10)
	{
		enemy->hit_frame == 0
		? Mix_PlayChannel(-1, env->sound.e_voice[enemy->ref], 0) : 0;
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

static void	bot_is_shootin(t_env *env, t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->shoot_frame / FRAME_RATIO < e->time_shoot)
	{
		enemy->shoot_frame == 0
		? Mix_PlayChannel(-1, env->sound.e_shot[enemy->ref], 0) : 0;
		enemy->sprite = e->shoot[enemy->shoot_frame / FRAME_RATIO];
		enemy->shoot_frame++;
	}
	else
		enemy->shoot_frame = 0;
}

static void	bot_is_dying(t_env *env, t_character *e, t_wrap_enmy *enemy, t_sector *s)
{
	int	temp;

	if (enemy->die_frame / FRAME_RATIO < e->time_death)
	{
		enemy->is_shooting = 0;
		enemy->is_shot = 0;
		enemy->walk_frame = 0;
		enemy->player.sound.dead
		? Mix_PlayChannel(-1, env->sound.e_death[enemy->ref], 0) : 0;
		enemy->sprite = e->death[enemy->die_frame / FRAME_RATIO];
		enemy->player.sound.dead = 0;
		enemy->die_frame++;
	}
	else
	{
		temp = env->stats.data[I_KTOGO];
		enemy->is_alive = 0;
		enemy->is_dying = 0;
		env->stats.data[I_KTOGO]--;
		temp && !env->stats.data[I_KTOGO]
		? Mix_PlayChannel(-1, env->sound.s_effect[EFCT_OP_BIGDOOR], 0) : 0;
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
				bot_is_shootin(env, e, enemy);
			else
				bot_is_moving(env, e, enemy);
			if (enemy->is_shot)
				bot_is_hit(env, e, enemy);
		}
		if (!enemy->is_alive && !enemy->is_dying)
			enemy->sprite = e->death[e->time_death - 1];
		enemy = enemy->next;
	}
}