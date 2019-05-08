/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:44:22 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 20:17:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wrap_enmy	*new_enemy(t_env *env, t_vtx v, int ref)
{
	t_character	*renemy;
	t_wrap_enmy	*new;

	new = ft_memalloc(sizeof(t_wrap_enmy));
	ft_bzero(new, sizeof(t_wrap_enmy));
	renemy = &env->world.enemies[ref];
	new->ref = ref;
	new->player.where = (t_vctr){v.x, v.y, 0};
	new->player.origin = (t_vctr){v.x, v.y, 0};
	new->player.velocity = (t_vctr){0, 0, 0};
	new->brain = renemy->brain;
	new->a.is_alive = 1;
	new->damage = renemy->damage;
	new->frame = renemy->cadence_shoot;
	new->player.nb_shot = 35;
	new->next = NULL;
	return (new);
}

int	fill_enemies_sector(t_env *env, t_sector *sector, t_vtx v, int ref)
{
	t_wrap_enmy	*iter;

	iter = NULL;
	env->stats.data[I_KTOGO]++;
	if (sector->head_enemy == NULL)
		return ((sector->head_enemy = new_enemy(env, v, ref)) ? 1 : 0);
	iter = sector->head_enemy;
	while (iter->next != NULL)
		iter = iter->next;
	return ((iter->next = new_enemy(env, v, ref)) ? 1 : 0);
}
