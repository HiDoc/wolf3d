/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:32 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 02:04:38 by abaille          ###   ########.fr       */
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
	if (env->hud.inventory.nb_wpn < 3)
	{
		iter = check_weapon_type(env, obj->ref);
		if (!iter)
		{
			env->hud.inventory.nb_wpn++;
			env->player.inventory.weapons[obj->ref].current = obj;
			env->player.inventory.current = &env->player.inventory.weapons[obj->ref];
			env->player.inventory.current->ammo_current = env->world.armory[obj->ref].ammo_curr_max;
			env->player.inventory.current->ammo_magazine = env->world.armory[obj->ref].ammo_mag_max;
			env->player.inventory.current->damage = env->world.armory[obj->ref].damage;
		}
		else
			return (16);
		obj->is_picked = 1;
		return (15);
	}
	return (17);
}

int		new_current_wpn(t_env *env, t_inventory *inv)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
	{
		if (inv->weapons[i].current)
			break ;
		i++;
	}
	inv->current = &inv->weapons[i];
	inv->current->ammo_current = env->world.armory[i].ammo_current;
	inv->current->ammo_magazine = env->world.armory[i].ammo_magazine;
	inv->current->damage = env->world.armory[i].damage;
	return (1);
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
		*wpn = (t_wrap_wpn) {NULL, 0, 0, 0};
		new_current_wpn(env, &env->player.inventory);
		env->hud.inventory.nb_wpn--;
		env->hud.is_txt = 18;
	}
	return (1);
}
