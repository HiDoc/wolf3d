/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:30:02 by abaille           #+#    #+#             */
/*   Updated: 2019/04/03 20:42:26 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	bot_is_moving(t_wrap_enmy *enemy)
{
	if (enemy->walk_frame < 10)
	{
		enemy->sprite = enemy->walk[enemy->walk_trig];
		enemy->walk_frame++;
	}
	else
	{
		enemy->walk_trig = !enemy->walk_trig ? 1 : 0;
		enemy->walk_frame = 0;
	}
	return (1);
}

int	bot_is_hit(t_wrap_enmy *enemy)
{
	if (enemy->hit_frame < 30)
	{
		enemy->sprite = enemy->is_hit;
		enemy->is_shooting = 0;
		enemy->hit_frame++;
	}
	else
	{
		enemy->hit_frame = 0;
		enemy->is_shot = 0;
	}
	return (1);
}

int	bot_is_shootin(t_wrap_enmy *enemy)
{
	if (enemy->shoot_frame < 10)
	{
		enemy->sprite = enemy->shootin[enemy->walk_trig];
		enemy->shoot_frame++;
	}
	else
	{
		enemy->shoot_frame = 0;
		enemy->walk_trig = !enemy->walk_trig ? 1 : 0;
	}

	return (1);
}

int	enemies_frames(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;

	(void)env;
	enemy = sector->head_enemy;
	while (enemy)
	{
		if (enemy->is_shooting)
			bot_is_shootin(enemy);
		else
			bot_is_moving(enemy);
		if (enemy->is_shot)
			bot_is_hit(enemy);
		if (!enemy->is_alive)
			enemy->sprite = enemy->dead;
		enemy = enemy->next;
	}
	return (1);
}