/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:22:02 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 22:24:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_weapon_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < GAME_NB_WPN)
	{
		if (env->player.inventory.weapons[i].is_full)
		{
			if (ref == env->player.inventory.weapons[i].ref)
				return (1);
		}
		i++;
	}
	return (0);
}

int		set_current_wpn(t_env *env, t_inventory *inv, int i)
{
	env->player.actions.is_shooting = 0;
	env->player.actions.is_loading = 0;
	inv->current = &inv->weapons[i];
	inv->current->is_full = 1;
	inv->current->ref = inv->weapons[i].ref;
	inv->current->ammo_current = &inv->weapons[i].ammo[0];
	inv->current->ammo_magazine = &inv->weapons[i].ammo[1];
	inv->current->damage = &inv->weapons[i].ammo[2];
	env->engine.player.sound.pick = 3;
	return (1);
}

void	fill_wpn_inv(t_wrap_wpn *wpn, t_weapon *rwpn, t_wrap_sect *obj)
{
	wpn->is_full = 1;
	wpn->ref = obj->ref;
	wpn->ammo[0] = rwpn->ammo_current;
	wpn->ammo[1] = rwpn->ammo_magazine;
	wpn->ammo[2] = rwpn->damage;
}
