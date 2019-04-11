/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:44:22 by abaille           #+#    #+#             */
/*   Updated: 2019/04/11 00:25:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wrap_enmy	*new_enemy(t_env *env, t_vtx v, int ref)
{
	t_character	*renemy;
	t_wrap_enmy	*new;
	int			i;

	i = -1;
	new = ft_memalloc(sizeof(t_wrap_enmy));
	ft_bzero(new, sizeof(t_wrap_enmy));
	renemy = &env->world.enemies[ref];
	new->ref = ref;
	new->player.where = (t_vctr){v.x, v.y, 0};
	new->player.origin = (t_vctr){v.x, v.y, 0};
	new->player.velocity = (t_vctr){0, 0, 0};
	new->brain = renemy->brain;
	new->is_alive = 1;
	new->damage = renemy->damage;
	new->frame = renemy->cadence_shoot;
	new->shot = ft_memalloc(sizeof(t_impact) * BOT_NB_SHOT);
	while (++i < BOT_NB_SHOT)
		ft_bzero(&new->shot[i], sizeof(t_impact));
	new->player.nb_shot = BOT_NB_SHOT;
	new->next = NULL;
	return (new);
}

int	fill_enemies_sector(t_env *env, t_sector *sector, t_vtx v, int ref)
{
	t_wrap_enmy	*iter;

	iter = NULL;
	env->stats.data[I_KTOGO]++;
	if (sector->head_enemy == NULL)
		return ((sector->head_enemy = new_enemy(env, v, ref)) ? sector->nb_enemies++ : 0);
	iter = sector->head_enemy;
	while (iter->next != NULL)
		iter = iter->next;
	return ((iter->next = new_enemy(env, v, ref)) ? sector->nb_enemies++ : 0);
}
