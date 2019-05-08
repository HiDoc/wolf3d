/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:02 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 20:22:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	bot_is_moving(t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->walk_frame / FRAME_RATIO < e->time_walk && !enemy->hit_frame)
	{
		enemy->sprite = e->walk[enemy->walk_frame / FRAME_RATIO];
		enemy->walk_frame++;
	}
	else
		enemy->walk_frame = 0;
}

void	bot_is_hit(t_character *e, t_wrap_enmy *enemy)
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

void	bot_is_shootin(t_character *e, t_wrap_enmy *enemy)
{
	if (enemy->shoot_frame / FRAME_RATIO < e->time_shoot)
	{
		enemy->sprite = e->shoot[enemy->shoot_frame / FRAME_RATIO];
		enemy->shoot_frame++;
	}
	else
		enemy->shoot_frame = 0;
}

void	bot_is_dying(t_env *e, t_character *ref, t_wrap_enmy *en)
{
	int	temp;

	if (en->die_frame < ref->time_death)
	{
		en->a.is_shooting = 0;
		en->a.is_shot = 0;
		en->walk_frame = 0;
		en->die_frame++;
	}
	else
	{
		temp = e->stats.data[I_KTOGO];
		en->a.is_alive = 0;
		en->a.is_dying = 0;
		(en->ref != BOSS) ? e->stats.data[I_KTOGO]-- : 0;
		if (temp && !e->stats.data[I_KTOGO] && e->curr_lvl < e->nb_levels)
			e->engine.player.sound.end_level = 1;
		if (temp && !e->stats.data[I_KTOGO] && e->curr_lvl == e->nb_levels - 1)
			e->finish = 1;
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
