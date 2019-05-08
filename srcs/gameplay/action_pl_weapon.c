/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:32 by abaille           #+#    #+#             */
/*   Updated: 2019/05/05 19:31:37 by abaille          ###   ########.fr       */
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
	if (!inv->current)
		printf("lol i'm segfaulting\n");
	inv->current->is_full = 1;
	inv->current->ref = inv->weapons[i].ref;
	inv->current->ammo_current = &inv->weapons[i].ammo[0];
	inv->current->ammo_magazine = &inv->weapons[i].ammo[1];
	inv->current->damage = &inv->weapons[i].ammo[2];
	env->engine.player.sound.pick = 3;
	return (1);
}

int		pick_weapon(t_env *env, t_wrap_sect *obj)
{
	int			iter;
	t_weapon	*rwpn;
	t_inventory	*inv;
	t_sector	*sector;

	iter = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	inv = &env->player.inventory;
	if (env->hud.inventory.nb_wpn < 3)
	{
		iter = check_weapon_type(env, obj->ref);
		if (!iter)
		{
			rwpn = &env->world.armory[obj->ref];
			env->hud.inventory.nb_wpn++;
			inv->weapons[obj->ref].is_full = 1;
			inv->weapons[obj->ref].ref = obj->ref;
			inv->weapons[obj->ref].ammo[0] = rwpn->ammo_current;
			inv->weapons[obj->ref].ammo[1] = rwpn->ammo_magazine;
			inv->weapons[obj->ref].ammo[2] = rwpn->damage;
			set_current_wpn(env, inv, obj->ref);
		}
		else
		{
			env->engine.player.sound.nope = 1;
			return (HAVE_WPN);
		}
		obj->is_picked = 1;
		sector->nb_objects--;
		env->engine.player.sound.pick = 3;
		return (NEW_WPN);
	}
	return (drop_wpn(env, env->player.inventory.current)
	? pick_weapon(env, obj) : TOO_MANY_WPN);
}

int		new_current_wpn(t_env *env, t_inventory *inv)
{
	int	i;

	i = 0;
	while (i < GAME_NB_WPN)
	{
		if (inv->weapons[i].is_full)
			break ;
		i++;
	}
	set_current_wpn(env, inv, i);
	return (1);
}

int		drop_wpn(t_env *env, t_wrap_wpn *wpn)
{
	t_vtx	vertex;
	t_sector	*sector;
	int			ref;
	int			cur_ref;

	if (wpn->is_full && wpn->ref != FIST)
	{
		ref = wpn->ref;
		cur_ref = env->player.inventory.current->ref;
		sector = &env->engine.sectors[env->engine.player.sector];
		vertex.x = env->engine.player.where.x + 5;
		vertex.y = env->engine.player.where.y;
		fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
			vertex, (t_ixy){wpn->ref, env->engine.player.sector}, 1);
		ft_bzero(wpn, sizeof(t_wrap_wpn));
		env->hud.inventory.nb_wpn--;
		env->hud.is_txt = WPN_DROPPED;
		sector->nb_objects++;
		env->engine.player.sound.drop = 1;
		return (ref == cur_ref ? new_current_wpn(env, &env->player.inventory) : 1);
	}
	return (0);
}
