/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_gems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:44:16 by abaille           #+#    #+#             */
/*   Updated: 2019/03/28 23:46:22 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	blue_gem(t_env *env)
{
	if (env->player.actions.is_superfast)
	{
		if (env->time.t_blue < 150)
		{
			// raise velocity
			env->time.t_blue++;
		}
		else
			env->time.t_blue = 0;
	}
	return (1);
}

int	green_gem(t_env *env)
{
	if (env->player.actions.is_invisible)
	{
		if (env->time.t_green < 150)
		{
			// variable set in enemy treatment
			env->time.t_green++;
		}
		else
		{
			env->time.t_green = 0;
			env->player.actions.is_invisible = 0;
		}
	}
	return (1);
}

int	red_gem(t_env *env)
{
	t_wrap_sect	*current;
	t_weapon	*ref;

	if (env->player.actions.is_superstrong)
	{
		if (env->player.inventory.current)
		{
			if (env->time.t_red < 150)
			{
				current = env->player.inventory.current->current;
				ref = &env->world.armory[current->ref];
				env->player.inventory.current->damage = ref->damage + 50;
				env->time.t_red++;
			}
			else
			{
				env->time.t_red = 0;
				env->player.inventory.current->damage -= 50;
				env->player.actions.is_superstrong = 0;
			}
		}
	}
	return (1);
}

int	purple_gem(t_env *env)
{
	if (env->player.actions.is_invulnerable)
	{
		if (env->time.t_purple < 150)
		{
			env->player.shield = 200;
			env->player.health = 200;
			env->time.t_purple++;
		}
		else
		{
			env->time.t_purple = 0;
			env->player.actions.is_invulnerable = 0;
		}
	}
	return (1);
}

int	action_gems(t_env *env)
{
	return (blue_gem(env)
	&& green_gem(env)
	&& red_gem(env)
	&& purple_gem(env));
}