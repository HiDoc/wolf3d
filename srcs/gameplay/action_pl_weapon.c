/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:32 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 22:24:52 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
			fill_wpn_inv(&inv->weapons[obj->ref], rwpn, obj);
			set_current_wpn(env, inv, obj->ref);
			obj->is_picked = 1;
			env->engine.player.sound.pick = 3;
		}
		return ((iter) ? NEW_WPN : HAVE_WPN);
	}
	return (drop_wpn(env, inv->current) ? pick_weapon(env, obj) : 0);
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
	t_vtx		vertex;
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
		return (ref == cur_ref
			? new_current_wpn(env, &env->player.inventory) : 1);
	}
	return (0);
}
