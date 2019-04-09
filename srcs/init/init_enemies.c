/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:27:29 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 14:27:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_enemies(t_env *env)
{
	t_character *enemy;
	long		ref;

	ref = 0;
	enemy = &env->world.enemies[0];
	enemy->ref = 0xa64640809140;
	enemy->type = (ref & 0xF);
	enemy->damage = ((ref >> (1 << 2)) & 0xFF);
	enemy->tshoot_between = ((ref >> (3 << 2)) & 0xFF);
	enemy->salve_shoot = ((ref >> (5 << 2)) & 0xFF);
	enemy->health = ((ref >> (7 << 2)) & 0xFF);
	enemy->shield = ((ref >> (9 << 2)) & 0xFF);
}
