/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:27:29 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 21:24:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemy_set(t_character *enemy, t_edge size)
{
	long	ref;

	ref = enemy->ref;
	enemy->type = (ref & 0xF);
	enemy->damage = ((ref >> (1 << 2)) & 0xFF);
	enemy->tshoot_between = ((ref >> (3 << 2)) & 0xFF);
	enemy->salve_shoot = ((ref >> (5 << 2)) & 0xFF);
	enemy->health = ((ref >> (7 << 2)) & 0xFF);
	enemy->shield = ((ref >> (9 << 2)) & 0xFF);
	enemy->size = (t_l_float){size.v1.x, size.v1.y};
	enemy->deathsize = (t_l_float){size.v2.x, size.v2.y};
}

void	init_enemies(t_env *env)
{
	env->world.enemies[0].ref = 0xa64640809140;
	enemy_set(&env->world.enemies[0], (t_edge){{0, 10}, {6, 5}});
}
