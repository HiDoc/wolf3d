/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:44:22 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 21:38:50 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wrap_enmy	*new_enemy(t_env *env, t_vtx v, int ref)
{
	t_character	*renemy;
	t_wrap_enmy	*new;
	int			i;

	i = -1;
	if (!(new = malloc(sizeof(t_wrap_enmy))))
		return (NULL);
	ft_bzero(new, sizeof(new));
	renemy = &env->world.enemies[ref];
	new->player.where = (t_vctr){v.x, v.y, 0};
	new->player.origin = (t_vctr){v.x, v.y, 0};
	new->player.velocity = (t_vctr){0, 0, 0};
	new->player.sprite = env->player.bullet;
	new->walk[0] = renemy->sprites[0];
	new->walk[1] = renemy->sprites[1];
	new->shootin[0] = renemy->sprites[2];
	new->shootin[1] = renemy->sprites[3];
	new->is_hit = renemy->sprites[4];
	new->dead = renemy->sprites[5];
	new->sprite = renemy->sprites[0];
	new->walk_trig = 0;
	new->is_shot = 0;
	new->frame = 0;
	new->shoot_frame = 0;
	new->ref = ref;
	new->health = renemy->health;
	new->shield = renemy->shield;
	new->damage = renemy->damage;
	new->is_alive = 1;
	if (!(new->shot = malloc(sizeof(t_impact) * BOT_NB_SHOT)))
		return (NULL);
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
	if (sector->head_enemy == NULL)
	{
		if (!(sector->head_enemy = new_enemy(env, v, ref)))
			return (0);
	}
	else
	{
		iter = sector->head_enemy;
		while (iter->next != NULL)
			iter = iter->next;
		if (!(iter->next = new_enemy(env, v, ref)))
			return (0);
	}
	sector->nb_enemies++;
	return (1);
}
