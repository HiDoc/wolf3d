/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:11 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 00:30:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		give_life(void *e, t_wrap_inv *object)
{
	t_env	*env;
	int		*data;
	int		max;

	env = (t_env*)e;
	data = object->current->ref == HEALTH
	? &env->player.health : &env->player.shield;
	max = object->current->ref == HEALTH
	? env->player.max_health : env->player.max_shield;
	if (*data < max)
	{
		*data += 50;
		if (*data > max)
			*data = max;
		object->nb_stack > 0 ? object->nb_stack-- : 0;
		object->is_used = object->nb_stack < 1 ? 1 : 0;
		object->is_used ? drop_object(env, object) : 0;
		return (0);
	}
	return (1);
}

int	give_ammo(void *e, t_wrap_inv *obj)
{
	t_env		*env;
	int			stack;
	int			ammo;
	t_wrap_wpn	*wpn;
	t_weapon	*wpn_ref;

	env = (t_env*)e;
	if (obj)
	{
		ammo = obj->current->ref * 10;
		wpn = &env->player.inventory.weapons[obj->current->ref - 2];
		stack = *wpn->ammo_current + *wpn->ammo_magazine;
		wpn_ref = &env->world.armory[obj->current->ref - 2];
		if (wpn && stack < wpn_ref->ammo_curr_max + wpn_ref->ammo_mag_max)
		{
			ammo -= wpn_ref->ammo_curr_max - *wpn->ammo_current;
			*wpn->ammo_current = wpn_ref->ammo_curr_max;
			*wpn->ammo_magazine += ammo;
			if (*wpn->ammo_magazine > wpn_ref->ammo_mag_max)
				*wpn->ammo_magazine = wpn_ref->ammo_mag_max;
			obj->nb_stack > 0 ? obj->nb_stack-- : 0;
			obj->is_used = obj->nb_stack < 1 ? 1 : 0;
			obj->is_used ? drop_object(env, obj) : 0;
			return (0);
		}
		return (wpn ? 9 : 10);
	}
	return (14);
}

int	give_jetpack(void *e, t_wrap_inv *obj)
{
	t_env	*env;

	env = (t_env*)e;
	if (obj)
	{
		env->player.actions.is_flying = !env->player.actions.is_flying;
		return (env->player.actions.is_flying ? 11 : 12);
	}
	return (13);
}