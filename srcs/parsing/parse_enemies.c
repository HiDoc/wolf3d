/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:44:22 by abaille           #+#    #+#             */
/*   Updated: 2019/03/30 16:33:28 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wrap_enmy	*new_enemy(t_env *env, t_vtx v, int ref)
{
	t_character	*renemy;
	t_wrap_enmy	*new;

	if (!(new = malloc(sizeof(t_wrap_enmy))))
		return (NULL);
	ft_bzero(new, sizeof(new));
	renemy = &env->world.enemies[ref];
	new->where = v;
	new->origin = v;
	new->velocity = (t_vtx){0, 0};
	new->ref = ref;
	new->health = renemy->health;
	new->shield = renemy->shield;
	new->damage = renemy->damage;
	new->is_alive = 1;
	new->next = NULL;
	return (new);
}

int	fill_enemies_sector(t_env *env, t_sector *sector, t_vtx v, int ref)
{
	t_wrap_enmy	*iter;

	iter = NULL;
	if (sector->head_enemy == NULL)
		sector->head_enemy = new_enemy(env, v, ref);
	else
	{
		iter = sector->head_enemy;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_enemy(env, v, ref);
	}
	return (1);
}
