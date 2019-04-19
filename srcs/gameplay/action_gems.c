/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_gems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:44:16 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 20:26:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	gem_is_usable(t_env *env, int i)
{
	if (i == 1 && !env->time.t_blue)
		return (1);
	if (i == 2 && !env->time.t_green)
		return (1);
	if (i == 3 && !env->time.t_red)
		return (1);
	if (i == 4 && !env->time.t_purple)
		return (1);
	return (0);
}

int	action_gems(t_env *e, t_wrap_inv *shortcut, int i)
{
	if (shortcut)
	{
		if (i == 0)
			shortcut->current->action(e, shortcut);
		if (i == 1)
			e->player.actions.is_ammo_illimited = 1;
		if (i == 2)
			e->player.actions.is_invisible = 1;
		if (i == 3)
			e->player.actions.is_superstrong = 1;
		if (i == 4)
			e->player.actions.is_invulnerable = 1;
		if (gem_is_usable(e, i))
		{
			shortcut->nb_stack--;
			if (i != 0 && !shortcut->nb_stack)
			{
				shortcut = NULL;
				e->player.inventory.gems[i - 1].current = NULL;
			}
			e->engine.player.sound.gem = 1;
		}
		if (i == 0)
			shortcut->nb_stack = 1;
	}
	return (1);
}

int	blue_gem(t_env *env)
{
	int	ref;
	t_wrap_wpn	*cur;

	if (env->player.actions.is_ammo_illimited)
	{
		cur = env->player.inventory.current;
		ref = cur->current->ref;
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
	t_wrap_sect	*current;
	t_weapon	*ref;

	if (env->player.actions.is_superstrong)
	{
		if (env->player.inventory.current)
		{
			if (env->time.t_red < 600)
			{
				current = env->player.inventory.current->current;
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

int	handle_gems(t_env *env)
{
	if (blue_gem(env))
		ui_put_data(env, (t_font){BLUE, "Illimited Ammo ON", env->hud.text.text, (t_vtx){W / 1.3, H / 1.8}, W / 60, -1, -1});
	if (green_gem(env))
		ui_put_data(env, (t_font){GREEN, "Invisiblity ON - Don't shoot !", env->hud.text.text, (t_vtx){W / 1.3, H / 1.7}, W / 60, -1, -1});
	if (red_gem(env))
		ui_put_data(env, (t_font){RED, "Super Strength ON", env->hud.text.text, (t_vtx){W / 1.3, H / 1.6}, W / 60, -1, -1});
	if (purple_gem(env))
		ui_put_data(env, (t_font){GOLD, "Invulnerability ON", env->hud.text.text, (t_vtx){W / 1.3, H / 1.5}, W / 60, -1, -1});
	return (1);
}