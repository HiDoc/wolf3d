/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:53:39 by abaille           #+#    #+#             */
/*   Updated: 2019/03/29 16:15:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	enemy_mask(long ref, int pos)
{
	return (((ref >> (pos << 2)) & 0xFF));
}

int	enemy_set(t_character *enemy)
{
	long	ref;

	ref = enemy->ref;
	enemy->type = (ref & 0xF);
	enemy->damage = enemy_mask(ref, 1);
	enemy->tshoot_between = enemy_mask(ref, 3);
	enemy->salve_shoot = enemy_mask(ref, 5);
	enemy->health = enemy_mask(ref, 7);
	enemy->shield = enemy_mask(ref, 9);
	return (1);
}

int	init_enemies(t_env *env)
{
	env->world.enemies[0].ref = 0xa64640809140;
	enemy_set(&env->world.enemies[0]);
	return (1);
}