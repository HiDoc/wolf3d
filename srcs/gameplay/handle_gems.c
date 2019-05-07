/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_gems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:34:52 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 18:13:01 by abaille          ###   ########.fr       */
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
			e->player.actions.is_flying = !e->player.actions.is_flying;
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
				ft_bzero(&e->player.inventory.gems[i - 1], sizeof(t_wrap_inv));
			}
			e->engine.player.sound.gem = 1;
		}
		if (i == 0)
			shortcut->nb_stack = 1;
	}
	return (1);
}

int	handle_gems(t_env *env)
{
	if (blue_gem(env))
		ui_put_data(env, (t_font){BLUE, "Illimited Ammo ON",
			env->hud.font.text, (t_vtx){W / 1.3, H / 1.8}, W / 60, -1, -1});
	if (green_gem(env))
		ui_put_data(env, (t_font){GREEN, "Invisiblity ON - Don't shoot !",
			env->hud.font.text, (t_vtx){W / 1.3, H / 1.7}, W / 60, -1, -1});
	if (red_gem(env))
		ui_put_data(env, (t_font){RED, "Super Strength ON",
			env->hud.font.text, (t_vtx){W / 1.3, H / 1.6}, W / 60, -1, -1});
	if (purple_gem(env))
		ui_put_data(env, (t_font){GOLD, "Invulnerability ON",
			env->hud.font.text, (t_vtx){W / 1.3, H / 1.5}, W / 60, -1, -1});
	return (1);
}
