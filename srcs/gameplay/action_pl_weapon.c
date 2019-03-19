/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:32 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 12:16:09 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_weapon_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
	{
		if (env->player.inventory.weapons[i].current != NULL)
		{
			if (ref == env->player.inventory.weapons[i].current->ref)
				return (1);
		}
		i++;
	}
	return (0);
}

int		pick_weapon(t_env *env, t_wrap_sect *obj)
{
	int	iter;

	iter = 0;
	if (env->player.inventory.ui.nb_wpn < WORLD_NB_WEAPONS)
	{
		iter = check_weapon_type(env, obj->ref);
		if (!iter)
		{
			env->player.inventory.ui.nb_wpn++;
			env->player.inventory.weapons[obj->ref].current = obj;
			env->player.inventory.current = &env->player.inventory.weapons[obj->ref];
			env->player.inventory.current->ammo_current = env->world.armory[obj->ref].ammo_curr_max;
			env->player.inventory.current->ammo_magazine = env->world.armory[obj->ref].ammo_mag_max;
		}
		else
			return (14);
		obj->is_picked = 1;
		//******************************
		//******************************
		//fonction pour retirer de la map
		//******************************
		//******************************

		return (15);
	}
	return (16);
}

int		drop_wpn(t_env *env, t_wrap_wpn *wpn)
{
	t_vtx	vertex;

	if (wpn != NULL)
	{
		vertex.x = env->engine.player.where.x;
		vertex.y = env->engine.player.where.y;
		fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
		vertex, wpn->current->ref, wpn->current->is_wpn);
		*wpn = (t_wrap_wpn) {NULL, 0, 0};
		env->player.inventory.ui.nb_wpn--;
	}
	env->player.hud.is_txt = 17;
	return (1);
}
