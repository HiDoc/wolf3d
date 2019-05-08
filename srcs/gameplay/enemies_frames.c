/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_frames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:01:29 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 23:02:11 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemies_frames(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;
	t_character	*e;

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
		sound_enemies(env, enemy, (t_vtx){env->engine.player.where.x,
			env->engine.player.where.y});
		enemy = enemy->next;
	}
}
