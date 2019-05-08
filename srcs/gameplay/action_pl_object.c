/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:24 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 20:20:57 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			access_object(t_env *env, t_sector *sector)
{
	t_wrap_sect *current;

	current = NULL;
	if (sector->head_object)
		current = sector->head_object;
	while (current)
	{
		if (!current->is_picked)
		{
			if (current->is_pickable)
			{
				env->hud.is_txt = pick_object(env, current);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int			pick_gem(t_env *env, t_wrap_sect *obj)
{
	int	ref;

	ref = obj->ref - B_GEM;
	if (!env->player.inventory.gems[ref].is_full)
	{
		env->player.inventory.gems[ref].ref = obj->ref;
		env->hud.shortcut[ref + 1] = &env->player.inventory.gems[ref];
		env->player.inventory.gems[ref].is_full = 1;
	}
	env->player.inventory.gems[ref].nb_stack++;
	obj->is_picked = 1;
	env->engine.player.sound.pick = 2;
	return (NEW_ITEM);
}

static int	csmble_to_inventory(t_env *e, t_wrap_sect *obj)
{
	t_uinv	*inv;
	int		index;

	if (e->player.inventory.nb_current_obj < 6
	&& obj->ref < WORLD_NB_CSMBLE && !obj->is_wpn)
	{
		inv = &e->hud.inventory;
		index = get_inventory_place(e);
		e->player.inventory.objects[index].ref = obj->ref;
		e->player.inventory.objects[index].is_full = 1;
		e->player.inventory.objects[index].action = obj->action;
		e->player.inventory.nb_current_obj++;
		inv->objects[index].sprite = e->world.objects[obj->ref].sprite;
		if (obj->ref == 5)
			e->hud.shortcut[0] = &e->player.inventory.objects[index];
		else
			e->player.inventory.objects[index].nb_stack++;
		obj->is_picked = 1;
		e->engine.player.sound.pick = 1;
		return (1);
	}
	return (0);
}

int			pick_object(t_env *env, t_wrap_sect *obj)
{
	int			i;
	t_inventory	*inv;

	i = 0;
	inv = &env->player.inventory;
	if (((i = check_object_type(inv->objects, obj->ref, 6)) > -1)
	&& !obj->is_wpn)
	{
		if (inv->objects[i].nb_stack >= env->world.objects[obj->ref].max_stack)
			return (FULL_STACK);
		inv->objects[i].nb_stack++;
		obj->is_picked = 1;
		env->engine.player.sound.pick = 1;
		return (NEW_ITEM);
	}
	else if (csmble_to_inventory(env, obj))
		return (NEW_ITEM);
	else if (obj->ref >= WORLD_NB_CSMBLE && !obj->is_wpn)
		return (pick_gem(env, obj));
	!obj->is_wpn ? env->engine.player.sound.nope = 1 : 0;
	return (!obj->is_wpn ? FULL_INV : pick_weapon(env, obj));
}

void		drop_object(t_env *env, t_wrap_inv *object)
{
	t_vtx		vertex;
	t_sector	*sector;

	if (object->is_full)
	{
		sector = &env->engine.sectors[env->engine.player.sector];
		if (!object->is_used)
		{
			vertex.x = env->engine.player.where.x + 1;
			vertex.y = env->engine.player.where.y;
			fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
				vertex, (t_ixy){object->ref, env->engine.player.sector}, 0);
			env->engine.player.sound.drop = 1;
		}
		if (object->nb_stack > 1)
			object->nb_stack--;
		else
		{
			if (object->ref == 5)
				env->hud.shortcut[object->ref] = NULL;
			ft_bzero(object, sizeof(t_wrap_inv));
			env->player.inventory.nb_current_obj--;
		}
	}
	env->hud.is_txt = ITEM_SUP;
}
