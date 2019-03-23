/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:24 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 22:13:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		is_pickable_object(t_env *env, t_sector *sector)
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
				env->player.hud.is_txt = pick_object(env, current);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int		get_inventory_place(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (env->player.inventory.objects[i].current == NULL)
			return (i);
		i++;
	}
	return (i);
}

int		check_object_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (env->player.inventory.objects[i].current != NULL)
		{
			if (ref == env->player.inventory.objects[i].current->ref)
				return (i);
		}
		i++;
	}
	return (-1);
}

int		pick_object(t_env *env, t_wrap_sect *obj)
{
	int	index;
	int	iter;

	iter = 0;
	if (env->player.inventory.nb_current_obj < 6
	&& !obj->is_wpn)
	{
		iter = check_object_type(env, obj->ref);
		if (iter > -1)
		{
			if (env->player.inventory.objects[iter].nb_stack >= env->world.objects[obj->ref].max_stack)
				return (5);
			env->player.inventory.objects[iter].nb_stack++;
		}
		else
		{
			index = get_inventory_place(env);
			env->player.inventory.objects[index].current = obj;
			env->player.inventory.objects[index].nb_stack++;
			env->player.inventory.nb_current_obj++;
			env->player.hud.inventory.objects[index].sprite = env->world.objects[obj->ref].sprite;
			if (obj->ref < 6)
				env->player.hud.shortcut[obj->ref] = &env->player.inventory.objects[index];
		}
		obj->is_picked = 1;
		env->player.hud.is_txt = 6;
		return (5);
	}
	return (!obj->is_wpn ? 6 : pick_weapon(env, obj));
}

int		drop_object(t_env *env, t_wrap_inv *object)
{
	t_vtx	vertex;

	if (object->current != NULL)
	{
		if (!object->is_used)
		{
			vertex.x = env->engine.player.where.x + 1;
			vertex.y = env->engine.player.where.y;
			fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
			vertex, object->current->ref, object->current->is_wpn);

		}
		if (object->nb_stack > 1)
			object->nb_stack--;
		else
		{
			if (object->current->ref < 6)
				env->player.hud.shortcut[object->current->ref] = NULL;
			*object = (t_wrap_inv)
			{NULL, 0, 0, {{{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}}};
			env->player.inventory.nb_current_obj--;
		}
	}
	env->player.hud.is_txt = 8;
	return (1);
}
