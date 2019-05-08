/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_gems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:44:16 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 16:35:54 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	blue_gem(t_env *env)
{
	int			ref;
	t_wrap_wpn	*cur;

	if (env->player.actions.is_ammo_illimited)
	{
		cur = env->player.inventory.current;
		ref = cur->ref;
		if (env->time.t_blue < 600)
		{
			*cur->ammo_current = env->world.armory[ref].ammo_current;
			*cur->ammo_magazine = env->world.armory[ref].ammo_magazine;
			env->time.t_blue++;
			return (1);
		}
		else
		{
			env->player.actions.is_ammo_illimited = 0;
			env->time.t_blue = 0;
		}
	}
	return (0);
}

int	green_gem(t_env *env)
{
	if (env->player.actions.is_invisible)
	{
		if (env->time.t_green < 600 && !env->player.actions.is_shooting)
		{
			env->time.t_green++;
			return (1);
		}
		else
		{
			env->time.t_green = 0;
			env->player.actions.is_invisible = 0;
		}
	}
	return (0);
}

int	red_gem(t_env *env)
{
	t_wrap_wpn	*current;
	t_weapon	*ref;

	if (env->player.actions.is_superstrong)
	{
		if (env->player.inventory.current->is_full)
		{
			if (env->time.t_red < 600)
			{
				current = env->player.inventory.current;
				ref = &env->world.armory[current->ref];
				*env->player.inventory.current->damage = ref->damage + 100;
				env->time.t_red++;
				return (1);
			}
			else
			{
				env->time.t_red = 0;
				*env->player.inventory.current->damage -= 100;
				env->player.actions.is_superstrong = 0;
			}
		}
	}
	return (0);
}

int	purple_gem(t_env *env)
{
	if (env->player.actions.is_invulnerable)
	{
		if (env->time.t_purple < 600)
		{
			env->player.shield = 200;
			env->player.health = 200;
			env->time.t_purple++;
			return (1);
		}
		else
		{
			env->time.t_purple = 0;
			env->player.actions.is_invulnerable = 0;
		}
	}
	return (0);
}
